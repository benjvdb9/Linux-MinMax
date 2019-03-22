#include <stdio.h>
#include <stdlib.h>

int t[5] = {1, 2, 3, 6, 8};

int size = sizeof(t)/ sizeof(t[0]);

int main()
{
	printf("%d\n", size);
	return 0;
}
