import csv
from sys import argv, exit

if len(argv) != 3:
    print("Usage: python dna.py STR_counts.csv DNA_sequence.txt")
    exit(1)

db = []

with open(argv[1], newline='') as csvfile:
    database = csv.reader(csvfile)
    for row in database:
        db.append(row)

with open(argv[2], "r") as textfile:
    sequence = textfile.read()

# Helper variables for counting
match = 0
totalMatch = 0
baseCount = []

for i in range(1, len(db[0])):
    # Assign the STR to be examined against
    base = db[0][i]

    # for each element in sequence
    for j in range(len(sequence)):
        # If the limits of the sequence are exceeded, break
        if j + len(base) > len(sequence):
            break
        x = j
        # While the substring is similat to the examined STR, count consecutive matches
        while sequence[x:x + len(base)] == base:
            match += 1
            x += len(base)
            # Break if no longer consecutive
            if x > len(sequence) or sequence[x:x + len(base)] != base:
                break

        # Replace max match count
        if match > totalMatch:
            totalMatch = match

        match = 0

    # Append to list for each STR after converting to str
    baseCount.append(str(totalMatch))
    totalMatch = 0

for i in range(len(db)):
    if db[i][1:] == baseCount:
        print(db[i][0])
        exit(0)
print("No match")
