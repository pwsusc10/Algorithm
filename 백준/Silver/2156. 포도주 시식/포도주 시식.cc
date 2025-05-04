#include <stdio.h>
#include <algorithm>
#define MAX 10001
using namespace std;

int n;
int V[MAX];
int dp[MAX];

int main(void)
{
	//포도주 잔 입력받기.
	scanf("%d", &n);

	//포도주 잔의 양 입력받기.
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &V[i]);
	}

	dp[0] = 0;
	dp[1] = V[1];
	dp[2] = V[2];

	for (int i = 1; i <= MAX; i++)
	{
		dp[i] = max({ dp[i - 1], dp[i - 2] + V[i], dp[i - 3] + V[i - 1] + V[i] });
	}

	printf("%d\n", dp[n]);

	return 0;

}