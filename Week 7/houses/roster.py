# TODO
import csv
import sys

from cs50 import SQL

# check that usage is correct
if (len(sys.argv) != 2):

    print('Usage: python roster.py House')

else:
    
    # give access to students databse
    db = SQL("sqlite:///students.db")
    
    # query database, which returns in form of dictionary
    returnDict = db.execute("SELECT * FROM students WHERE house = %s ORDER BY last, birth DESC;", sys.argv[1])
    
    # sort and print based on the enty having a middle name or not
    for entry in returnDict:
        if entry['middle'] != None:
            print(entry['first'], entry['middle'], entry['last'] + ', born', entry['birth'])
            
        else:
            print(entry['first'], entry['last'] + ', born', entry['birth'])
