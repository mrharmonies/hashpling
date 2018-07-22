# hashpling
hashpling allows you to **use shebang on non-unix platform**, (eg. on Windows 10, Windows XP or on MSDOS). For more info about shebang, read this wikipedia article on [shebang](https://en.wikipedia.org/wiki/Shebang_(Unix)).

# usage
Just add **#!** followed by **path to interpreter** (works with many famous interpreter including **python, bash, kornshell, perl, lua, nodejs, ruby, instantfpc, etc**) at the very **beginning** of your file and continue writing your code below it. To execute the code, just run 'hp.exe *filename*' on command line.

Tip: If you use windows, just add '.hp' file extension at the end of your filename and associate the extension with hashpling program. So later when you double click the dot-hp file, it will execute automatically. No execution permission is required. For example:

![](https://drive.google.com/uc?id=19t10vXhu90PSn2uAnV0vr08ABcM79UPJ)

Example using python interpreter located in "c:\python\bin\python32", append the path right after shebang, like this "**#!c:\python\bin\python32.exe**":
```
#!c:\python\bin\python32.exe
kmh = int(raw_input("Enter km/h: "))
mph =  0.6214 * kmh
print "Speed:", kmh, "KM/H = ", mph, "MPH"
```
If the interpreter in already in the folder registered in PATH environment variable, then full path is not required, in this case, just use "**#!perl**":
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
# compiling
Hashpling only use standard C library (stdio.h, stdlib.h and string.h). Change directory to "src" folder and just do standard compilation using your C compiler eg, **'gcc -w -o hp.exe hashpling.c'**. As for now, I'm able to compile hashpling on **Windows, DOS, macOS and Ubuntu**.

# more screenshot
![](https://drive.google.com/uc?id=143BAvDgNTuEiYN8SP24b5y-AzvZz6Zm3)

# binaries
I recommend compiling hashpling from source. However you can download precompiled binaries (unmaintained) here:
+ Windows (Mingw32) - <https://goo.gl/3AzZu2>
+ macOS High Sierra (clang) - <https://goo.gl/oeTA15>
+ DOS/DOSBOX (djgpp) - <https://goo.gl/NdztRB>

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
