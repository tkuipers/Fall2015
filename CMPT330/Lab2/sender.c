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
int run(int argc, char* argv[]);
int main(int argc, char *argv[]){
 	int id=fork();
	if(id==0){
		return run(argc, argv);
	}
	else{
		return 0;	
	}
	/* return (int)popen(run(argc, argv), "r"); */
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
	char * string =  strcat(argv[0],  location);
	/* printf("The Process Name is: %s\n", string); */
	prctl(PR_SET_NAME, string);
	if( access( location, F_OK ) != -1 ) {
		if(debugging){
	    	printf("Found File\n");
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
