#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

int main(int argc, char ** argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <input file> <index file>\n" , argv[0]);
		return 1;
	}
	return 0;
}
