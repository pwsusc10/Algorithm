#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, E, n[2];
vector<vector<int>> dist;
vector<vector<bool>> visited;
vector<vector<pair<int, int>>> adj; // first: node, second: weight

struct Node {
  int dist;
  int node;

  bool operator<(const Node& other) const {
    return dist > other.dist; // Min-heap based on distance
  }
};

priority_queue<Node> pq;

void input(){
  cin >> N >> E;
  dist.resize(3, vector<int>(N + 1, 21e8));
  visited.resize(3, vector<bool>(N + 1, false));
  adj.resize(N + 1);

  for(int i = 0; i < E; i++){
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  cin >> n[0] >> n[1];
}

void dijkstra(int start, int idx) {
  dist[idx][start] = 0;
  pq.push({0, start});

  while(!pq.empty()) {
    Node current = pq.top();
    pq.pop();

    if(visited[idx][current.node]) continue;
    visited[idx][current.node] = true;

    for(auto& neighbor : adj[current.node]) {
      int next_node = neighbor.first;
      int weight = neighbor.second + current.dist;

      if(weight < dist[idx][next_node]) {
        dist[idx][next_node] = weight;
        pq.push({weight, next_node});
      }
    }
  }
}

void solution(){
  dijkstra(1, 0);
  dijkstra(n[0], 1);
  dijkstra(n[1], 2);

  int root[2];

  if(dist[0][n[0]] >= 21e8 || dist[1][n[1]] >= 21e8 || dist[2][N] >= 21e8)
    root[0] = 21e8;
  else
    root[0] = dist[0][n[0]] + dist[1][n[1]] + dist[2][N];

  if(dist[0][n[1]] >= 21e8 || dist[1][n[1]] >= 21e8 || dist[1][N] >= 21e8)
    root[1] = 21e8;
  else
    root[1] = dist[0][n[1]] + dist[1][n[1]] + dist[1][N];

  int result = min(root[0], root[1]);

  if(result == 21e8) {
    cout << -1;
  } else {
    cout << result;
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  solution();

  return 0;
}