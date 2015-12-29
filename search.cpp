#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cassert>

#include "common.hpp"

using namespace std;
unsigned int n;
pair<int, int> count(int * seq, int * C , int ** occ , int * pattern, int p)
{
    int c = pattern[p - 1];
    int i = p - 1;
    int sp = C[c] + 1 -1;
    int ep = C[c + 1] -1;
    while (sp <= ep && i >= 1)
    {
        c = pattern[i - 1];
        sp = C[c] + occ[c][sp] + 1 -1;
        ep = C[c] + occ[c][ep + 1] -1;
        --i;
    }
    if (ep < sp)
    {
        fprintf(stderr, "[INFO] %s\n", "Pattern not found.");
        return pair<int, int>(0, 0);
    }
    else
    {
        fprintf(stderr, "[INFO] Result: %d, sp = %d, ep = %d\n", ep - sp + 1 , sp  ,ep);
        return pair<int, int>(sp, ep);
    }
}
int main(int argc, char ** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input file> <index file>\n" , argv[0]);
        return 1;
    }

    /* read subject string */
    fprintf(stderr, "[INFO] %s\n", "Loading original sequence.");
    FILE * finput = fopen(argv[1], "r");
    if (!finput)
    {
        perror("[FATAL] open input file");
        return 2;
    }
    char buf[255];
    fgets(buf, 255 , finput);
    sscanf(buf, "%u" , &n);
    char * str = (char *) calloc( n + 1 , sizeof(char) );
    fgets(str, n + 1, finput);
    fclose(finput);
    int * istr = transform_to_int(str, n);
    assert(istr[n] == 1);
    free(str);
    str = NULL;

    /* read bwt result */
    fprintf(stderr, "[INFO] %s\n", "Loading BWT-transformed.");
    FILE * findex = fopen(argv[2], "rb");
    if (!findex)
    {
        perror("[FATAL] open index file");
        return 2;
    }
    int * sa =  (int *) calloc( n + 1 , sizeof(int) );
    int * seq = (int *) calloc( n + 1 , sizeof(int) );
    fread(sa, sizeof(int) , n + 1 , findex);
    fclose(findex);
    for (int i = 0 ; i < n + 1 ; ++i)
        seq[i] = istr[ (sa[i] + (n+1) - 1) % (n+1) ];

    /* creating FP index */
    fprintf(stderr, "[INFO] %s\n", "Creating index.");
    int ** occ = (int **) calloc( 6 , sizeof(int *) );
    for (int i = 1 ; i <= 5 ; ++i)
        occ[i] = (int *) calloc( n + 2 , sizeof(int) );
    for (int j = 1; j <= 5 ; ++j)
        for (int i = 0 ; i < n + 1 ; ++i)
        {
            occ[ j ][i + 1] = occ[ j ][i];
            if (j == seq[i])
                ++occ[j][i + 1];
        }
    int * c = (int *) calloc( 7 , sizeof(int));
    for (int i = 2 ; i <= 6 ; ++i)
        c[i] = c[i - 1] + occ[i - 1][n + 1];
    fprintf(stderr, "[INFO] %s\n", "Ready for queries.");

    char * input = (char* ) malloc(8192);
	while (gets(input))
	{
	    unsigned int p_len = strlen(input);
	    int * p = transform_to_int(input, p_len);
	    pair<int, int> ret = count(seq, c , occ, p, p_len);
	    if (ret.first)
	    {
	        int * occurences = (int *) calloc(ret.second - ret.first + 1, sizeof(int));
	        int * op = occurences;
	        printf("%d Occurrence(s): ", ret.second - ret.first + 1);
	        for (int i = ret.first ; i <= ret.second ; ++i)
	        {
	            *op++ = sa[i];
	        }
	        int * p_end = op;
	        sort(occurences , p_end);
	        for (op = occurences ; op != p_end ; ++op)
	            printf(op == occurences?"%d" : ", %d", *op);
	        printf("\n");
	    } else {
	    	printf("No occurences found.");
	    }
	    free(p);
	}
    return 0;
}
