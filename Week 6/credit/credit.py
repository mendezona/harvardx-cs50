cardnum = 0

while (True):
    try:
        cardNum = input("Number: ")
        if (int(cardNum) < 0):
            continue

    except ValueError:
        continue

    else:
        break

multiplyByTwo = []
for number in cardNum[-2::-2]:
    multiplyByTwo.append(number)

count = 0
for multiply in multiplyByTwo:
    multiplyByTwo[count] = (int(multiply))*2
    count += 1

additionTotal = 0
for addition in multiplyByTwo:
    for digit in str(addition):
        additionTotal += int(digit)

for newAddition in cardNum[len(cardNum)::-2]:
    additionTotal += int(newAddition)

if (additionTotal % 10 == 0):

    if (len(cardNum) == 16):
        if (cardNum[0] == '5' and (cardNum[1] == '1' or cardNum[1] == '2' or cardNum[1] == '3' or cardNum[1] == '4' or cardNum[1] == '5')):
            print('MASTERCARD')

        elif (cardNum[0] == '4'):
            print('VISA')

    elif (len(cardNum) == 13):
        if (cardNum[0] == '4'):
            print('VISA')

    elif (len(cardNum) == 15):
        if (cardNum[0] == '3' and (cardNum[1] == '4' or cardNum[1] == '7')):
            print('AMEX')

    else:
        print('INVALID')

else:
    print('INVALID')
