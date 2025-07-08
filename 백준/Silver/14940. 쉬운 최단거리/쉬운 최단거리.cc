#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

vector<vector<int> > map;
vector<vector<int> > distance_map;
pair<int, int> start_pos;
int n, m, cur_distance;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

void input_data(){
    cin >> n >> m;
    map.resize(n, vector<int>(m));
    distance_map.resize(n, vector<int>(m, -1));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> map[i][j];
            
            if(map[i][j] == 2){
                start_pos = make_pair(i, j);
                distance_map[i][j] = 0;
            } else if(map[i][j] == 0)
                distance_map[i][j] = 0;
        }
    }
}

void solution(){
    queue<pair<int, int> > q;
    int q_size;
    q.push(start_pos);

    while(!q.empty()){
        cur_distance++;
        q_size = q.size();

        for(int i = 0; i < q_size; i++){
            pair<int, int> cur_pos;
            cur_pos = q.front();
            q.pop();

            for(int j = 0; j < 4; j++){
                pair<int, int> next_pos = make_pair(cur_pos.first + dy[j], cur_pos.second + dx[j]);
                if(next_pos.first < 0 || next_pos.first >= n || next_pos.second < 0 || next_pos.second >= m)
                    continue;
                else if(distance_map[next_pos.first][next_pos.second] >= 0)
                    continue;
                distance_map[next_pos.first][next_pos.second] = cur_distance;
                q.push(next_pos);
            }
        }
    }
}

void print_result(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << distance_map[i][j] << " ";
        }
        cout << "\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    input_data();
    solution();
    print_result();

    return 0;
}