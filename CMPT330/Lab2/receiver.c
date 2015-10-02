//
//  Tyler Kuipers
//  120065
// 
//  receiver.c
//

#include "common.h"
void printUsage(char* pname){
	printf("USAGE %s [-­v] outputFile\n", pname);
}
void chopN(char *str, size_t n)
{
		if(n == 0 || str == 0){
			return;
		}
		size_t len = strlen(str);
		if (n > len)
				return;
		memmove(str, str+n, len - n + 1);
}





int main(int argc, char *argv[]) {
	int debugging = 0;
	char* location = malloc(3000);
	if(argv[1]){
		if(strcmp(argv[1], "-v") == 0){
			debugging = 1;
		}
	}
	else{
		printUsage(argv[0]);
		return 1;
	}


	if(debugging){
		if(argv[2]){
			strcpy(location, argv[2]);
			if(debugging){
				printf("Location: %s\n", location);
			}
		}
		else{
			printUsage(argv[0]);
			return 1;
		}
	}
	else{
		strcpy(location, argv[1]);
		if(argv[2]){
			printUsage(argv[0]);
			return 1;
		}
		if(debugging){
			printf("Location: %s\n", location);
		}
	}

	FILE *fp;
	char file_type[400];
	fp = popen("ps -eF --cols 3000| grep \"./sender\" | sed -r 's/^.{72}//' | sed 's/\\s.*$//' | grep '[a-zA-Z0-9]'", "r");// | sed 's/\\s.*$//'", "r");// |  grep -P  \"^(/[^/ ]*)+/?$\"", "r");
	/* fp = popen("ps -eF --cols 3000| grep \"./sender\" | sed -r 's/^.{72}//' |  grep -P  \"^/k(/[^/ ]*)+/?$\"", "r"); */
	if (!fp) {
		printf("Failed to run ps command.\n");
		return 1;
	}


	/* printf("The return of the bash command: %s\n", fgets(file_type, sizeof(file_type), fp)); */
	char* firstline = fgets(file_type, sizeof(file_type), fp);
	if(debugging){
		printf("The Location grabbed from the sender: %s\n", firstline);
	}
	if(strcmp(trimwhitespace(firstline), "ender") == 0){
		printf("Looks like the sender isn't running.  Please run the sender before trying to recieve a message\n");
		return 1;
	}
	int c;
	FILE *file;
	char* cleanLoc = malloc(3000);
	strcpy(cleanLoc, firstline);
	firstline = trimwhitespace(cleanLoc);
	file = fopen(firstline, "r");
	FILE *f = fopen(location, "w");
	if (!f) {
		printf("Error opening file for writing.  Do you have write permissions in the directory you are trying to save it in?\n");
		if(debugging){
			printf("the process: %s", location);
		}
		return 1;
	}

	if (file) {
		while ((c = getc(file)) != EOF)
			putc(c, f);
		fclose(file);
	}
	else{
		printf("Could not find the file that you are requesting.  Are the sender an the reciever in the same folder? If not, are you using absolute paths?\n");
		return 1;
	}
	free( cleanLoc);
	pclose(fp);
	return 0;
}
