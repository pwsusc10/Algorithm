#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int M, N, K;
vector<vector<int> > map;
vector<int> areas;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};


void input() {
  cin >> M >> N >> K;

  map.resize(N, vector<int>(M, 0));

  for(int i = 0; i < K; i++) {
    int x1, y1, x2, y2;
    cin >> y1 >> x1 >> y2 >> x2;

    if(x1 > x2) swap(x1, x2);
    if(y1 > y2) swap(y1, y2);

    for(int j = y1; j < y2; j++) {
      for(int k = x1; k < x2; k++) {
        map[j][k] = 1;
      }
    }
  }
}

void bfs(int startY, int startX) {
  vector<pair<int, int> > q;

  q.push_back({startY, startX});
  int area = 0;
  map[startY][startX] = 1;
  area++;

  while(!q.empty()) {
    pair<int, int> current = q.back();
    q.pop_back();

    for(int i = 0; i < 4; i++) {
      int nextY = current.first + dy[i];
      int nextX = current.second + dx[i];

      if(nextY < 0 || nextY >= N || nextX < 0 || nextX >= M) 
        continue;
      else if(map[nextY][nextX] == 1) 
        continue;
      map[nextY][nextX] = 1;
      area++;
      q.push_back({nextY, nextX});
    }
  }

  areas.push_back(area);
}

void solve() {
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      // cout << map[i][j] << " ";
      if(map[i][j] == 0) {
        bfs(i, j);
        // cout << "bfs(" << i << ", " << j << ")\n";
      }
    }
    // cout << "\n";
  }

  sort(areas.begin(), areas.end());

  cout << areas.size() << "\n";
  for(int i = 0; i < areas.size(); i++) {
    cout << areas[i] << " ";
  }
}

int main(){
  ios:: sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  solve();

  return 0;
}