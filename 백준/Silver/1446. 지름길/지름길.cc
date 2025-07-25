#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_NUM 10001

using namespace std;

int dp[MAX_NUM];
int N, D;
vector<vector<pair<int,int> > > paths;

void input(){
    cin >> N >> D;

    paths.resize(MAX_NUM);
    
    int st, en, cost;
    
    for(int i = 0; i < N; i++){
        cin >> st >> en >> cost;
        
        paths[en].push_back({st, cost});
    }
}

void get_dp(int idx){
    int init_cost = dp[idx - 1] + 1;

    for(int i  = 0; i < paths[idx].size(); i++){
        init_cost = min(init_cost, dp[paths[idx][i].first] + paths[idx][i].second);
    }

    dp[idx] = init_cost;
}

void solution(){
    for(int i = 1; i <= D; i++)
        get_dp(i);

    cout << dp[D];
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    input();
    solution();

    return 0;
}