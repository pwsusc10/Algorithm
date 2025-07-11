#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<int> is_visited;
vector<vector<pair<int, int> > > tree;  // first: node, second: value
int V, start_node, max_dist;

void input_data() {
    cin >> V;
    
    tree.resize(V + 1);

    int st, en, val;
    for(int i = 0; i < V; i++) {
        cin >> st;

        while(1) {
            cin >> en;

            if(en == -1)
                break;
            
            cin >> val;
            tree[st].push_back({en, val});
        }
    }
}

void clear_data(int idx){
    max_dist = 0;
    is_visited.clear();
    is_visited.resize(V + 1, false);
    is_visited[idx] = true;
}

void dfs(int cur_idx, int cur_dist){
    if(cur_dist > max_dist){
        max_dist = cur_dist;
        start_node = cur_idx;
    }
    
    for(int i = 0; i < tree[cur_idx].size(); i++){
        if(is_visited[tree[cur_idx][i].first])
            continue;
        
        is_visited[tree[cur_idx][i].first] = true;
        dfs(tree[cur_idx][i].first, cur_dist + tree[cur_idx][i].second);
        is_visited[tree[cur_idx][i].first] = false;
    }
}

void solution() {
    clear_data(1);
    dfs(1, 0);

    clear_data(start_node);
    dfs(start_node, 0);
    
    cout << max_dist;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    input_data();
    solution();

    return 0;
}