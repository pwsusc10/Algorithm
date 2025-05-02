#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, max_width;
vector<int> arr;
vector<int> idx_tree;

void input_data(){
  cin >> N;

  arr.resize(N + 1, 0);
  arr[0] = 21e8;
  idx_tree.resize(4 * N);

  for (int i = 1; i <= N; i++){
    cin >> arr[i];
  }
}

void init_tree(int node, int st, int en) {
  if(st == en) {
    idx_tree[node] = st;
    return;
  }
  init_tree(node * 2, st, (st + en) / 2);
  init_tree(node * 2 + 1, (st + en) / 2 + 1, en);
  if(arr[idx_tree[node * 2]] < arr[idx_tree[node * 2 + 1]]) {
    idx_tree[node] = idx_tree[node * 2];
  } else {
    idx_tree[node] = idx_tree[node * 2 + 1];
  }
}

int get_min_height_idx(int node, int st, int en, int left, int right) {
  if(right < st || en < left) {
    return 0;
  } else if(left <= st && en <= right) {
    return idx_tree[node];
  } else {
    int lmin = get_min_height_idx(node * 2, st, (st + en) / 2, left, right);
    int rmin = get_min_height_idx(node * 2 + 1, (st + en) / 2 + 1, en, left, right);
    if(arr[lmin] < arr[rmin]) {
      return lmin;
    } else {
      return rmin;
    }
  }
}

void get_max_width(int st, int en) {
  int min_height_idx = get_min_height_idx(1, 1, N, st, en);
  max_width = max(max_width, arr[min_height_idx] * (en - st + 1));

  if(min_height_idx - 1 >= st) {
    get_max_width(st, min_height_idx - 1);
  }
  if(min_height_idx + 1 <= en) {
    get_max_width(min_height_idx + 1, en);
  }
}

void solution(){
  init_tree(1, 1, N);

  get_max_width(1, N);

  cout << max_width << "\n";
}

int main(){

  input_data();
  solution();

  return 0;
}