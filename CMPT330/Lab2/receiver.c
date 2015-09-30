//
//  YOUR NAME HERE!
//  YOUR ID HERE!
// 
//  receiver.c
//

#include "common.h"
void chopN(char *str, size_t n)
{
    if(n == 0 || str == 0){
    	return;
    }
    size_t len = strlen(str);
    if (n > len)
        return;  // Or: n = len;
    memmove(str, str+n, len - n + 1);
}

char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace(*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}

int main() {
	FILE *fp;
	char file_type[40];
	// filepath = system("ps -ef | grep \"./sender\" | sed -r 's/^.{32}//'");
	fp = popen("ps -eF --cols 3000| grep \"./sender\" | sed -r 's/^.{72}//'", "r");
	if (fp == NULL) {
	    printf("Failed to run ps command\n" );
	    return 1;
	}
	char* firstline = fgets(file_type, sizeof(file_type), fp);
	printf("FIRSTLINE = %s\n", firstline);
	printf("FIRSTLINE AFTER CHOP = %s\n", firstline);

	int c;
	FILE *file;
	printf("FIRSTLINE BEFORE OPEN = %s\n", firstline);
	char* cleanLoc = malloc(3000);
	strcpy(cleanLoc, firstline);
	firstline = trimwhitespace(cleanLoc);
	file = fopen(firstline, "r");
	printf("%s\n", file);
	if (file) {
		printf("FOUND THE FILE\n");
		while ((c = getc(file)) != EOF)
			putchar(c);
		fclose(file);
	}
	else{
		printf("Could not find the file that you are requesting.  Are the sender an the reciever in the same folder? If not, are you using absolute paths?\n");
		perror("Error");
		return 1;
	}
	free( cleanLoc);
	pclose(fp);
	return 0;
}