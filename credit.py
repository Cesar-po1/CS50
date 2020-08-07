 # Credit pset 6 python
import sys
import math
from cs50 import get_int

card = 0
card_len = 0
digit2 = 0

card = get_int("What's your card number? \n")

if card < 1000000000000 or card > 10000000000000000:  # validates valid lenght

    print("INVALID")
    exit(0)  # finishes program
    
card_len = len(str(card))

digit2 = ((card % 100) // 10) * 2  # gets the second to last digit and multiplies it by two
digit4 = int(((card % 10000) // 1000) * 2)
digit6 = int(((card % 1000000) // 100000) * 2)
digit8 = int(((card % 100000000) // 10000000) * 2)
digit10 = int(((card % 10000000000) // 1000000000) * 2)
digit12 = int(((card % 1000000000000) // 100000000000) * 2)
digit14 = int(((card % 100000000000000) // 10000000000000) * 2)
digit16 = int(((card % 10000000000000000) // 1000000000000000) * 2)

sum1 = int((digit2 % 10) + (digit2 % 100) / 10)  # adds each digit of the numbers previously selected
sum1 += int((digit4 % 10) + (digit4 % 100) / 10)
sum1 += int((digit6 % 10) + (digit6 % 100) / 10)
sum1 += int((digit8 % 10) + (digit8 % 100) / 10)
sum1 += int((digit10 % 10) + (digit10 % 100) / 10)
sum1 += int((digit12 % 10) + (digit12 % 100) / 10)
sum1 += int((digit14 % 10) + (digit14 % 100) / 10)
sum1 += int((digit16 % 10) + (digit16 % 100) / 10)

digit1 = int(card % 10)  # gets the digits not selected previously
digit3 = int((card % 1000) / 100)
digit5 = int((card % 100000) / 10000)
digit7 = int((card % 10000000) / 1000000)
digit9 = int((card % 1000000000) / 100000000)
digit11 = int((card % 100000000000) / 10000000000)
digit13 = int((card % 10000000000000) / 1000000000000)
digit15 = int((card % 1000000000000000) / 100000000000000)

sum2 = digit1 + digit3 + digit5 + digit7 + digit9 + digit11 + digit13 + digit15  # adds the digits that were not added previously

sumTOT = sum1 + sum2  # adds the first sum and the second sum

card_start = card // (pow(10, (card_len - 2)))  # gets the first 2 digits of the credit card number

if sumTOT % 10 != 0:  # if the last digit of sumTOT is not 0 then the card is invalid

    print("INVALID")
    exit(0)

elif card_start == 34 or card_start == 37:  # checks requierments for amex

    if card_len == 15:
    
        print("AMEX")
    
elif card_start == 51 or card_start == 52 or card_start == 53 or card_start == 54 or card_start == 55:  # checks requierments for mastercard

    if card_len == 16:
        
        print("MASTERCARD")
        
elif (card_start // 10) == 4: # checks requierments for visa

    if card_len == 13 or card_len == 14 or card_len == 15 or card_len == 16:
    
        print("VISA")
        
else:  # any other case is a invalid card
    
        print("INVALID")
        exit(0)