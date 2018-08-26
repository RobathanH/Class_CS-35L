#!/usr/bin/python

import random, sys
from argparse import ArgumentParser

class randline:
    def __init__(self, filename1, filename2, unsorted):
        if filename1 == '-' and filename2 == '-':
            print("ERROR: Both files can't be read from std input")
            exit()
        elif filename1 == '-':
            self.lines1 = sys.stdin.readlines()
            f2 = open(filename2, 'r')
            self.lines2 = f2.readlines()
            f2.close()
        elif filename2 == '-':
            f1 = open(filename1, 'r')
            self.lines1 = f1.readlines()
            f1.close()
            self.lines2 = sys.stdin.readlines()
        else:
            f1 = open(filename1, 'r')
            self.lines1 = f1.readlines()
            f1.close()
            f2 = open(filename2, 'r')
            self.lines2 = f2.readlines()
            f2.close()
        
        self.unsorted = unsorted

    #returns 1st line which is earliest in alpha order, and the file which it is from, or the column it should go into
    #Assumes that at least one of the lists is NOT empty - done() returns False
    def chooseline(self):
        if not self.unsorted:
            if len(self.lines1) == 0:
                return self.lines2.pop(0), 2
            elif len(self.lines2) == 0:
                return self.lines1.pop(0), 1
            elif self.lines1[0] < self.lines2[0]:
                return self.lines1.pop(0), 1
            elif self.lines1[0] > self.lines2[0]:
                return self.lines2.pop(0), 2
            else:
                self.lines1.pop(0)
                return self.lines2.pop(0), 3
            return random.choice(self.lines)
        
        else:
            if len(self.lines1) == 0:
                return self.lines2.pop(0), 2
            else:
                j = 0
                while j < len(self.lines2) and self.lines2[j] != self.lines1[0]: 
                    j += 1
                if j == len(self.lines2):
                    return self.lines1.pop(0), 1
                else:
                    self.lines2.pop(j)
                    return self.lines1.pop(0), 3
        
    #returns true if both lists are empty
    def done(self):
        return (len(self.lines1) == 0 and len(self.lines2) == 0)


def main():

    parser = ArgumentParser()
    parser.add_argument("file1")
    parser.add_argument("file2")
    parser.add_argument("-1", action="store_true", dest="suppress1", default=False, help="Suppress column 1, which shows lines only in file 1.")
    parser.add_argument("-2", action="store_true", dest="suppress2", default=False, help="Suppress column 2, which shows lines only in file 2.")
    parser.add_argument("-3", action="store_true", dest="suppress3", default=False, help="Suppress column 3, which shows lines only in file 3.")
    parser.add_argument("-u", action="store_true", dest="unsorted", default=False, help="Input files need not be sorted.")    
    
    args = parser.parse_args()

    try:
        generator = randline(args.file1, args.file2, args.unsorted)
    except IOError as err:
        parser.error("I/O Error: " + err)
    
    
    while not generator.done():
        line, col = generator.chooseline()
        if col == 1 and not args.suppress1:
            sys.stdout.write(line)
        elif col == 2 and not args.suppress2:
            if args.suppress1:
                sys.stdout.write(line)
            else:
                sys.stdout.write("\t" + line)
        elif col == 3 and not args.suppress3:
            if args.suppress1:
                if args.suppress2:
                    sys.stdout.write(line)
                else:
                    sys.stdout.write("\t" + line)
            else:
                if args.suppress2:
                    sys.stdout.write("\t" + line)
                else:
                    sys.stdout.write("\t\t" + line)
            
        
   
if __name__ == "__main__":
    main()
