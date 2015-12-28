#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

void suffix_array(int * str, int * sa , int n , int m);

unsigned int n;

int * transform_to_int(char * str) {
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
	int * istr = transform_to_int(str);
	assert(istr[n] == 1);
	free(str);
	int * sa =  (int *) calloc( n + 1 , sizeof(int) );
	suffix_array(istr, sa , n + 1,  5);
	fwrite(sa, sizeof(int) , n + 1 , fout);
	fclose(fout);
	free(sa);
	return 0;
	/*
	char buf[1000];
	gets(buf);
	int sa[1000];
	memset(sa , 0 ,sizeof sa);
	int maxc = 0;
	int n = strlen(buf);
	int str[1000];
	for (int i = 0 ; i < n ; ++i)
		str[i] = buf[i], maxc = max(maxc, str[i]);
	suffix_array(str, sa, n , maxc);
	for (int i = 0 ; i < n; ++i)
		cerr << sa[i] << ' ' << ( (char) str[(sa[i] + n - 1) % n] ) << endl;
	return 0;	
	*/
}
