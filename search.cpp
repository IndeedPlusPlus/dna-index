#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cassert>
#include "common.hpp"

using namespace std;

int main(int argc, char ** argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <input file> <index file>\n" , argv[0]);
		return 1;
	}
	/* read subject string */
	finput = fopen(argv[1], "r");
	if (!finput) {
		perror("[FATAL] open input file");
		return 2;
	}
	char buf[255];
	fgets(buf, 255 , fin);
	sscanf(buf, "%u" , &n);
	char * str = (char *) calloc( n + 1 , sizeof(char) );
	fgets(str, n + 1, fin);
	fclose(finput);
	int * istr = transform_to_int(str, n);
	assert(istr[n] == 1);
	free(str);
	str = NULL;

	/* read bwt result */
	findex = fopen(argv[2], "rb");
	if (!findex) {
		perror("[FATAL] open index file");
		return 2;
	}
	int * sa =  (int *) calloc( n + 1 , sizeof(int) );
	fread(sa, sizeof(int) , n + 1 , findex);
	return 0;
}
