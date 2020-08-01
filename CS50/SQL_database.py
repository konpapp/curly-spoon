from sys import argv, exit
import csv
import cs50

# Database as command-line argument
if len(argv) != 2:
    print("Usage: python import.py <characters.csv>")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

fullName = []

with open(argv[1], "r") as students:
    reader = csv.DictReader(students)

    for row in reader:

        # Check for student with middle name
        fullName = row["name"].split(" ")

        # If no middle name, insert None
        if len(fullName) == 2:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",

                       fullName[0], None, fullName[1], row["house"], row["birth"])
        elif len(fullName) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ? ,?)",

                       fullName[0], fullName[1], fullName[2], row["house"], row["birth"])
                       
##########################################################################################################################                       
                       
from sys import argv, exit
import csv
import cs50

# Check for group (house) as command line argument
if len(argv) != 2:
    print("Usage: python roster.py <house>")
    exit(1)

db = cs50.SQL(f"sqlite:///students.db")

# Select distinct to avoid values appearing more than once
results = db.execute(f'SELECT DISTINCT first, middle, last, birth FROM students WHERE house = "{argv[1]}" ORDER BY last')

for row in results:
    if row["middle"] != None:
        print(f'{row["first"]} {row["middle"]} {row["last"]}, born {row["birth"]}')
    else:
        print(f'{row["first"]} {row["last"]}, born {row["birth"]}')
