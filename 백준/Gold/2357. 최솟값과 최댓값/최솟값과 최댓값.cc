#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<int> arr;
vector<int> min_tree;
vector<int> max_tree;

void init_min_tree(int node, int st, int en) {
  if (st == en) {
    min_tree[node] = arr[st];
    return;
  }
  init_min_tree(node * 2, st, (st + en) / 2);
  init_min_tree(node * 2 + 1, (st + en) / 2 + 1, en);
  min_tree[node] = min(min_tree[node * 2], min_tree[node * 2 + 1]);
}

void init_max_tree(int node, int st, int en) {
  if (st == en) {
    max_tree[node] = arr[st];
    return;
  }
  init_max_tree(node * 2, st, (st + en) / 2);
  init_max_tree(node * 2 + 1, (st + en) / 2 + 1, en);
  max_tree[node] = max(max_tree[node * 2], max_tree[node * 2 + 1]);
}

int min_query(int node, int st, int en, int left, int right) {
  if (right < st || en < left)
    return 21e8;
  else if (left <= st && en <= right)
    return min_tree[node];
  else {
    int lmin = min_query(node * 2, st, (st + en) / 2, left, right);
    int rmin = min_query(node * 2 + 1, (st + en) / 2 + 1, en, left, right);
    return min(lmin, rmin);
  }
}

int max_query(int node, int st, int en, int left, int right) {
  if (right < st || en < left)
    return 0;
  else if (left <= st && en <= right)
    return max_tree[node];
  else {
    int lmax = max_query(node * 2, st, (st + en) / 2, left, right);
    int rmax = max_query(node * 2 + 1, (st + en) / 2 + 1, en, left, right);
    return max(lmax, rmax);
  }
}

void solution() {
  int left, right;
  for (int i = 0; i < M; i++) {
    cin >> left >> right;
    
    cout << min_query(1, 1, N, left, right) << " " 
         << max_query(1, 1, N, left, right) << "\n";
  }
}

void input_data(){
  cin >> N >> M;

  arr.resize(N + 1);
  min_tree.resize(4 * N);
  max_tree.resize(4 * N);

  for (int i = 1; i <= N; i++) {
    cin >> arr[i];
  }

  init_min_tree(1, 1, N);
  init_max_tree(1, 1, N);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  
  input_data();
  solution();
  return 0;
}