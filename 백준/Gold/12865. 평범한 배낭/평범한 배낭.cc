#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
vector<pair<int, int>> items;
vector<vector<int>> dp;

void input() {
  cin >> N >> K;
  
  items.resize(N + 1, pair<int, int>(0, 0));
  dp.resize(N + 1, vector<int>(K + 1, 0));

  for (int i = 1; i <= N; ++i) {
    cin >> items[i].first >> items[i].second; // weight, value
  }
}

void solve() {
  for (int i = 1; i <= N; i++) {
    for (int w = 1; w <= K; w++) {
      if (w >= items[i].first) {
        dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i].first] + items[i].second);
      } else {
        dp[i][w] = dp[i - 1][w];
      }
    }
  }

  cout << dp[N][K];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  input();
  solve();

  return 0;
}