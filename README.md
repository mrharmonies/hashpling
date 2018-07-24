# hashpling
Hashpling allows you to **use shebang on non-unix platform**, (eg. on Windows 10, Windows XP or on MSDOS). For more info about shebang, read this wikipedia article on [shebang](https://en.wikipedia.org/wiki/Shebang_(Unix)). Hashpling is **very fast** and **portable** because it is written in **C** and following **ANSI C** language dialect. 

# usage
Just add **#!** followed by **path to interpreter** (works with many famous interpreter including **python, bash, kornshell, perl, lua, nodejs, ruby, gnuplot, instantfpc, etc**) at the very **beginning** of your file and continue writing your code below it. To execute the code, just run **'hp.exe *filename*'** on command line.

![](https://drive.google.com/uc?id=19t10vXhu90PSn2uAnV0vr08ABcM79UPJ)

Tip: If you use windows, just add '.hp' file extension at the end of your filename and associate the extension with hashpling program. So later when you double click the dot-hp file, it will execute automatically. No execution permission is required. 

Example using python interpreter located in "**c:\python\bin\python32**", append the path right after shebang, like this "**#!c:\python\bin\python32.exe**":
```
#!c:\python\bin\python32.exe
kmh = int(raw_input("Enter km/h: "))
mph =  0.6214 * kmh
print "Speed:", kmh, "KM/H = ", mph, "MPH"
```
If the interpreter in already in the folder registered in **PATH** environment variable, then full path is not required, in this case, just use "**#!perl**":
```
#!perl
print "Hello, world!\n";
print qq=Did you say "Hello?"\n=;
```
Using hashpling on macOS, linux or other UNIX variant? Shebang is already in the heart of every UNIX system, but just to show hashpling works everywhere, heres another example that works on UNIX-like platform:
```
#!/usr/bin/python
friends = ['john', 'pat', 'gary', 'michael']
for i, name in enumerate(friends):
    print "iteration {iteration} is {name}".format(iteration=i, name=name)
```
```
#!instantfpc
// instantfpc folder is registered in PATH environment variables, so full path is not required.
program params;
var
  i: Integer;
begin
  for i:=0 to ParamCount do writeln(ParamStr(i));
end.
```
Even using '**/usr/bin/env**' works!
```
#!/usr/bin/env bash
echo "Hello world"
```
Passing arguments to script is as usual, for example executing this script with "**hp namearg.sh _audrey hepburn_**" will produce this output
```
$ hp namearg.sh audrey hepburn
My first name is audrey
My surname is hepburn
Total number of arguments is 2
```
and here is the bash script (namearg.sh)
```
#!/bin/bash
# example of using arguments to a script
echo "My first name is $1"
echo "My surname is $2"
echo "Total number of arguments is $#" 
```
hashpling can also **run on a http server**. In this example I'm using **[tinyweb](https://www.ritlabs.com/en/products/tinyweb/)**. After placing this Lua script (named x.hp) in "**cgi-bin**":
```
#!C:\www\root\cgi-bin\lua53

print("Content-type: text/html\n\n");
print("<HTML>\n");
print( "<HEAD><TITLE>hashpling on HTTP server!</TITLE></HEAD>\n");
print("<BODY>\n");
print("<H1>hashpling running on HTTP server!</H1><HR>\n");
print("</BODY></HTML>\n");
```
I can go to **http://localhost/cgi-bin/x.hp** in my favorite browser and get this result:

![](https://drive.google.com/uc?id=1mayTKWP1ytebl8T2tfk-WzzHWMEPXsQs)

# compiling
Hashpling is written in **C** and following **ANSI C** language dialect which makes it very fast and portable. Hashpling only use standard C library (stdio.h, stdlib.h and string.h). To compile, change directory to "src" folder and just do standard compilation using your C compiler eg, **'gcc -ansi -o hp.exe hashpling.c'**. This compilation will produce **one self-contained** executable. The executable requires **no dependency**, so its very **portable**. Compilation is tested sucessfully on **Windows, DOS, macOS and Ubuntu**.

# binaries
I recommend compiling hashpling from source. Compiling hashpling from source is easy if you already have C compiler installed in your system (see "compiling" part above). However you can download precompiled binaries (**unmaintained**) here:
+ **Windows (Mingw32)** - <https://goo.gl/3AzZu2> (v0.1) 
+ **macOS High Sierra (clang)** - <https://goo.gl/oeTA15> (v0.1)
+ **DOS/DOSBOX (djgpp)** - <https://goo.gl/NdztRB> (v0.1)

# more screenshot
![](https://drive.google.com/uc?id=143BAvDgNTuEiYN8SP24b5y-AzvZz6Zm3)

# license
  Copyright (C) 2018 Mohd Kholid Yaacob (<http://mrharmonies.blogspot.com>)
  
  This source is free software; you can redistribute it and/or modify it under
  the terms of the GNU General Public License as published by the Free
  Software Foundation; either version 2 of the License, or (at your option)
  any later version.
  
  
  This code is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
  details.
  
  
  A copy of the GNU General Public License is available on the World Wide Web
  at <http://www.gnu.org/copyleft/gpl.html>. You can also obtain it by writing
  to the Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,
  Boston, MA 02110-1335, USA. 
