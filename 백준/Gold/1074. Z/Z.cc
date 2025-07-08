#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int N, r, c;

void input_data(){
    cin >> N >> r >> c;
}


void solution(int y, int x, int n, int cur){
    if(n == 0){
        cout << cur;
        return;
    }
    int half_length = pow(2, n - 1);
    int quarter_value = half_length * half_length;

    if(r < y + half_length){
        // 위
        if(c < x + half_length){
            // 2사분면
            solution(y, x, n - 1, cur);
        } else{
            // 1사분면
            solution(y, x + half_length, n - 1, cur + quarter_value);
        }

    } else {
        // 아래
        if(c < x + half_length){
            // 3사분면
            solution(y + half_length, x, n - 1, cur + quarter_value * 2);
        } else{
            // 4사분면
            solution(y + half_length, x + half_length, n - 1, cur + quarter_value * 3);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    input_data();
    solution(0, 0, N, 0);

    return 0;
}