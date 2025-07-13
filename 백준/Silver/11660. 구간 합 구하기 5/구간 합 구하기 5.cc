#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<vector<int> > map;
vector<vector<int> > dp;

void input() {
  cin >> N >> M;
  map.resize(N, vector<int>(N));
  dp.resize(N, vector<int>(N));

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      cin >> map[i][j];

      if(i == 0) {
        if(j == 0) {
          dp[i][j] = map[i][j];
        } else {
          dp[i][j] = dp[i][j-1] + map[i][j];
        }
      } else {
        for(int k = 0; k <= j; k++) 
          dp[i][j] += map[i][k];
        dp[i][j] += dp[i-1][j];
      }

      // cout << dp[i][j] << " ";
    }
    // cout << "\n";
  }
}

void solve() {
  for(int i = 0; i < M; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    x1--; y1--; x2--; y2--;
    cout << dp[x2][y2] - (y1 > 0 ? dp[x2][y1-1] : 0) - (x1 > 0 ? dp[x1-1][y2] : 0) + (x1 > 0 && y1 > 0 ? dp[x1-1][y1-1] : 0) << "\n";
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