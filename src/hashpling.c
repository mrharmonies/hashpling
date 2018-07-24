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

#define _HPVERSION_ "0.5"

#define _BUFFER_ 800

int main(int argc, char **argv) {
	FILE *f;

	if(argc==1) {
		printf("%s: No input file. Terminated.\n",argv[0]);
		return 0;
	}

	if (!strcmp(argv[1],"-v")) {
		printf("Hashpling v%s. Made with love by Muhamad Khalid Muzappa Yakub. For license info, execute using '-l' option\n",_HPVERSION_);
		return 0;
	}
	
	if (!strcmp(argv[1],"-l")) {
		printf("Copyright (C) 2018 Mohd Kholid Yaacob (mrharmonies.blogspot.com)\n\n");

		printf("This source is free software; you can redistribute it and/or modify it under\n");
		printf("the terms of the GNU General Public License as published by the Free\n");
		printf("Software Foundation; either version 2 of the License, or (at your option)\n");
		printf("any later version.\n\n");

		printf("This code is distributed in the hope that it will be useful, but WITHOUT ANY\n");
		printf("WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS\n");
		printf("FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more\n");
		printf("details.\n\n");

		printf("A copy of the GNU General Public License is available on the World Wide Web\n");
		printf("at <http://www.gnu.org/copyleft/gpl.html>. You can also obtain it by writing\n");
		printf("to the Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,\n");
		printf("Boston, MA 02110-1335, USA.\n");
		return 0;
	}

	if (!strcmp(argv[1],"-h")) {
		printf("Hashpling v%s.\n",_HPVERSION_);
		printf("To use, run \"%s <filename> [arg1 arg2 ..]\" in command line.\n",argv[0]);
		printf("Shebang format is #!(interpreter) [interpreter arguments].\n");
		printf("(interpreter) can be absolute path to an interpreter or just an interpreter name if its already in PATH variable.\n");
		return 0;
	}
	
	char *optionstr=malloc(sizeof(char) * _BUFFER_);
	int i;
	strcpy(optionstr,"");
	if(argc>1) { 
		for (i=2;i<argc;i++) {
			strcat(optionstr, " ");	
			strcat(optionstr,"\"");
			strcat(optionstr, argv[i]);
			strcat(optionstr,"\"");
		}
	}

	f=fopen(argv[1],"r");
	if (f==0) {
		printf("%s: File \"%s\" failed to be opened. Sorry.\n",argv[0],argv[1]);
		return 1;
	}

	char *s=malloc(sizeof(char) * _BUFFER_);
	int l=0;
	
	while (1) {
		s[l]=fgetc(f);
		if (s[l]=='\x0d'||s[l]=='\x0a') 
		{
			s[l]='\0'; 
			break;
		}
		l++;
	}

	fclose(f);
	free(f);

	char *launcher=malloc(sizeof(char) * _BUFFER_);
	char *cmd=malloc(sizeof(char) * _BUFFER_);

	if(s[0]=='#' && s[1]=='!') { 
		strncpy(launcher,s+2,strlen(s));
		strcpy(cmd,launcher); 
		strcat(cmd," ");
		strcat(cmd,"\""); 
		strcat(cmd,argv[1]);  
		strcat(cmd,"\"");
		strcat(cmd,optionstr); 
		/*system(cmd);*/
		printf("command is %s",cmd);
		free(s);
		free(cmd);
		free(launcher);
		free(optionstr);
	} else { 
		printf("%s: File \"%s\" is not in shebang format.\n",argv[0],argv[1]);
		return 1;
	}
	return 0;
}
