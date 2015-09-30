//
//  YOUR NAME HERE!
//  YOUR ID HERE!
// 
//  sender.c
//

#include "common.h"
void printUsage(char* pname){
	printf("USAGE %s [-­v] inputFile\n", pname);
}
int main(int argc, char *argv[]) {
	// argv[0][5] = 65;
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
	// char* cleanLocation = malloc(3000);
	// strcpy(cleanLocation, location);
	// char* string = (char*)malloc(3000);
	char kdkdk[] = {'B', 'I', 'G', '\0'};
	char * string =  strcat(argv[0],  location);
	printf("Location Name = %s\n", location);
	// printf("CleanLocation Name = %s\n", cleanLocation);
	printf("Process Name = %s\n", string);
	prctl(PR_SET_NAME, string);
	if( access( location, F_OK ) != -1 ) {
	    // file exists
	    printf("Found File\n");
	} else {
		printf("Sorry, I could not find the file you are requesting\n");
		return 1;
	    // file doesn't exist
	}
	free(location);
	sleep(10);
	// printf("%s", argv[0]);
	// free(location);
}
// int main() {
	// return 0;
// }