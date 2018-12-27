# Count the minimum number of coins

from cs50 import get_float
from math import floor

def main():
    # Get user input
    cash = floor(100 * get_positive_float("How much money do you need to transfer? "))

    # Determine minimal number of coins
    coins = cash // 25
    cash %= 25

    coins += cash // 10
    cash %= 10

    coins += cash // 5
    cash %= 5

    coins += cash

    # Print the result
    print(coins)

def get_positive_float(message):
    """Ask the user until the number is positive"""
    while True:
        f = get_float(message)
        if (f > 0):
            return f;

if __name__ == "__main__":
    main()