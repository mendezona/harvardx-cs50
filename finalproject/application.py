#import libraries to write to local files instead of cookies
import os
from tempfile import mkdtemp

#import flask library and set app to reference this file, and security
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session

from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

#import custom helper files
from apis import lookupWeather
from datetime import datetime, timedelta

#import SQL
from cs50 import SQL

# Configure Flask app
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

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite databasefrom cs50 import SQL
db = SQL("sqlite:///basketball.db")

# Index page
@app.route("/")
def index():
    return render_template("index.html")

# Get the timestamp now, weather from APIs file, calculate time between sunset and time now, render weather page
@app.route("/weather")
def weather():
    timeNow = datetime.now()
    weather = lookupWeather()
    sunsetNow = round((timedelta.total_seconds(weather["sunset"] - timeNow) / 60) / 60)
    return render_template("weather.html", weather=lookupWeather(), sunsetNow=sunsetNow)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User is registering an ID
    if request.method == "GET":
        return render_template("register.html")

    # User has attempted to register an ID with POST
    else:
        usernameDict = db.execute("SELECT username FROM users")
        usernameList = []
        for user in usernameDict:
            usernameList.append(user["username"])

        # if username is already taken or not filled in
        if request.form.get("username") == '' or request.form.get("username") in usernameList:
            return render_template("register.html", error='usernameTaken')

        # Save username and password into database
        username = request.form.get("username")
        passwordHash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :passwordHash)", username=username, passwordHash=passwordHash)
        return redirect("/login")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            print("found")
            return render_template("login.html", error="errorFound")

        else:
            print("not found")
            # Remember which user has logged in
            session["user_id"] = rows[0]["id"]
            session["username"] = rows[0]["username"]
            session['logged_in'] = True

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


@app.route("/noticeboard", methods=["GET", "POST"])
def noticeboard():

    #if loading without posting a message
    if request.method == "GET":
        yesterday = datetime.now() - timedelta(hours = 24)
        messages = db.execute("SELECT username, message, time, availability, seeking FROM messages WHERE time >= :yesterday", yesterday=yesterday)

        return render_template("noticeboard.html", messages=messages)

    #if message posted
    else:
        if session.get('logged_in') == True:
            username = db.execute("SELECT username FROM users WHERE id = :id", id=session["user_id"])
            user = username[0]["username"]

        else:
            user = 'anonymous'

        message = request.form.get("message")
        seeking = request.form.get("seeking")
        availability = request.form.get("availability")
        postTime = datetime.now()

        db.execute("INSERT INTO messages (username, message, time, availability, seeking) VALUES (:username, :message, :time, :availability, :seeking)", username=user, message=message, time=postTime, availability=availability, seeking=seeking)

        yesterday = datetime.now() - timedelta(hours = 24)
        messages = db.execute("SELECT username, message, time, availability, seeking FROM messages WHERE time >= :yesterday", yesterday=yesterday)

        return render_template("noticeboard.html", messages=messages)

@app.route("/thankyou")
def thankyou():

    return render_template("thankyou.html")