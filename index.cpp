#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cassert>
#include "common.hpp"

using namespace std;

void suffix_array(int * str, int * sa , int n , int m);

unsigned int n;

int main(int argc , char ** argv)
{
	if (argc != 3) {
		fprintf(stderr, "%s\n", "Please specify both input and output file.");
		return 1;
	}

	FILE * fin = fopen(argv[1], "r");
	if (!fin) {
		perror("[FATAL] open input file");
		return 2;
	}
	FILE * fout = fopen(argv[2] , "w");
	if (!fout) {
		perror("[FATAL] open output file");
		return 2;
	}
	char buf[255];
	fgets(buf, 255 , fin);
	sscanf(buf, "%u" , &n);
	char * str = (char *) calloc( n + 1 , sizeof(char) );
	fgets(str, n + 1, fin);
	fprintf(stderr, "Length: %u, first character: %c\n", n, str[0]);
	fclose(fin);
	int * istr = transform_to_int(str, n);
	assert(istr[n] == 1);
	free(str);
	int * sa =  (int *) calloc( n + 1 , sizeof(int) );
	suffix_array(istr, sa , n + 1,  5);
	fwrite(sa, sizeof(int) , n + 1 , fout);
	fclose(fout);
	free(sa);
	return 0;
}
