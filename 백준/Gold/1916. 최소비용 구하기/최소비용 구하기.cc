#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, M, st, en;
vector<int> dist;
vector<bool> visited;
vector<vector<pair<int, int>>> adj;

struct Node {
  int dist;
  int node;

  bool operator<(const Node& other) const {
    return dist > other.dist; // Min-heap based on distance
  }
};

priority_queue<Node> pq;

void input(){
  cin >> N >> M;

  dist.resize(N + 1, 21e8);
  visited.resize(N + 1, false);
  adj.resize(N + 1);

  for(int i = 0; i < M; i++) {
    int u, v, w;
    
    cin >> u >> v >> w;
    adj[u].push_back({v, w});
  }

  cin >> st >> en;
}

void solution(){
  dist[st] = 0;
  pq.push({0, st});

  while(!pq.empty()) {
    int cur_node = pq.top().node;
    int cur_dist = pq.top().dist;
    pq.pop();

    if(visited[cur_node]) continue;
    visited[cur_node] = true;

    for(const auto& edge : adj[cur_node]) {
      int next_node = edge.first;
      int next_dist = edge.second + cur_dist;
      if(next_dist < dist[next_node]) {
        dist[next_node] = next_dist;
        pq.push({next_dist, next_node});
      }
    }
  }

  cout << dist[en];
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  solution();

  return 0;
}