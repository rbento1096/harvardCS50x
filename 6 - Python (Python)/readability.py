def main():
    # gets text
    text = input("Text: ")

    # initializes all variables. words start at 1, since we will use space between words to count them
    nr_letters = 0
    nr_words = 1
    nr_sentences = 0

    # loops through all the characters in the text
    for char in text:
        # if char is a letter, increment letters by 1
        nr_letters += letters(char)
        # if char is a blankspace increment words by 1
        nr_words += words(char)
        # if char is a punctuation mark, increment sentences by 1
        nr_sentences += sentences(char)

    # The Coleman-Liau formula calculates the reading level of the text
    C_L_index = 0.0588 * (nr_letters * 100 / nr_words) - 0.296 * (nr_sentences * 100 / nr_words) - 15.8

    if C_L_index >= 16:
        print("Grade 16+")
        return

    if C_L_index < 1:
        print("Before Grade 1...")
        return

    print(f"Grade {round(C_L_index)}")
    return


def letters(character):
    # if the character is an upper or lower-case letter, return 1
    if ord(character) >= ord("A") and ord(character) <= ord("Z"):
        return 1
    elif ord(character) >= ord("a") and ord(character) <= ord("z"):
        return 1
    else:
        return 0


def words(character):
    # if the chacter is a blank space, a new word is added
    if character == " ":
        return 1
    else:
        return 0


def sentences(character):
    # these characters indicate the end of a sentence
    if character in [".", "!", "?"]:
        return 1
    else:
        return 0


# executes main
main()