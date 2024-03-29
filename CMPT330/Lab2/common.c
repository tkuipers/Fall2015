//
//  Tyler Kuipers
//  120065
// 
//  common.c
//  

#include "common.h"

// Takes out whitespace from the beginning and end of the string that is passed in
char *trimwhitespace(char *str)
{
	char *end;
	while(isspace(*str)) str++;

	if(*str == 0)
		return str;

	end = str + strlen(str) - 1;
	while(end > str && isspace(*end)) end--;

	*(end+1) = 0;

	return str;
}
