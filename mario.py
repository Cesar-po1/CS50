from cs50 import get_int

i, j, k, height = 0, 0, 0, 0 #declare variables

while True:
    height = get_int("Height: ") #asks for height
    if height < 9 and height > 0:
        break

for i in range (0, height, 1): #itinerates rows
    for k in range (height-1, -1, -1):  #1st piramid colums
        if i < k:
            print(" ", end="")
        else:
            print("#", end="")
    print("  ", end="") #second piramid colums
    for j in range (-1, height - 1, 1):
        if i > j:
            print("#", end="")
        else:
            print(" ", end="")
    print() #change 