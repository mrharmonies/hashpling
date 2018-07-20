#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _HPVERSION_ "0.2"

int main(int argc, char **argv) {
	FILE *f;

	if(argc==1) {
		printf("%s: No input file. Terminated.\n",argv[0]);
		return 0;
	}

	if (!strcmp(argv[1],"-v")) {
		printf("Hashpling v%s. Made with love by Muhamad Khalid Muzappa Yakub.\nhttp://mrharmonies.blogspot.com\n",_HPVERSION_);
		return 0;
	}

	if (!strcmp(argv[1],"-h")) {
		printf("Hashpling v%s.\n",_HPVERSION_);
		printf("To use, run \"%s [filename]\" in command line.\n",argv[0]);
		printf("Shebang format is #!(interpreter) [arguments].\n");
		printf("Interpreter can be absolute path or a program\n");
		printf("name registered in PATH environment variable.\n");
		return 0;
	}

	f=fopen(argv[1],"r");
	if (f==0) {
		printf("%s: File \"%s\" failed to be opened. Sorry.\n",argv[0],argv[1]);
		return 1;
	}
	char s[800];
	int l;
	while (1) {
		s[l]=fgetc(f);
		if (s[l]=='\x0d'||s[l]=='\x0a') // look for CR and LF, which ever comes first. 
		{
			s[l]='\0'; // last char is \0
			break;
		}
		l++;
	}

	fclose(f);

	char* launcher[800],cmd[800],lastchar;
	int c;

	if(s[0]=='#' && s[1]=='!') { // if code is in shebang format
		strncpy(launcher,s+2,strlen(s));
		strcpy(cmd,launcher); 
		strcat(cmd," ");
		strcat(cmd,"\""); 
		strcat(cmd,argv[1]);  
		strcat(cmd,"\"");
		system(cmd);
	} else { // else if not in shebang format
		printf("%s: File \"%s\" is not in shebang format.\n",argv[0],argv[1]);
		return 1;
	}
	return 0;
}
