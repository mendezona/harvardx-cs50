import csv
import sys

# check that usage is correct
if (len(sys.argv) != 3):

    print('Usage: python dna.py data.csv sequence.txt')

else:
    # open database file
    databaseFile = open(sys.argv[1], 'r')

    # put csv file into reader and record header row as array
    reader = csv.reader(databaseFile)
    headerRow = next(reader)

    # count number of people by recording number or rows after header row
    peopleCount = 0
    for row in reader:
        peopleCount += 1

    # close database file
    databaseFile.close()

    # open sequences file and move string into memory
    sequencesFile = open(sys.argv[2], 'r')
    for sequence in sequencesFile:
        sequenceString = sequence

    # initialise dictionary to record the number of sequences found consectively, per sequence
    highscores = {}

    # iterate across DNA headers from csv file without names column
    for header in headerRow[1:]:

        # check if the header is in sequence string
        if header in sequenceString:

            # initialise highscore for header
            headerHighscore = 0

            # iterate acrross the sequence string
            for cursorPos in range(len(sequenceString)):

                # check if letter in cursor matches first letter of DNA header
                if sequenceString[cursorPos] == header[0]:

                    # mark in check as true, record number of sequential iterations
                    sequenceCheck = True
                    iteration = 0

                    # while doing check
                    while sequenceCheck == True:

                        # intialise the next letters to look at as per length of DNA header
                        tempString = ''
                        for sequences in sequenceString[cursorPos:cursorPos + len(header)]:
                            tempString += sequences

                        # if header is the same as the next letters
                        if header == tempString:

                            # move cursor up and add one iteration to the count
                            cursorPos = cursorPos + len(header)
                            iteration += 1

                            # record highscore for DNA header if current iteration is greater
                            if headerHighscore < iteration:
                                headerHighscore = iteration
                                highscores.update({header: headerHighscore})

                        # if next letters do not match DNA header, exit check
                        else:
                            sequenceCheck = False

                # move cursor up in sequence string
                cursorPos += 1

        # mark as not found if header not found in sequence string
        else:
            highscores.update({header: 0})

    # initialise matches found and winner name
    matchFound = False
    winner = ''

    # open database file
    databaseFile = open(sys.argv[1], 'r')

    # open database file in DictReader mode, record rows in people Dict with key as numeric row
    dictReader = csv.DictReader(databaseFile)

    # iterate over rows in CVS fike
    for row in dictReader:

        # initialise count of matches found
        matchesFound = 0
        
        # iterate over headers excluding name header
        for headers in headerRow[1:]:
            
            # if value in person's DNA matches the highscore recorded for DNA sequence mark as match
            if int(row[headers]) == highscores.get(headers):
                matchesFound += 1
            
            # if all DNA matches, mark as winner
            if matchesFound == len(headerRow) - 1:
                matchFound = True
                winner = row['name']

    # close database file
    databaseFile.close()
    
    # if winner found print name, else print no match
    if matchFound == True:
        print(winner)

    else:
        print('No match')