#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_WEIGHT 1000000

using namespace std;

int N, M;
vector<pair<int, int> > items;  // items[i].first = weight, items[i].second = value
vector<int> bags;
vector<vector<int>> dp; // dp[i][j] = 0~i까지 의 물건을 담을 수 있는 max value, j는 weight.
pair<int, double> ans = {1, 0.0f};  // first : idx, second : value

void input_data(){
  cin >> N >> M;

  items.resize(N + 1, pair<int, int>(0, 0));
  bags.resize(M + 1, 0);
  dp.resize(N + 1, vector<int>(MAX_WEIGHT + 1, 0));

  for (int i = 1; i <= N; i++){
    cin >> items[i].first >> items[i].second;
  }
  for (int i = 1; i <= M; i++){
    cin >> bags[i];
  }
}

void get_dp_data(){
  for (int i = 1; i <= N; i++){ // 물건이 0인 경우는 없으므로 1부터 시작
    for (int j = 1; j <= MAX_WEIGHT; j++){
      if (j >= items[i].first) {
        // dp[i-1][j] : i번째 물건을 담지 않는 경우
        // dp[i-1][j - items[i].first] + items[i].second : i번째 물건을 담는 경우
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - items[i].first] + items[i].second);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
}

void get_max_value(){
  for(int i = 1; i <= M; i++) {
    int bag_value = dp[N][bags[i]];
    double bag_efficiency = bag_value / double(bags[i]);

    if (ans.second < bag_efficiency) {
      ans.first = i;
      ans.second = bag_efficiency;
    }
  }
}

void solution(){
  get_dp_data();
  get_max_value();
  cout << ans.first;
}

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  input_data();
  solution();


  return 0;
}