#include <iostream>
#include <vector>
#include <queue>
#define MAX_SIZE 100001

using namespace std;

int N, K;
vector<int> times;
queue<int> pos;

void input(){
    cin >> N >> K;
    times.resize(MAX_SIZE, 21e8);
    times[N] = 0;
    pos.push(N);
}

void solution(){
    int cur_pos;
    while(!pos.empty()){
        cur_pos = pos.front();
        pos.pop();

        if(cur_pos == K){
            cout << times[cur_pos];
            break;
        }

        // 전진
        if(cur_pos + 1 < MAX_SIZE && times[cur_pos + 1] > times[cur_pos] + 1) {
            times[cur_pos + 1] = times[cur_pos] + 1;
            pos.push(cur_pos + 1);
        }
        // 후진
        if(cur_pos - 1 >= 0 && times[cur_pos - 1] > times[cur_pos] + 1) {
            times[cur_pos - 1] = times[cur_pos] + 1;
            pos.push(cur_pos - 1);
        }
        // 순간이동
        if(cur_pos == 0)
            continue;
        while(cur_pos * 2 < MAX_SIZE){
            if(times[cur_pos * 2] > times[cur_pos]){
                times[cur_pos * 2] = times[cur_pos];
                pos.push(cur_pos * 2);
            }
            cur_pos *= 2;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    input();
    solution();

    return 0;
}