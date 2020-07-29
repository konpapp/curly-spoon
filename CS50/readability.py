from cs50 import get_string

text = get_string("Text: ")

# Initialize variables for counting
letters = 0
words = 0
sentences = 0

for i in range(len(text)):
    # If alphanumeric character increment letters
    if text[i].isalpha():
        letters += 1
    # If space increment words
    elif text[i].isspace():
        words += 1
        # And if the previous character is ".", "?", "!", increment sentences
        if text[i - 1] == "." or text[i - 1] == "?" or text[i - 1] == "!":
            sentences += 1

# Increment by 1 for the last word and sentence that doesn't have space
words += 1
sentences += 1

# Coleman-Liau readability index = 0.0588 * L - 0.296 * S - 15.8
L = letters / words * 100
S = sentences / words * 100

index = round(0.0588 * L - 0.296 * S - 15.8)
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
