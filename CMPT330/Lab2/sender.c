//
//  Tyler Kuipers
//  120065!
// 
//  sender.c
//

#include "common.h"
void printUsage(char* pname){
	printf("USAGE %s [-­v] inputFile\n", pname);
}
int run(int argc, char* argv[]);
int main(int argc, char *argv[]){
	int id=fork();
	if(id==0){
		return run(argc, argv);
	}
	else{
		return 0;	
	}
}
int run(int argc, char *argv[]) {
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
		printf("Argv[0]: %s\n", argv[0]);
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
	char* cleanerLoc = malloc(3000);
	char* ch = malloc(3000);
	ch="chmod o+r ";
	char* newstring = "readlink -en ";
	strcpy(cleanerLoc, location);
	char *newres = malloc(strlen(newstring)+strlen(cleanerLoc)+1);
	strcpy(newres, newstring);
    strcat(newres, cleanerLoc);
	FILE *fj;
	char file_type[500];
	fj = popen(newres, "r");
	char* firstline = fgets(file_type, sizeof(file_type), fj);
	char * string =  strcat(argv[0],  firstline);
	prctl(PR_SET_NAME, string);
	char *result = malloc(strlen(ch)+strlen(cleanerLoc)+1);
	FILE *fpe;
	if (!fj) {
		printf("Failed to run ps command.\n");
		return 1;
	}


	if(debugging){
		printf("The Location of the file: %s\n", firstline);
	}
	if( access( location, F_OK ) != -1 ) {
		if(debugging){
	    	printf("Found File\n");
		}
    	strcpy(result, ch);
    	strcat(result, cleanerLoc);
		fpe = popen(result, "r");
		if (!fpe) {
			printf("Failed to read the file.\n");
			return 1;
		}
	}
	else {
		printf("Sorry, I could not find the file you are requesting\n");
		return 1;
	}
	free(location);
	sleep(30);
	return 0;
}
