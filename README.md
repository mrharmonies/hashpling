# hashpling
hashpling allows you to use shebang - https://en.wikipedia.org/wiki/Shebang_(Unix) on non-unix platform, mainly on Windows and DOS. Just add #! followed by path to interpreter (works with many famous interpreter including python, lua, nodejs, ruby, instantfpc etc) at the very beginning of your file and continue writing your code below it. For example:

![](https://drive.google.com/uc?id=19t10vXhu90PSn2uAnV0vr08ABcM79UPJ)

if the interpreter in already in the folder registered in PATH environment variable, then full path is not required, for example:
```
#!perl
print "Hello, world!\n";
print qq=Did you say "Hello?"\n=;
```
To execute the code, just run 'hp.exe <filename>' on command line. Or if you use windows, just add '.hp' file extension at the end of your filename and associate the extension with hashpling. So later when you double click the dot-hp file, it will execute automatically. No execution permission is required.
    
# compiling
Hashpling only use standard C library (stdio.h, stdlib.h and string.h). Change directory to "src" folder and just do standard compilation using your C compiler eg, 'gcc -o hp.exe hashpling.c'.

# more screenshot
![](https://drive.google.com/uc?id=143BAvDgNTuEiYN8SP24b5y-AzvZz6Zm3)
