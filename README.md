# hashpling
hashpling allows you to use shebang - https://en.wikipedia.org/wiki/Shebang_(Unix) on non-unix platform, mainly on Windows and DOS. Just add #! followed by path to interpreter (works with many famous interpreter including python, lua, nodejs, ruby, instantfpc etc) at the very beginning of your file and continue writing your code below it. For example:
```
#!c:\python32\python
import sys
import random

ans = True

while ans:
    question = raw_input("Ask the magic 8 ball a question: (press enter to quit) ")
    
    answers = random.randint(1,8)
    
    if question == "":
        sys.exit()
    
    elif answers == 1:
        print "It is certain"
    
    elif answers == 2:
        print "Outlook good"
    
    elif answers == 3:
        print "You may rely on it"
    
    elif answers == 4:
        print "Ask again later"
    
    elif answers == 5:
        print "Concentrate and ask again"
    
    elif answers == 6:
        print "Reply hazy, try again"
    
    elif answers == 7:
        print "My reply is no"
    
    elif answers == 8:
        print "My sources say no"

```
if the interpreter in already in the folder registered in PATH environment variable, then full path is not required, for example:
```
#!perl
print "Hello, world!\n";
print qq=Did you say "Hello?"\n=;
```
To execute the code, just run 'hp.exe <filename>' on command line. Or if you use windows, just add '.hp' file extension at the end of your filename and associate the extension with hashpling. So later when you double click the dot-hp file, it will execute automatically. No execution permission is required.
    
# compiling
Hashpling only use standard C library (stdio.h, stdlib.h and string.h). Just do standard compilation using your C compiler eg, 'gcc -o hp.exe hashpling.c'.

# screenshot
![](https://drive.google.com/uc?id=1JpujgvlmMjUqC9DNQqDBGrQOLRq6zosO)
![](https://drive.google.com/uc?id=143BAvDgNTuEiYN8SP24b5y-AzvZz6Zm3)
