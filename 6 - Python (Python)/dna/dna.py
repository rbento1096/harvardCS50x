import re
import csv
import sys


def main():
    people = []

    # appends each row as a dictionary to the people list
    with open(sys.argv[1]) as db:
        reader = csv.DictReader(db)
        for row in reader:
            people.append(row)

    # copies the DNA sequence into the variable sequence
    with open(sys.argv[2], "r") as sample:
        sequence = sample.read().strip()

    # checks if there is a second argument when running the programs
    try:
        sys.argv[2]
    # if there isn't indicate the correct usage
    except IndexError:
        print("Usage: python dna.py data.csv sequence.txt")

    # creates a dictionary to store the repeats by using one form the list as a prototype
    repeats = get_repeats(people[0])

    # counts the longest consecutive streak in the sequence for each STR
    count_repeats(repeats, sequence)

    # checks if the sequence matches any one in the list
    get_match(people, repeats)
    return


def get_repeats(person):
    # returns a dictionary with all values equal to 0 to initialize
    return person.fromkeys(person, 0)


def count_repeats(repeats, sequence):
    # each key in repeats is an STR, we will loop through each
    for repeat in list(repeats.keys()):
        # bypasses the name key, as it won't be present on the sequence
        if repeat != "name":
            try:
                # findall will look for a regex consisting of the repeat and return a list with all STRs matching the repeat
                # dividing every item's length in the list by the length of the repeat returns the number of consecutive repeats
                # max gets the highest value, str converts it to a string
                repeats[repeat] = str(max([len(x) // len(repeat) for x in re.findall(rf'((?:{repeat})+)', sequence)]))
            except ValueError:
                # if the STR is not in the sequence, list will be null and max will return an error
                # handle the exception and print no match as specified
                print("No match")


def get_match(people, repeats):
    # checks every person
    for person in people:
        # repeats has the keys but also the name key which has the value of 0
        # we equal the name, so the next condition will not return False because of the name
        repeats['name'] = person['name']
        # if we have a match
        if repeats == person:
            # print person name
            print(person['name'])
            return
    # else no match has been found
    print("No match")


main()