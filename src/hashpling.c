/*
  Copyright (C) 2018 Mohd Kholid Yaacob (mrharmonies.blogspot.com)
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
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HPVERSION "0.9.1"

#define BUFFER 800*sizeof(char)

int main(int argc, char **argv) {
	FILE *f;

	if(argc==0||argc==1) {
		fprintf(stderr,"%s: No input file. Terminated.\n",argv[0]);
		return 1;
	}

  if (argv[1][0]=='-'){
    if (argv[1][1]=='v'){
      printf("Hashpling v%s.\n\nMade with love by Muhamad Khalid Muzappa Yakub. For license info, execute using '-l' option\n",HPVERSION);
		  return 0;
    }
    else if (argv[1][1]=='l'){
		  printf("Copyright (C) 2018 Mohd Kholid Yaacob (mrharmonies.blogspot.com)\n\n");
		  printf("This source is free software; you can redistribute it and/or modify it under\nthe terms of the GNU General Public License as published by the Free\nSoftware Foundation; either version 2 of the License, or (at your option)\nany later version.\n\n");
		  printf("This code is distributed in the hope that it will be useful, but WITHOUT ANY\nWARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS\nFOR A PARTICULAR PURPOSE.  See the GNU General Public License for more\ndetails.\n\n");
		  printf("A copy of the GNU General Public License is available on the World Wide Web\nat <http://www.gnu.org/copyleft/gpl.html>. You can also obtain it by writing\nto the Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,\nBoston, MA 02110-1335, USA.\n");
		  return 0;
    }
    else if (argv[1][1]=='h'){
      printf("Hashpling v%s.\n\n",HPVERSION);
		  printf("To use, run \"%s <filename> [arg1 arg2 ..]\" in command line.\n\n",argv[0]);
		  printf("Shebang format is #!(interpreter) [interpreter arguments]. The (interpreter)\ncan be absolute path to an interpreter or just an interpreter name if its\nalready in PATH variable.\n");
		  return 0;
    } else {
      fprintf(stderr,"%s: Unrecognized option \"%s\".\n",argv[0],argv[1]);
      return 1;
    }
  }

	char optionstr[BUFFER];
	int i;

	if(argc>1) {
		for (i=2; i<argc; i++) {
			snprintf(optionstr,BUFFER,"%s \"%s\"",optionstr,argv[i]);
		}
	}

	f=fopen(argv[1],"r");
	if (f==0) {
		fprintf(stderr, "%s: File \"%s\" failed to be opened. Sorry.\n",argv[0],argv[1]);
		return 1;
	}

	char s[BUFFER];
	int l=0;

	fgets(s,BUFFER,f);

	while (1) {
		if (s[l]=='\r'||s[l]=='\n'||s[l]==EOF) {
			s[l]='\0';
			break;
		}
		l++;
	}

	fclose(f);

	char launcher[BUFFER];
	char cmd[BUFFER];

	if(s[0]=='#' && s[1]=='!') {
		snprintf(launcher,BUFFER,"%s",s+2);
		snprintf(cmd,BUFFER,"%s \"%s\" %s",launcher,argv[1],optionstr);
		return system(cmd);
	} else {
		fprintf(stderr,"%s: File \"%s\" is not in shebang format.\n",argv[0],argv[1]);
		return 1;
	}
}
