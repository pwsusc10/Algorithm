#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, M, cnt;
int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

struct Point {
  int height;
  pair<int, int> pos;

  bool operator<(const Point& other) const {
    return height < other.height; // Max-heap based on height
  }
};

vector<vector<int>> map;
vector<vector<bool>> visited;
priority_queue<Point> pq;

void input(){
  cin >> N >> M;

  map.resize(N, vector<int>(M));
  visited.resize(N, vector<bool>(M, false));

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      cin >> map[i][j];

      pq.push({map[i][j], {i, j}});
    }
  }
}

void bfs(pair<int, int> cur){
  queue<pair<int, int>> q;
  q.push(cur);

  while(!q.empty()){
    pair<int, int> pos = q.front();
    q.pop();

    if(visited[pos.first][pos.second])
      continue;

    visited[pos.first][pos.second] = true;

    for(int i = 0; i < 8; i++){
      int nx = pos.first + dx[i];
      int ny = pos.second + dy[i];

      if(nx < 0 || nx >= N || ny < 0 || ny >= M)
        continue;

      if(!visited[nx][ny] && map[nx][ny] <= map[pos.first][pos.second]){
        q.push({nx, ny});
      }
    }
  }
}

void solution(){
  while(!pq.empty()){
    Point cur = pq.top();
    pq.pop();

    if(visited[cur.pos.first][cur.pos.second])
      continue;

    cnt++;

    bfs(cur.pos);
  }

  cout << cnt;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  solution();

  return 0;
}