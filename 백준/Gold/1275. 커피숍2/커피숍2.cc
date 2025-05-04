#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long N, Q;
vector<long long> arr;
vector<long long> tree;

void init_tree(long long node, long long st, long long en) {
  if (st == en) {
    tree[node] = arr[st];
    return;
  }
  init_tree(node * 2, st, (st + en) / 2);
  init_tree(node * 2 + 1, (st + en) / 2 + 1, en);
  tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void update_tree(long long node, long long st, long long en, long long idx, long long value) {
  if (idx < st || en < idx)
    return;
  else if (st == en) {
    tree[node] = value;
    return;
  }
  update_tree(node * 2, st, (st + en) / 2, idx, value);
  update_tree(node * 2 + 1, (st + en) / 2 + 1, en, idx, value);
  tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

long long query(long long node, long long st, long long en, long long left, long long right) {
  if (right < st || en < left)
    return 0;
  else if (left <= st && en <= right)
    return tree[node];
  else {
    long long lsum = query(node * 2, st, (st + en) / 2, left, right);
    long long rsum = query(node * 2 + 1, (st + en) / 2 + 1, en, left, right);
    return lsum + rsum;
  }
}

void input_data(){
  cin >> N >> Q;

  arr.resize(N + 1);
  tree.resize(4 * N);

  for (long long i = 1; i <= N; i++){
    cin >> arr[i];
  }
  init_tree(1, 1, N);  
}

void solution() {
  long long left, right, idx, value;
  long long result;
  for (long long i = 0; i < Q; i++) {
    cin >> left >> right >> idx >> value;
    if(left > right) {
      swap(left, right);
    }
    result = query(1, 1, N, left, right);
    update_tree(1, 1, N, idx, value);
    cout << result << "\n";
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  input_data();
  solution();

  return 0;
}