from cs50 import get_float

while True:
    dollars = get_float("Change owed: ")
    if dollars > 0:
        break
change = round(dollars * 100)

# Variable to track number of coins
minCoins = 0

while change > 0:
    # Quarters first
    if change >= 25:
        change -= 25
        minCoins += 1

    # Then dimes
    elif change >= 10:
        change -= 10
        minCoins += 1

    # Then nickels
    elif change >= 5:
        change -= 5
        minCoins += 1

    # Then pennies
    elif change >= 1:
        change -= 1
        minCoins += 1

print(minCoins)
