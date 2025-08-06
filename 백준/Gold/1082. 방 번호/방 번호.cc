#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> values(51, -1); // index : 가격, value : 숫자
vector<string> dp(51, ""); // dp[i] : i가격에 대한 최대 숫자
int N, M;

void input() {
  cin >> N;

  int value;

  // 중복된 값 제거, values[i]는 항상 최대값을 유지
  for(int i = 0; i < N; i++) {
    cin >> value;
    if(values[value] < i)
      values[value] = i;
  }

  cin >> M;
}

string calculate_number(string prev, string to_add, string cur) {
  // 두 숫자를 이어붙여서 더 큰 숫자를 만들어야 함
  string option1 = prev + to_add;
  if(prev == "0")
    option1 = to_add; // 0을 앞에 붙이는 경우는 무시

  string option2 = to_add + prev;
  if(to_add == "0")
    option2 = prev; // 0을 앞에 붙이는 경우는 무시

  if(option1.length() > cur.length())
    return max(option1, option2);
  else if(option1.length() < cur.length())
    return cur;
  else
    return max({cur, option1, option2});
}

void solution() {
  for(int i = 1; i <= M; i++) {
    dp[i] = dp[i - 1]; // 이전 가격의 최대 숫자
    
    
    // if(i == 13)
    //   cout << "Debugging at price 13: " << dp[i] << endl; // 디버깅용 출력


    for(int j = 0; j <= i; j++) {
      if(values[j] == -1)
        continue; // 해당 가격에 대한 숫자가 없는 경우
      
      string number = to_string(values[j]);
      string new_number = calculate_number(dp[i - j], number, dp[i]);

      dp[i] = new_number; // 현재 가격 i에 대한 최대 숫자 업데이트
    }
  }

  // for(int i = 0; i <= M; i++) {
  //   cout << i << " : " << dp[i] << endl; // 디버깅용 출력
  // }
  cout << dp[M];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  input();
  solution();

  return 0;
}