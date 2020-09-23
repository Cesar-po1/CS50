# TODO
import cs50
import csv
from sys import argv

if len(argv) != 2:
    print('Usage: 2 command-line agruments')
    exit(1)

db = cs50.SQL("sqlite:///students.db")  # database
with open(argv[1], 'r') as file:
    reader = csv.DictReader(file)  # readsfile
    for row in reader:
        names = row['name'].split()  # for middle name
        if len(names) == 3:
            first = names[0]
            middle = names[1]
            last = names[2]
        elif len(names) == 2:
            first = names[0]
            middle = None
            last = names[1]
        house = row['house']
        birth = row['birth']
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?,?,?,?,?)",
                   first, middle, last, house, birth)  # query
        