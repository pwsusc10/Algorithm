#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_SIZE 10000

using namespace std;

int n;
double m;
vector<pair<int, int> > arr; // first: calories, second: price
vector<int> dp;

void clear_data(){
  arr.clear();
  dp.clear();
}

void input_data(){
  clear_data();
  
  dp.resize(MAX_SIZE + 1, 0);

  int calories;
  double price;

  for(int i = 0; i < n; i++){
    cin >> calories >> price;
    int cnt = (int)(m / price + 0.5f);
    for(int j = cnt; j > 0; j >>= 1){
      int package = j - (j >> 1);
      arr.push_back(make_pair(calories * package, (int)(price * 100.0 + 0.5f) * package));
    }
  }
}

void solution(){
  for(int i = 0; i < arr.size(); i++){
    for(int j = (int)(m * 100.0 + 0.5f); j >= arr[i].second; j--){
      dp[j] = max(dp[j], dp[j - arr[i].second] + arr[i].first);
    }
  }

  cout << dp[(int)(m * 100.0 + 0.05f)] << "\n";
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  while(true){
    cin >> n >> m;
    if(n == 0 && m == 0)
      break;

    input_data();

    solution();
  }

  return 0;
}