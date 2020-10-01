#include <stdio.h>

int main()
{
	#ifdef DEBUG
	printf("%s\n","DEBUG");
	#endif

	int d;
	scanf("%d", &d);
	printf("\n%d\n", d);
	return 0;
}
