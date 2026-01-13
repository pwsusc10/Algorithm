#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > map;	// -1 : 청소 한 칸, 0 : 청소하지 않은 빈 칸, 1 : 벽
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
int N, M, curX, curY, d, cnt;

bool existDirty() {
	for (int i = 0; i < 4; i++) {
		int nx = curX + dx[i];
		int ny = curY + dy[i];

		if (ny < 0 || ny >= N || nx < 0 || nx >= M )
			continue;

		// 청소되지 않은 칸을 찾은 경우 return true;
		if (map[ny][nx] == 0)
			return true;
	}

	// 주변에 청소할 칸이 없는 경우 return false;
	return false;
}

bool moveToClean() {
	for (int i = 1; i <= 4; i++) {
		int nd = (4 + d - i) % 4;
		int nx = curX + dx[nd];
		int ny = curY + dy[nd];

		if (ny < 0 || ny >= N || nx < 0 || nx >= M)
			continue;

		if (map[ny][nx] == 0) {
			d = nd;
			curY = ny;
			curX = nx;
			return true;
		}
	}
	return false;
}

void startClean() {
	while (true) {
		// 현재 칸이 청소하지 않은 곳이라면 청소.
		if (map[curY][curX] == 0) {
			//cout << "청소한 곳 : ny : " << curY << ", nx : " << curX <<  ", dir : " << d << endl;
			cnt++;
			map[curY][curX] = -1;
		}

		// 주변에 청소할 곳이 있는 지 체크.
		if (existDirty()) {	// 청소할 곳이 있다면.
			if (moveToClean()) {
				continue;
			}
			else {
				cout << "error\n";
				break;
			}
		}
		else {	// 청소할 곳이 없다면.
			// 후진할 곳 체크.
			int nd = (d + 2) % 4;
			int nx = curX + dx[nd];
			int ny = curY + dy[nd];

			// 경계를 넘거나, 벽인 경우 break.
			if (ny < 0 || ny >= N || nx < 0 || nx >= M)
				break;
			else if (map[ny][nx] == 1)
				break;

			// 후진.
			curX = nx;
			curY = ny;
		}
	}
}

int main() {
	cin >> N >> M;
	cin >> curY >> curX >> d;

	map.resize(N, vector<int>(M));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			cin >> map[i][j];
	}

	startClean();

	cout << cnt;

	return 0;
}