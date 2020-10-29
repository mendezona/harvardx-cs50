# TODO
import csv
import sys

from cs50 import SQL

# check that usage is correct
if (len(sys.argv) != 2):

    print('Usage: python import.py characters.csv')

else:

    # give access to students databse
    db = SQL("sqlite:///students.db")

    # open CSV file as dictionary
    with open(sys.argv[1], newline='') as csvfile:
        characterFile = csv.DictReader(csvfile)

        # iterate over each row of CSV file
        for row in characterFile:

            # split name and allocate first/middle/last names depending on number of names provided (max 3 names)
            name = row['name'].split()
            if len(name) == 2:
                firstName = name[0]
                middleName = None
                lastName = name[1]

            else:
                firstName = name[0]
                middleName = name[1]
                lastName = name[2]

            # insert names, house and birth into database file
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (%s, %s, %s, %s, %s);", 
                       firstName, middleName, lastName, row['house'], row['birth'])