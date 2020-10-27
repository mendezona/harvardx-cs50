text = input("Text: ")

letterCount = 0
wordCount = 1
sentanceCount = 0

for character in text:
    if (character.isalpha() == True):
        letterCount += 1
        
    elif(character.isspace() == True):
        wordCount += 1
        
    elif (character == '.' or character == '!' or character == '?'):
        sentanceCount += 1
        
index = (0.0588 * (letterCount / wordCount * 100)) - (0.296 * (sentanceCount / wordCount * 100)) - 15.8

if (index > 16):
    print("Grade 16+")
    
elif (index < 1):
    print("Before Grade 1")
    
else:
    print("Grade " + str(round(index)))
    