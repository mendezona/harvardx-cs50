import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # get data from database
    username = db.execute("SELECT username FROM users WHERE id=:id", id=session["user_id"])
    symbol = db.execute("SELECT symbol FROM stocks WHERE username=:username GROUP BY symbol", username=username[0]["username"])
    stockName = db.execute("SELECT name FROM stocks WHERE username=:username GROUP BY symbol", username=username[0]["username"])
    quantity = db.execute("SELECT symbol, SUM(quantity) FROM stocks WHERE username=:username GROUP BY symbol", username=username[0]["username"])

    #initialise grand total and index table
    indexTable = {}
    grandTotal = 0

    #iterate over data pulled from database and add to dictionary of stock
    for count in range(len(symbol)):
        symbolStock = symbol[count]["symbol"]
        stockNameStock = stockName[count]["name"]
        stockQty = float (quantity[count]["SUM(quantity)"])
        price = lookup(symbolStock)["price"]
        total = round(stockQty * price, 2)
        grandTotal += total

        indexTable[symbolStock] = [stockNameStock, stockQty, price, total]

    #use dictionary and grand total to render index page
    return render_template("index.html", indexTable=indexTable, grandTotal=round(grandTotal, 2))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    #if GET, render buy template
    if request.method == "GET":
        return render_template("buy.html")

    #if POST from buy page
    else:
        #put input as uppercase to look for stock
        stockQuote = lookup((request.form.get("symbol")).upper())

        #if stock not found render error
        if stockQuote == None:
            return render_template("buyerror.html", error="Stock not found.")

        #if stock found, get price, how much cash user has, username of user and time of trade
        else:
            price =  stockQuote["price"] * float (request.form.get("quantity"))
            userCash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
            username = db.execute("SELECT username FROM users WHERE id = :id", id=session["user_id"])
            now = datetime.now()

            #if user does not have enough cash render error
            if price > userCash[0]["cash"]:
                return render_template("buyerror.html", error="Not enough cash available.")

            #if user has enough cash, update stock register, update amount of cash user has, redirect to homepage
            else:
                db.execute("INSERT INTO stocks (username, symbol, quantity, price, time, name) VALUES (:username, :symbol, :quantity, :price, :time, :name)", username=username[0]["username"], symbol=stockQuote["symbol"], quantity=request.form.get("quantity"), price=stockQuote["price"], time=now.strftime("%m/%d/%Y, %H:%M:%S"), name=stockQuote["name"])
                db.execute("UPDATE users SET cash = :newAmount WHERE id = :id", newAmount=userCash[0]["cash"]-price, id=session["user_id"])
                return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # get data from database
    username = db.execute("SELECT username FROM users WHERE id=:id", id=session["user_id"])
    history = db.execute("SELECT symbol, name, quantity, price, time FROM stocks WHERE username=:username ORDER BY time DESC", username=username[0]["username"])

    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    #Let user go to form to submit stock symbol
    if request.method == "GET":
        return render_template("quote.html")

    #once user has submitted stock symbol look up stock via API
    else:
        stockQuote = lookup((request.form.get("symbol")).upper())

        #if stock found render the quote
        if stockQuote != None:
            return render_template("quoted.html", stockQuote=stockQuote)

        #if stock not found provide error
        else:
            return render_template("stocknotfound.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User is registering an ID
    if request.method == "GET":
        return render_template("register.html")

    # User has attempted to register an ID with POST
    else:

        # If no user name provided
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # If no passowrd provided
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Save username and password into database
        username = request.form.get("username")
        passwordHash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :passwordHash)", username=username, passwordHash=passwordHash)
        return render_template("registrationSuccess.html")

@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    """Register user"""

    # User is navigates to page
    if request.method == "GET":
        return render_template("password.html")

    # User has attempted to register an ID with POST
    else:

        # If no passowrd provided
        if not request.form.get("password"):
            return apology("must provide password", 403)

        # Save username and password into database
        passwordHash = generate_password_hash(request.form.get("password"))
        db.execute("UPDATE users SET hash = :passwordHash WHERE id=:id", id=session["user_id"], passwordHash=passwordHash)
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    """Buy shares of stock"""

    #if GET, render sell template
    if request.method == "GET":
        return render_template("sell.html")

    #if POST from sell page
    else:
        #put input as uppercase to look for stock
        stockQuote = lookup((request.form.get("symbol")).upper())

        #if stock not found render error
        if stockQuote == None:
            return render_template("sellerror.html", error="Stock not found.")

        #if stock found, get username, get quantity of stock user owns
        else:
            username = db.execute("SELECT username FROM users WHERE id = :id", id=session["user_id"])
            quantity = db.execute("SELECT SUM(quantity) FROM stocks WHERE username=:username AND symbol=:symbol", username=username[0]["username"], symbol=request.form.get("symbol").upper())

            #if user does not have enough stocks to complete trade
            if float (request.form.get("quantity")) > quantity[0]["SUM(quantity)"]:
                return render_template("buyerror.html", error="Trade exceeds quantity owned.")

            #if user has enough stocks to execute trade
            else:
                #get amount of cash user has, price of trade and time
                userCash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
                price =  (stockQuote["price"] * float (request.form.get("quantity"))) * -1
                now = datetime.now()

                #add trade to database, update amount of cash user has, redirect to index
                db.execute("INSERT INTO stocks (username, symbol, quantity, price, time, name) VALUES (:username, :symbol, :quantity, :price, :time, :name)", username=username[0]["username"], symbol=stockQuote["symbol"], quantity=int(request.form.get("quantity"))*-1, price=stockQuote["price"], time=now.strftime("%m/%d/%Y, %H:%M:%S"), name=stockQuote["name"])
                db.execute("UPDATE users SET cash = :newAmount WHERE id = :id", newAmount=userCash[0]["cash"]-price, id=session["user_id"])
                return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
