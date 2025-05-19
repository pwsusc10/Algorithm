#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#define MOD 1000000007

using namespace std;

long long N;
map<long long, long long> dp;

void input_data() {
  cin >> N;
  dp[0] = 0;
  dp[1] = 1;
  dp[2] = 1;
}

long long get_dp(long long x){
    if(dp[x]) return dp[x];

    long long result;
    if(x % 2 == 0) result = (get_dp(x/2)*(get_dp(x/2+1)+get_dp(x/2-1)))%MOD;
    else result = ((get_dp((x+1)/2) * get_dp((x+1)/2))%MOD)+((get_dp((x-1)/2)*get_dp((x-1)/2))%MOD)%MOD;

    return dp[x] = result%MOD;
}

void solution() {
  get_dp(N);

  cout << dp[N];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  input_data();
  solution();

  return 0;
}