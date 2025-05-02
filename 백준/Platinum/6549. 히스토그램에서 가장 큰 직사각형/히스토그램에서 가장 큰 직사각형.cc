#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> arr;
vector<int> max_height_tree;
long long max_width;

// 구간 별 최소 높이의 idx를 구하기 위한 세그먼트 트리
void init_min_height_tree(int node, int st, int en) {
  if (st == en) {
    max_height_tree[node] = st;
    return;
  }
  init_min_height_tree(node * 2, st, (st + en) / 2);
  init_min_height_tree(node * 2 + 1, (st + en) / 2 + 1, en);

  if (arr[max_height_tree[node * 2]] < arr[max_height_tree[node * 2 + 1]])
    max_height_tree[node] = max_height_tree[node * 2];
  else
    max_height_tree[node] = max_height_tree[node * 2 + 1];
}

int get_max_height_idx(int node, int st, int en, int left, int right){
  if(right < st || en < left)
    return 0;
  else if(left <= st && en <= right)
    return max_height_tree[node];
  else if(st == en){
    return max_height_tree[node];
  }
  int l_idx = get_max_height_idx(node * 2, st, (st + en) / 2, left, right);
  int r_idx = get_max_height_idx(node * 2 + 1, (st + en) / 2 + 1, en, left, right);

  if (arr[l_idx] < arr[r_idx])
    return l_idx;
  else
    return r_idx;
}

void clear_data() {
  max_width = 0;
  arr.clear();
  max_height_tree.clear();
}

void input_data() {  
  clear_data();

  arr.resize(N + 1);
  arr[0] = 21e8;
  max_height_tree.resize(4 * N);
  for (int i = 1; i <= N; i++) {
    cin >> arr[i];
  }
  init_min_height_tree(1, 1, N);
}

void solution(int st, int en){
  int h_idx = get_max_height_idx(1, 1, N, st, en);
  long long width = width = (long long)(en - st + 1) * arr[h_idx];
  max_width = max(max_width, width);

  if(st <= h_idx - 1)
    solution(st, h_idx - 1);
  if(h_idx + 1 <= en)
    solution(h_idx + 1, en);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  while(1){
    cin >> N;
    
    if(N == 0)
      break;
    input_data();
    solution(1, N);
    cout << max_width << '\n';
  }

  return 0;
}