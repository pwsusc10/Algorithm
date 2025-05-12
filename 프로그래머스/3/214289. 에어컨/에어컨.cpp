#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > dp(51, vector<int>(1001, 21e8));

void get_dp_data(int temperature, int t1, int t2, int a, int b, vector<int> &onboard){
    for(int j = 1; j < onboard.size(); j++){
        for(int i = 0; i <= 50; i++){
            // 손님이 탄 시각, 적정 온도가 아닌 경우.
            if(onboard[j] == 1 && (i < t1 || i > t2))
                continue;
            
            int up = 21e8;
            int mid = 21e8;
            int down = 21e8;
            // 온도 상승.
            if(i - 1  >= 0){
                // 실외 온도쪽으로 온도 상승.
                if(i <= temperature)
                    up = dp[i - 1][j - 1];
                else if(i > temperature)
                    up = dp[i - 1][j - 1] + a;
            }
            // 온도 하락.
            if(i + 1 <= 50){
                // 실외 온도 반대쪽으로 온도 하락.
                if(i < temperature)
                    down = dp[i + 1][j - 1] + a;
                else if(i >= temperature)
                    down = dp[i + 1][j - 1];
            }
            if(i == temperature)
                mid = dp[i][j - 1];
            else
                mid = dp[i][j - 1] + b;
            dp[i][j] = min({up, mid, down});
            // cout << "(i, j) : " << i << " " << j << "up : " << up << " mid : " << mid << " down : " << down << "\n";
            // cout << "(i, j) : " << i << " " << j << " : " << dp[i][j] << "\n----------\n";
        }
    }
}

int get_min_energy(int time){
    int min_energy = 21e8;
    
    for(int i = 0; i <= 50; i++){
        // cout << "energy : " << dp[i][time] << "\n";
        min_energy = min(min_energy, dp[i][time]);
    }
    return min_energy;
}

int solution(int temperature, int t1, int t2, int a, int b, vector<int> onboard) {
    int answer = 0;
    
    dp[temperature + 10][0] = 0;
    get_dp_data(temperature + 10, t1 + 10, t2 + 10, a, b, onboard);
    answer = get_min_energy(onboard.size() - 1);
    
    return answer;
}