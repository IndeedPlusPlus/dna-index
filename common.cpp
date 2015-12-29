#include <cstdlib>
#include <cstdio>
#include "common.hpp"

int * transform_to_int(char * str, unsigned int &n) {
	int * a = (int *) calloc( n + 1 , sizeof(int) );
	int p = 0;
	for (char * c = str ; *c ; ++c) 
	{
		bool flag = true;
		switch (*c)
		{
			case 'A':
				a[p] = 2;
				break;
			case 'T':
				a[p] = 3;
				break;
			case 'C':
				a[p] = 4;
				break;
			case 'G':
				a[p] = 5;
				break;
			default:
				//fixme: something wrong with the input
				n = p;
				flag = false;
				break;
				fprintf(stderr, "[FATAL] unexpected input: '%c' at %d\n", *c , p);
				abort();
		}
		if (!flag)
			break;
		++p;
	}
	a[p++] = 1;
	return a;
}
