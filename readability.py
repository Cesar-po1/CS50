from cs50 import get_string

while True:
    
    text = get_string("Text: ")
    
    if text != "" or text != " ":
        break

cont_l = 0.0  # letter counter
letter = 0  # letters
cont_w = 1.0  # word counter
cont_s = 0.0  # sentences counter 
L = 0.0 
S = 0.0
grade = 0

for letter in text:  # letter by letter
    
    if (letter >= 'a' and letter <= 'z') or (letter >= 'A' and letter <= 'Z'):
        cont_l += 1  # couhts letter
        
    if letter == ' ':
        cont_w += 1  # counts words
        
    if letter == '.' or letter == '!' or letter == '?':
        cont_s += 1  # counts sentences
        
L = ((cont_l / cont_w) * 100)  # average number of letters per 100 words in the text

S = ((cont_s / cont_w) * 100)  # average number of sentences per 100 words in the text.

grade = round(0.0588 * L - 0.296 * S - 15.8)  # Coleman-Liau formula

if grade >= 16:
    print("Grade 16+")  # final grade
elif grade < 16 and grade >= 1:
    print("Grade", grade)  # final grade
elif grade < 1:
    print("Before grade 1")  # final grade
    

