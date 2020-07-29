from cs50 import get_int

while True:
    cardNumber = get_int("Number: ")
    if cardNumber > 0:
        break

# Number of digits
digits = len(str(cardNumber))

# Implementation of Luhn's Algorithm for credit card validity
totalSum = 0
for i in range(2, digits + 1, 2):
    digit = int(cardNumber % (10 ** i) / 10 ** (i - 1))

    # if multiplication by 2 results in double digit number, add individual digits
    if digit * 2 > 9:
        totalSum += int((digit * 2 / 10) + (digit * 2 % 10))

    # else add multiplication by 2
    else:
        totalSum += int(digit * 2)

    # store first digit from even number to check provider
    firstEven = digit

for i in range(1, digits + 1, 2):
    digit = int(cardNumber % (10 ** i) / 10 ** (i - 1))
    totalSum += int(digit)

    # store first digit from odd number to check provider
    firstOdd = digit

lastDigit = int(totalSum % 10)

# bool variable for validity
legit = False

if lastDigit == 0:
    legit = True

if legit == True:
    if firstEven == 5 and (firstOdd >= 1 and firstOdd <= 5) and digits == 16:
        print("MASTERCARD")
    elif firstEven == 4 and (digits == 13 or digits == 16):
        print("VISA")
    elif firstOdd == 3 and (firstEven == 4 or firstEven == 7) and digits == 15:
        print("AMEX")
    else:
        print("INVALID")
else:
    print("INVALID")
