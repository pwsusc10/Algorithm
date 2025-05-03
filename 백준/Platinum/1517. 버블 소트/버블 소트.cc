#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
long long cnt;
vector<int> arr;
vector<int> idx_tree; // 구간 별 가장 큰 수의 idx를 저장하는 tree
vector<int> cnt_tree; // 구간 별 몇개의 수가 있는지 저장하는 tree

void init_tree(int node, int st, int en) {
  if(st == en) {
    idx_tree[node] = st;
    cnt_tree[node] = 1;
    return;
  }
  init_tree(node * 2, st, (st + en) / 2);
  init_tree(node * 2 + 1, (st + en) / 2 + 1, en);
  if(arr[idx_tree[node * 2]] > arr[idx_tree[node * 2 + 1]]) {
    idx_tree[node] = idx_tree[node * 2];
  } else {
    idx_tree[node] = idx_tree[node * 2 + 1];
  }
  cnt_tree[node] = cnt_tree[node * 2] + cnt_tree[node * 2 + 1];
}

void input_data(){
  cin >> N;

  arr.resize(N + 1, 0);
  arr[0] = -21e8; // 0번째 인덱스는 사용하지 않음
  idx_tree.resize(4 * N);
  cnt_tree.resize(4 * N);

  for (int i = 1; i <= N; i++){
    cin >> arr[i];
  }

  init_tree(1, 1, N);
}

// left ~ right 구간에서의 갯수를 반환하는 함수
long long query(int node, int st, int en, int left, int right) {
  if(right < st || en < left) {
    return 0;
  } else if(left <= st && en <= right) {
    return cnt_tree[node];
  } else {
    long long lsum = query(node * 2, st, (st + en) / 2, left, right);
    long long rsum = query(node * 2 + 1, (st + en) / 2 + 1, en, left, right);
    return lsum + rsum;
  }
}

// st ~ en 구간에서 idx가 포함된 구간을 update하는 함수
void update_tree(int node, int st, int en, int idx) {
  if(idx < st || en < idx)
    return;
  else if(st == en) {
    cnt_tree[node] = 0;
    return;
  }
  update_tree(node * 2, st, (st + en) / 2, idx);
  update_tree(node * 2 + 1, (st + en) / 2 + 1, en, idx);
  if(arr[idx_tree[node * 2]] > arr[idx_tree[node * 2 + 1]]) {
    idx_tree[node] = idx_tree[node * 2];
  } else {
    idx_tree[node] = idx_tree[node * 2 + 1];
  }
  cnt_tree[node] = cnt_tree[node * 2] + cnt_tree[node * 2 + 1];
}

void solution(){
  for(int i = 0; i <= N; i++) {
    int max_idx = idx_tree[1];
    long long back_cnt = query(1, 1, N, max_idx + 1, N);

    // cout << max_idx << " " << "value : " << arr[max_idx] << " cnt : "<< back_cnt << "\n";
    if(max_idx == 0)
      break;
    cnt += back_cnt;
    arr[max_idx] = -21e8;
    update_tree(1, 1, N, max_idx);
  }

  cout << cnt;
}

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  input_data();
  solution();

  return 0;
}