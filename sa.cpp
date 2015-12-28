#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int N;

void radix_sort(int * str, int * a, int *b, int n, int m)
{
	int* count = (int *) calloc( m + 1 , sizeof (int) );


	for (int i = 0 ; i < n ; ++i)
		++count[str[a[i]]];
	for (int i = 1 ; i <= m ; ++i)
		count[i] += count[i - 1];
	for (int i = n - 1 ; i >= 0 ; --i)
		b[--count[str[a[i]]]] = a[i];

	free(count);
}

void suffix_array(int * str, int * sa , int n , int m)
{
	int * rank = (int *) malloc(sizeof(int) * n);
	int * a = (int *) malloc(sizeof(int) * n);
	int * b = (int *) malloc(sizeof(int) * n);
	for (int i = 0 ; i < n ; ++i)
		rank[i] = i;
	radix_sort(str, rank, sa, n, m);

	rank[sa[0]] = 0;
	for (int i = 1 ; i < n ; ++i)
		rank[sa[i]] = rank[sa[i - 1]] + (str[sa[i]] != str[sa[i - 1]]);
	for (int i = 0 ; i << i < n ; ++i) {
		for (int j = 0 ; j < n ; ++j) {
			a[j] = rank[j] + 1;
			b[j] = j + (1 << i) >= n ? 0 : rank[j + (1 << i)] + 1;
			sa[j] = j;
		}
		radix_sort(b, sa, rank, n, n);
		radix_sort(a, rank, sa, n, n);
		rank[sa[0]] = 0;
		for (int j = 1 ; j < n ; ++j) {
			rank[sa[j]] = rank[sa[j - 1]] + 
			(a[sa[j - 1]] != a[sa[j]] || b[sa[j - 1]] != b[sa[j]]);
		}
	}
	free(rank);
	free(a);
	free(b);
}

void calc_height(int * str, int * sa, int * h, int n)
{
	int * rank = (int *) malloc(sizeof(int) * n);
	int k = 0;
	h[0] = 0;
	for (int i = 0 ; i < n ; ++i)
		rank[sa[i]] = i;
	for (int i = 0 ; i < n ; ++i)
	{
		k = k == 0 ? 0 : k - 1;
		if (rank[i] != 0)
			while (str[i + k] == str[sa[rank[i] - 1] + k])
				++k;
		h[rank[i]] = k;	
	}
}

