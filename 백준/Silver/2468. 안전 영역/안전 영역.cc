#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <vector>
#include <algorithm>
#define MAX 100

using namespace std;

bool Isvisited[MAX][MAX];
int Map[MAX][MAX];
int N, num, cnt_Max, cnt;
int M_height, height;
int d_x[4] = {-1, 0, 0, 1};
int d_y[4] = {0, 1, -1, 0};
vector<int> V;

void dfs(int x, int y)
{
	//바다이거나 방문을 이미 했다면 return.
	if(Map[x][y] <= height || Isvisited[x][y] == 1)
		return;

	//육지이지만 방문한 적이 없으므로 방문에 체크한다.
	Isvisited[x][y] = 1;

	for(int i = 0; i < 4; i++)
	{
		int next_x = x + d_x[i];
		int next_y = y + d_y[i];

		if(next_x >= 0 && next_x < MAX && next_y >= 0 && next_y < MAX)
			dfs(next_x, next_y);
	}
}

int main(void)
{
	//지역 크기 입력받기.
	scanf("%d", &N);
		
	//지역의 높이 입력받기.
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			scanf("%d", &num);
			Map[i][j] = num;
			M_height = max(M_height, num);
		}
	}

	height = 0;

	while(height < M_height)
	{
		
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < N; j++)
			{
				//방문을 안한 곳이며 안전한 곳을 다시 dfs에 넣는다.
				if(Isvisited[i][j] == 0 && Map[i][j] > height)
				{
					dfs(i ,j);
					cnt++;
				}
			}
		}
		height++;
		cnt_Max = max(cnt, cnt_Max);
		//초기화.
		cnt = 0;
		memset(Isvisited, 0, sizeof(Isvisited));
	}

	printf("%d\n", cnt_Max);

	return 0;
}
