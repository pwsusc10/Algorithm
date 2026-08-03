#include <string>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

vector<vector<bool>> is_visited;
vector<string> game_board;

pair<int, int> st;

int h, w;

// 상, 하, 좌, 우
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

int bfs() {
    int cnt = 0;

    queue<pair<int, int>> q;
    q.push(st);

    is_visited[st.first][st.second] = true;

    while (!q.empty()) {
        int q_size = q.size();

        // 현재 이동 횟수로 도달한 모든 위치 확인
        for (int i = 0; i < q_size; i++) {
            pair<int, int> cur = q.front();
            q.pop();

            int cur_y = cur.first;
            int cur_x = cur.second;

            // 목표 지점에 정확히 정지한 경우
            if (game_board[cur_y][cur_x] == 'G') {
                return cnt;
            }

            // 상하좌우 네 방향
            for (int dir = 0; dir < 4; dir++) {
                int next_y = cur_y;
                int next_x = cur_x;

                // 장애물 또는 보드 끝을 만날 때까지 이동
                while (true) {
                    int move_y = next_y + dy[dir];
                    int move_x = next_x + dx[dir];

                    // 보드 범위를 벗어나면 현재 위치에서 정지
                    if (move_y < 0 || move_y >= h ||
                        move_x < 0 || move_x >= w) {
                        break;
                    }

                    // 장애물을 만나면 현재 위치에서 정지
                    if (game_board[move_y][move_x] == 'D') {
                        break;
                    }

                    next_y = move_y;
                    next_x = move_x;
                }

                // 한 칸도 이동하지 못한 경우
                if (next_y == cur_y && next_x == cur_x) {
                    continue;
                }

                // 이미 정지해 본 위치인 경우
                if (is_visited[next_y][next_x]) {
                    continue;
                }

                is_visited[next_y][next_x] = true;
                q.push({next_y, next_x});
            }
        }

        cnt++;
    }

    // 목표 지점에 도달할 수 없는 경우
    return -1;
}

int solution(vector<string> board) {
    game_board = board;

    h = board.size();
    w = board[0].size();

    is_visited.assign(h, vector<bool>(w, false));

    bool found = false;

    for (int i = 0; i < h && !found; i++) {
        for (int j = 0; j < w; j++) {
            if (board[i][j] == 'R') {
                st = {i, j};
                found = true;
                break;
            }
        }
    }

    return bfs();
}