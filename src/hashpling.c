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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

/* Platform-specific headers */
#ifdef _WIN32
    /* Windows (MSVC or MinGW) */
    #include <process.h>
    #include <io.h>
    #define access _access
    #define F_OK 0
#elif defined(__DJGPP__)
    /* DOS (djgpp) */
    #include <process.h>
    #include <unistd.h>
#else
    /* Unix-like systems (Linux, macOS, Haiku, etc.) */
    #include <unistd.h>
#endif

#define HPVERSION "0.9"
#define MAX_LINE_SIZE 4096
#define MAX_ARGS 256

/*
 * Validates that a string contains only safe characters for an interpreter path.
 * Rejects any shell metacharacters that could be used for command injection.
 */
static int is_safe_interpreter_path(const char *str) {
	const char *dangerous = ";|&$`\"'<>{}[]()!\n\r\\*?\t";
	
	if (str == NULL || str[0] == '\0') {
		return 0;
	}
	
	/* Check for dangerous characters */
	if (strpbrk(str, dangerous) != NULL) {
		return 0;
	}
	
	/* Check for path traversal attempts */
	if (strstr(str, "..") != NULL) {
		return 0;
	}
	

	
	return 1;
}

/*
 * Trims leading and trailing whitespace from a string in place.
 * Returns pointer to the trimmed string.
 */
static char *trim_whitespace(char *str) {
	char *end;
	
	if (str == NULL) {
		return NULL;
	}
	
	/* Trim leading whitespace */
	while (isspace((unsigned char)*str)) {
		str++;
	}
	
	if (*str == '\0') {
		return str;
	}
	
	/* Trim trailing whitespace */
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) {
		end--;
	}
	end[1] = '\0';
	
	return str;
}

/*
 * Parses the shebang line into interpreter and arguments.
 * Returns 0 on success, -1 on failure.
 * The args array is populated with null-terminated strings.
 * argc will be set to the number of arguments.
 */
static int parse_shebang(const char *line, char *interpreter, size_t interp_size,
                         char **args, int *argc, int max_args) {
	const char *p;
	char *token;
	char line_copy[MAX_LINE_SIZE];
	int count = 0;
	
	if (line == NULL || interpreter == NULL || args == NULL || argc == NULL) {
		return -1;
	}
	
	/* Copy line for tokenization */
	if (strlen(line) >= sizeof(line_copy) - 1) {
		return -1;
	}
	strncpy(line_copy, line, sizeof(line_copy) - 1);
	line_copy[sizeof(line_copy) - 1] = '\0';
	
	/* Skip the #! prefix */
	p = line + 2;
	while (isspace((unsigned char)*p)) {
		p++;
	}
	
	if (*p == '\0') {
		return -1;
	}
	
	/* Extract interpreter (first token) */
	token = strtok(line_copy + (p - line), " \t");
	if (token == NULL) {
		return -1;
	}
	
	token = trim_whitespace(token);
	if (!is_safe_interpreter_path(token)) {
		fprintf(stderr, "hashpling: Interpreter path contains unsafe characters\n");
		return -1;
	}
	
	if (strlen(token) >= interp_size - 1) {
		return -1;
	}
	strncpy(interpreter, token, interp_size - 1);
	interpreter[interp_size - 1] = '\0';
	
	if (count < max_args) {
		args[count++] = interpreter;
	}
	
	/* Extract additional interpreter arguments */
	while ((token = strtok(NULL, " \t")) != NULL) {
		token = trim_whitespace(token);
		
		if (token[0] == '\0') {
			continue;
		}
		
		if (!is_safe_interpreter_path(token)) {
			fprintf(stderr, "hashpling: Interpreter argument contains unsafe characters\n");
			return -1;
		}
		
		if (count >= max_args) {
			fprintf(stderr, "hashpling: Too many interpreter arguments\n");
			return -1;
		}
		
		args[count] = malloc(strlen(token) + 1);
		if (args[count] == NULL) {
			/* Clean up previously allocated memory */
			for (int j = 1; j < count; j++) {
				free(args[j]);
			}
			return -1;
		}
		strncpy(args[count], token, strlen(token) + 1);
		count++;
	}
	
	*argc = count;
	return 0;
}

/*
 * Platform-specific function to execute the interpreter.
 * This replaces the process with the interpreter (exec-like behavior).
 * Returns -1 on failure, or does not return on success.
 */
static int execute_interpreter(const char *interpreter, char **args) {
#ifdef _WIN32
	/* Windows: Use _spawnvp with _P_OVERLAY to replace current process */
	int result;
	result = _spawnvp(_P_OVERLAY, interpreter, args);
	/* If we get here, _spawnvp failed */
	return result;
#elif defined(__DJGPP__)
	/* DOS (djgpp): Use spawnvp with P_OVERLAY */
	int result;
	result = spawnvp(P_OVERLAY, interpreter, args);
	/* If we get here, spawnvp failed */
	return result;
#else
	/* Unix-like: Use execvp to replace current process */
	execvp(interpreter, args);
	/* If we get here, execvp failed */
	return -1;
#endif
}

int main(int argc, char **argv) {
	FILE *f;
	char line[MAX_LINE_SIZE];
	char interpreter[MAX_LINE_SIZE];
	char *exec_args[MAX_ARGS];
	int i;
	int interp_argc = 0;
	int total_args = 0;
	size_t line_len;
	
	/* argc is always at least 1 in standard C */
	if (argc < 2) {
		fprintf(stderr, "hashpling: No input file. Terminated.\n");
		return 1;
	}
	
	if (argv[1][0] == '-') {
		if (argv[1][1] == 'v' && argv[1][2] == '\0') {
			printf("Hashpling v%s.\n\nMade with love by Muhamad Khalid Muzappa Yakub. "
			       "For license info, execute using '-l' option\n", HPVERSION);
			return 0;
		} else if (argv[1][1] == 'l' && argv[1][2] == '\0') {
			printf("Copyright (C) 2018 Mohd Kholid Yaacob (mrharmonies.blogspot.com)\n\n");
			printf("This source is free software; you can redistribute it and/or modify it under\n"
			       "the terms of the GNU General Public License as published by the Free\n"
			       "Software Foundation; either version 2 of the License, or (at your option)\n"
			       "any later version.\n\n");
			printf("This code is distributed in the hope that it will be useful, but WITHOUT ANY\n"
			       "WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS\n"
			       "FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more\n"
			       "details.\n\n");
			printf("A copy of the GNU General Public License is available on the World Wide Web\n"
			       "at <http://www.gnu.org/copyleft/gpl.html>. You can also obtain it by writing\n"
			       "to the Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,\n"
			       "Boston, MA 02110-1335, USA.\n");
			return 0;
		} else if (argv[1][1] == 'h' && argv[1][2] == '\0') {
			printf("Hashpling v%s.\n\n", HPVERSION);
			printf("To use, run \"hashpling <filename> [arg1 arg2 ..]\" in command line.\n\n");
			printf("Shebang format is #!(interpreter) [interpreter arguments]. The (interpreter)\n"
			       "can be absolute path to an interpreter or just an interpreter name if its\n"
			       "already in PATH variable.\n");
			return 0;
		} else {
			fprintf(stderr, "hashpling: Unrecognized option \"%s\".\n", argv[1]);
			return 1;
		}
	}
	
	f = fopen(argv[1], "r");
	if (f == NULL) {
		fprintf(stderr, "hashpling: File \"%s\" failed to be opened: %s\n", 
		        argv[1], strerror(errno));
		return 1;
	}
	
	/* Read first line */
	if (fgets(line, sizeof(line), f) == NULL) {
		fprintf(stderr, "hashpling: Failed to read from file \"%s\": %s\n",
		        argv[1], ferror(f) ? strerror(errno) : "empty file");
		fclose(f);
		return 1;
	}
	
	fclose(f);
	
	/* Remove trailing newline/carriage return with bounds checking */
	line_len = strlen(line);
	if (line_len > 0) {
		if (line[line_len - 1] == '\n') {
			line[line_len - 1] = '\0';
			line_len--;
		}
		if (line_len > 0 && line[line_len - 1] == '\r') {
			line[line_len - 1] = '\0';
		}
	}
	
	/* Check for shebang */
	if (line[0] != '#' || line[1] != '!') {
		fprintf(stderr, "hashpling: File \"%s\" is not in shebang format.\n", argv[1]);
		return 1;
	}
	
	/* Parse the shebang line */
	memset(exec_args, 0, sizeof(exec_args));
	if (parse_shebang(line, interpreter, sizeof(interpreter), 
	                  exec_args, &interp_argc, MAX_ARGS - argc - 1) != 0) {
		fprintf(stderr, "hashpling: Failed to parse shebang line\n");
		/* Free allocated args */
		for (i = 1; i < interp_argc; i++) {
			if (exec_args[i] != NULL) {
				free(exec_args[i]);
			}
		}
		return 1;
	}
	
	/* Add the script file as the next argument */
	total_args = interp_argc;
	exec_args[total_args++] = argv[1];
	
	/* Add remaining arguments from command line */
	for (i = 2; i < argc && total_args < MAX_ARGS - 1; i++) {
		exec_args[total_args++] = argv[i];
	}
	exec_args[total_args] = NULL;
	
	/* Execute the interpreter with the script and arguments */
	(void)execute_interpreter(interpreter, exec_args);
	
	/* If we get here, execution failed */
	fprintf(stderr, "hashpling: Failed to execute \"%s\": %s\n", 
	        interpreter, strerror(errno));
	
	/* Free allocated args */
	for (i = 1; i < interp_argc; i++) {
		if (exec_args[i] != NULL) {
			free(exec_args[i]);
		}
	}
	
	return 127; /* Standard exit code for command not found */
}
