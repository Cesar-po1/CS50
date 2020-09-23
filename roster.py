# TODO
import cs50
from sys import argv

if len(argv) != 2:  
    print('Usage: 2 command-line agruments')   # checks user input
    exit(1)
    
db = cs50.SQL("sqlite:///students.db")  # sets de data base
rows = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", argv[-1])  # query
for name in rows:
    print(name['first'] + ' ' + (name['middle'] + ' 'if name['middle'] !=
                                   None else'') + name['last'] + ',', 'born', name['birth'])  # outpu