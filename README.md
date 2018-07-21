# hashpling
hashpling allows you to **use shebang on non-unix platform**, for example, on Windows or DOS. Just add **#!** followed by **path to interpreter** (works with many famous interpreter including **python, perl, lua, nodejs, ruby, instantfpc, etc**) at the very **beginning** of your file and continue writing your code below it. For example:

![](https://drive.google.com/uc?id=19t10vXhu90PSn2uAnV0vr08ABcM79UPJ)

if the interpreter in already in the folder registered in PATH environment variable, then full path is not required, for example:
```
#!perl
print "Hello, world!\n";
print qq=Did you say "Hello?"\n=;
```
To execute the code, just run 'hp.exe *filename*' on command line. Or if you use windows, just add '.hp' file extension at the end of your filename and associate the extension with hashpling program. So later when you double click the dot-hp file, it will execute automatically. No execution permission is required.
    
# compiling
Hashpling only use standard C library (stdio.h, stdlib.h and string.h). Change directory to "src" folder and just do standard compilation using your C compiler eg, **'gcc -w -o hp.exe hashpling.c'**. As for now, I'm able to compile hashpling on **Windows, DOS, macOS and Ubuntu**.

# more screenshot
![](https://drive.google.com/uc?id=143BAvDgNTuEiYN8SP24b5y-AzvZz6Zm3)

# download precompiled binaries (unmaintained)
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
