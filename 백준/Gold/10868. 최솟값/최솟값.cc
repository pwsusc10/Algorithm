#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
vector<int> arr;
vector<int> tree;

void init_tree(int node, int st, int en) {
  if (st == en) {
    tree[node] = arr[st];
    return;
  }
  init_tree(node * 2, st, (st + en) / 2);
  init_tree(node * 2 + 1, (st + en) / 2 + 1, en);
  tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

void input_data(){
  cin >> N >> M;

  arr.resize(N + 1);
  tree.resize(4 * N);

  for (int i = 1; i <= N; i++){
    cin >> arr[i];
  }
  init_tree(1, 1, N);  
}

int query(int node, int st, int en, int left, int right) {
  if (right < st || en < left)
    return 21e8;
  else if(left <= st && en <= right)
    return tree[node];
  else {
    int lmin = query(node * 2, st, (st + en) / 2, left, right);
    int rmin = query(node * 2 + 1, (st + en) / 2 + 1, en, left, right);
    return min(rmin, lmin);
  }
}

void solution() {
  int left, right;
  for (int i = 0; i < M; i++) {
    cin >> left >> right;
    cout << query(1, 1, N, left, right) << "\n";
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  input_data();
  solution();

  return 0;
}