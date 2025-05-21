#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
	int height, up_num, down_num;
	int distance;
	int day = 0;


	scanf("%d %d %d", &up_num, &down_num, &height);

	distance = up_num - down_num;

	day = (height-up_num) / distance;
	day++;
	if ((height- up_num) % distance != 0)
		day++;

	printf("%d", day);

	return 0;
}
