#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct BaseEntity {
    int s;  // 속도
    int d;  // 방향, 1인 경우는 위, 2인 경우는 아래, 3인 경우는 오른쪽, 4인 경우는 왼쪽
    int z;  // 크기
};

struct Shark : public BaseEntity {
    int y;  // 세로 위치
    int x;  // 가로 위치

    Shark() {}

    Shark(int y, int x, int s, int d, int z) {
        this->y = y;
        this->x = x;
        this->s = s;
        this->d = d;
        this->z = z;
    }
};

int R, C, M, sum, fishman;
vector<vector<BaseEntity> > map;
vector<Shark> sharks;

void input_data(){
    cin >> R >> C >> M;

    map.resize(R, vector<BaseEntity>(C));

    Shark temp;
    for(int i = 0; i < M; i++){
        cin >> temp.y >> temp.x >> temp.s >> temp.d >> temp.z;

        map[temp.y - 1][temp.x - 1] = {temp.s, temp.d, temp.z};
    }
}

void fishing_shark(){
    for(int i = 0; i < R; i++){
        if(map[i][fishman].z != 0){
            sum += map[i][fishman].z;
            map[i][fishman] = {0, 0, 0};
            break;
        }
    }
}

Shark calculate_next_pos(Shark shark){
    // 1인 경우는 위, 2인 경우는 아래, 3인 경우는 오른쪽, 4인 경우는 왼쪽
    if(shark.d == 1){
        if(shark.s <= shark.y)
            shark.y -= shark.s;
        else {
            int share, res;
            share = (shark.s - shark.y) / (R - 1);
            res = (shark.s - shark.y) % (R - 1);

            if(share % 2 == 0)
                shark = {res, shark.x, shark.s, 2, shark.z};
            else
                shark = {(R - 1) - res, shark.x, shark.s, shark.d, shark.z};
        }
    } else if(shark.d == 2){
        if(shark.y + shark.s < R)
            shark.y += shark.s;
        else {
            int share, res;
            share = (shark.y + shark.s - (R - 1)) / (R - 1);
            res = (shark.y + shark.s - (R - 1)) % (R - 1);

            if(share % 2 == 0)
                shark = {(R - 1) - res, shark.x, shark.s, 1, shark.z};
            else
                shark = {res, shark.x, shark.s, shark.d, shark.z};
        }
    } else if(shark.d == 3){
        if(shark.x + shark.s < C)
            shark.x += shark.s;
        else {
            int share, res;
            share = (shark.x + shark.s - (C - 1)) / (C - 1);
            res = (shark.x + shark.s - (C - 1)) % (C - 1);

            if(share % 2 == 0)
                shark = {shark.y, (C - 1) - res, shark.s, 4, shark.z};
            else
                shark = {shark.y, res, shark.s, shark.d, shark.z};
        }
    } else if(shark.d == 4){
        if(shark.s <= shark.x)
            shark.x -= shark.s;
        else {
            int share, res;
            share = (shark.s - shark.x) / (C - 1);
            res = (shark.s - shark.x) % (C - 1);

            if(share % 2 == 0)
                shark = {shark.y, res, shark.s, 3, shark.z};
            else
                shark = {shark.y, (C - 1) - res, shark.s, shark.d, shark.z};
        }
    } else {
        cout << "direction error";
    }

    return shark;
}

void move_shark(){
    // 상어들 초기화
    sharks.clear();

    // 상어들 정보 추출
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            if(map[i][j].z != 0){
                sharks.push_back({i, j, map[i][j].s, map[i][j].d, map[i][j].z});
                map[i][j] = {0, 0, 0};
            }
        }
    }

    // 상어들 이동
    Shark next;
    for(int i = 0; i < sharks.size(); i++){
        next = calculate_next_pos(sharks[i]);

        if(map[next.y][next.x].z > next.z)
            continue;
        map[next.y][next.x] = {next.s, next.d, next.z};
    }
}

void solution(){
    while(fishman < C){
        // 낚시
        fishing_shark();
        // 상어 이동
        move_shark();
        // 낚시꾼 이동
        fishman++;
    }

    cout << sum;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    input_data();
    solution();

    return 0;
}