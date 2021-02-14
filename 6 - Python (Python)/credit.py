def main():
    # initialized the var to store the card number
    number = "blank"
    # ensures card number consists only of integers
    while number.isdigit() == False:
        number = input("Credit card number? ")

    # creates a set with possible card lengths and outputs invalid if card has different length
    lengths = {13, 15, 16}
    if len(number) not in lengths:
        print("INVALID")
        return

    # returns the sum of the cards digits according to Luhn's algorithm
    luhn_sum = luhn_algorithm(number)
    # checks if last digit is 0 to validate card
    luhn_valid = luhn_sum % 10 == 0
    if luhn_valid:
        # if so, check the card brand
        print(check_card(number))


def luhn_algorithm(nr):
    # initializes a list with the odd digits' and the even digits' sums
    sums = [0, 0]

    # starting from the last digit, add two by two
    for i in range(len(nr) - 1, -1, -2):
        sums[0] += int(nr[i])

    # starting from the second to last digit, multiply by 2 every digit and add two by two
    digits = ""
    for i in range(len(nr) - 2, -1, -2):
        product = int(nr[i]) * 2
        digits += str(product)
    # we stored the previous addition in a sum because we will now add the DIGITS, not the product
    for i in range(0, len(digits)):
        sums[1] += int(digits[i])

    # returns the sum of the odd and even digits
    return sums[0] + sums[1]


def check_card(number):
    # creates a dictionary with first card digit as key, with second digit, card length and card name as values
    cards = {
        "3": ((4, 7), [15], "AMEX"),
        "4": ((list(range(10))), [13, 16], "VISA"),
        "5": ((list(range(1, 6))), [16], "MASTERCARD")
    }
    # using the first card digit, gets the possible key, if there isn't one, return INVALID
    first = cards.get(number[0], "INVALID")

    # if second digit is within possible second digits
    if int(number[1]) in first[0]:
        # if length of number is within possible lengths for each card
        if len(number) in first[1]:
            # print the card name
            return first[2]
    # else return "INVALID"
    return "INVALID"


main()