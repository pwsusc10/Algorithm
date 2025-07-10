#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<string> map(12);
vector<vector<bool> > is_visited(12, vector<bool>(6, false));
vector<pair<int, int> > clear_pos;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int chain_num;

void input(){
    for(int i = 0; i < 12; i++)
    cin >> map[i];
}

void check_chain(int y, int x){
    vector<pair<int, int> > check_pos;
    queue<pair<int, int> > q;

    check_pos.push_back({y, x});
    q.push({y, x});
    is_visited[y][x] = true;
    
    while(!q.empty()){
        pair<int, int> cur_pos = q.front();
        q.pop();

        for(int i = 0; i < 4; i++){
            if(cur_pos.first + dy[i] < 0 || cur_pos.first + dy[i] >= 12 || cur_pos.second + dx[i] < 0 || cur_pos.second + dx[i] >= 6)
                continue;
            else if(map[cur_pos.first][cur_pos.second] != map[cur_pos.first + dy[i]][cur_pos.second + dx[i]])
                continue;
            else if(is_visited[cur_pos.first + dy[i]][cur_pos.second + dx[i]])
                continue;
            
            is_visited[cur_pos.first + dy[i]][cur_pos.second + dx[i]] = true;
            check_pos.push_back({cur_pos.first + dy[i], cur_pos.second + dx[i]});
            q.push({cur_pos.first + dy[i], cur_pos.second + dx[i]});
        }
    }

    if(check_pos.size() > 3){
        while(!check_pos.empty()){
            clear_pos.push_back(check_pos.back());
            check_pos.pop_back();
        }
    }
}

void drop_puyo(){
    for(int j = 0; j < 6; j++){
        int st = -1;
        int en = -1;
        bool is_color = false;

        string str;
        for(int i = 11; i >= 0; i--){
            if(map[i][j] != '.'){
                str.push_back(map[i][j]);
            }
        }

        if(str.length() > 0){
            for(int i = 0; i < 12; i++){
                if(i >= str.length())
                    map[11 - i][j] = '.';
                else
                    map[11 - i][j] = str[i];
            }
        }
    }
}

void clear_data(){
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 6; j++)
            is_visited[i][j] = false;
    }
}

void after_boom(){
    drop_puyo();
    clear_data();
}

void solution(){
    while(1) {
        for(int i = 0; i < 12; i++){
            for(int j = 0; j < 6; j++){
                if(map[i][j] != '.' && !is_visited[i][j]){
                    check_chain(i,j);
                }
            }
        }
        
        if(clear_pos.empty())
            break;

        while(!clear_pos.empty()){
            pair<int, int> pos = clear_pos.back();
            clear_pos.pop_back();
            map[pos.first][pos.second] = '.';
        }
        
        chain_num++;
        after_boom();
    }

    cout << chain_num;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    input();
    solution();

    return 0;
}