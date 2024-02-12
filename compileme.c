#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* mystery(char* a, char* b, int stringlen) {
	char* newstr = malloc(sizeof(char)*(stringlen+1));
	char* newstrcpy = newstr;
	while(*a) *(newstr++) = 64|31&(*(a++)^*(b++));
	*newstr = 0;
	return newstrcpy;
}

int main() 
{
	char* a = NULL;
	size_t abuflen = 0;
	char* b = NULL;
	size_t bbuflen = 0;
	fprintf(stderr,"%s\n", "Write String 1");
	fflush(stderr);
	ssize_t alen = getline(&a,&abuflen,stdin);
	a[--alen] = 0;
	fprintf(stderr,"%s\n", "Write String 2");
	fflush(stderr);
	ssize_t blen = getline(&b,&bbuflen,stdin);
	b[--blen] = 0;
	if(alen!=blen) {
		printf("%s\n", "Error: String lengths do not match");
		return 1;
	}
	char* result = mystery(a,b,alen);
	fprintf(stderr,"%s\n", "Result is on the next line: ");
	fflush(stderr);
	fprintf(stdout, "%s\n", result); //If you're curious, fprintf to stderr gets piped to a different place than stdout. So this lets us save only the data we care about to the file.
	free(a);
	free(b);
	free(result);
	return 0;
}
