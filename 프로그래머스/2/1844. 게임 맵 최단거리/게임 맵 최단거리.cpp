#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node{
    int y, x, dist;
};

vector<vector<bool> > visited;
int w, h, min_dist = -1;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

void init_data(vector<vector<int> > &map){
    h = map.size();
    w = map[0].size();
    
    // cout << "h : " << h << " w : " << w << "\n";
    visited.resize(h, vector<bool>(w, false));
}


void bfs(vector<vector<int> > &map){
    queue<Node> q;
    visited[0][0] = true;
    q.push({0, 0, 1});
    
    while(!q.empty()){
    
        Node cur = q.front();
        q.pop();
        if(cur.y == h - 1 && cur.x == w - 1){
            min_dist = cur.dist;
            return;
        }
        
        for(int i = 0; i < 4; i++){
            Node npos = {cur.y + dy[i], cur.x + dx[i], cur.dist + 1};
        
            // 경계 확인
            if(npos.x < 0 || npos.x >= w || npos.y < 0 || npos.y >= h)
                continue;
            else if(map[npos.y][npos.x] == 0)   // 벽인지
                continue;
            else if(visited[npos.y][npos.x])    // 방문했는지
                continue;

            visited[npos.y][npos.x] = true;
            q.push(npos);
        }
    }
}

int solution(vector<vector<int> > maps)
{
    init_data(maps);
    bfs(maps);
    
    return min_dist;
}