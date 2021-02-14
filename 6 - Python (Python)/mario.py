def main():
    # initializes height variable
    height = False

    # sets the min and max values for height
    min = 1
    max = 8

    # ensures user inputs correct value
    while height not in range(min, max + 1):
        # try catch block prevents ensures input is an int
        try:
            print("Enter an integer from 1 to 8")
            height = int(input("What is the pyramid height? "))
        except ValueError:
            print("Format not correct. Enter an integer between 1 and 8.")
    # calls the function pyramids using height
    pyramids(height, height)


def pyramids(blocks, height):

    # start fron the tip through recursion, ensuring first call to function uses only 1 block
    if blocks - 1 != 0:
        pyramids(blocks - 1, height)

    # prints the required spaces to put the blocks in place
    for i in range(0, height - blocks):
        print(" ", end="")

    # prints the number of blocks on this layer
    for i in range(0, blocks):
        print("#", end="")

    # prints two spaces to separate the pyramid
    print("  ", end="")

    # prints the number of blocks of this layer, again
    for i in range(0, blocks):
        print("#", end="")

    # prints a new line
    print("")


# executes the main function
main()