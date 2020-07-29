from cs50 import get_int

# check for positive integer less than 9
while True:
    height = get_int("Height: ")
    if height > 0 and height <= 8:
        break

for i in range(height):
    # moving to the right
    for j in range(height - i - 1):
        print(" ", end="")

    # building left block
    for j in range(i + 1):
        print("#", end="")

    # space
    print("  ", end="")

    # building right block
    for j in range(i + 1):
        print("#", end="")

    print()
