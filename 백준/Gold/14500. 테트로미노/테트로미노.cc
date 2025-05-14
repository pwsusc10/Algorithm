#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, max_value;
vector<vector<int>> map;
vector<vector<vector<int>>> diagrams = {
  {{1, 1, 1, 1}},
  {{1}, {1}, {1}, {1}},
  {{1, 1}, {1, 1}},
  {{1, 0}, {1, 0}, {1, 1}},
  {{0, 1}, {0, 1}, {1, 1}},
  {{1, 1}, {0, 1}, {0, 1}},
  {{1, 1}, {1, 0}, {1, 0}},
  {{1, 1, 1}, {1, 0, 0}},
  {{1, 0, 0}, {1, 1, 1}},
  {{1, 1, 1}, {0, 0, 1}},
  {{0, 0, 1}, {1, 1, 1}},
  {{1, 0}, {1, 1}, {0, 1}},
  {{0, 1, 1}, {1, 1, 0}},
  {{0, 1}, {1, 1}, {1, 0}},
  {{1, 1, 0}, {0, 1, 1}},
  {{1, 1, 1}, {0, 1, 0}},
  {{0, 1}, {1, 1}, {0, 1}},
  {{0, 1, 0}, {1, 1, 1}},
  {{1, 0}, {1, 1}, {1, 0}}
};

void input_data(){
  cin >> N >> M;
  map.resize(N, vector<int>(M));

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++)
      cin >> map[i][j];
  }
  // cout << "input map\n";
  // for(int i = 0; i < N; i++){
  //   for(int j = 0; j < M; j++)
  //     cout << map[i][j] << " ";
  //   cout << endl;
  // }
}

void calculate_diagram(int y, int x){
  int cur_max = 0;

  for(int i = 0; i < diagrams.size(); i++){
    int sum = 0;
    if(y + diagrams[i].size() > N || x + diagrams[i][0].size() > M)
      continue;
    
    for(int j = 0; j < diagrams[i].size(); j++){
      for(int k = 0; k < diagrams[i][0].size(); k++){
        if(diagrams[i][j][k] == 1)
          sum += map[y + j][x + k];
      }
    }
    cur_max = max(cur_max, sum);
  }
  max_value = max(max_value, cur_max);
}

void solution(){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++)
      calculate_diagram(i, j);
  }

  cout << max_value;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  
  input_data();
  solution();

  return 0;
}