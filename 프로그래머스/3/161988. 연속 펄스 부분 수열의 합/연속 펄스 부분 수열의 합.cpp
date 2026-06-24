#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long solution(vector<int> sequence) {
    vector<vector<int>> pulse_seq(2);
    vector<vector<long long>> squeeze_seq(2);
    long long answer = 0;
    
    for(int i = 0; i < sequence.size(); i++){
        if(i % 2 == 0){
            pulse_seq[0].push_back(sequence[i]);
            pulse_seq[1].push_back(sequence[i] * (-1));
        } else {
            pulse_seq[0].push_back(sequence[i] * (-1));
            pulse_seq[1].push_back(sequence[i]);
        }
    }
    
    for(int i = 0; i < 2; i++){
        long long cur = pulse_seq[i][0];
        
        for(int j = 1; j < pulse_seq[i].size(); j++){
            // 부호가 같은 경우.
            if(cur * pulse_seq[i][j] >= 0) {
                cur += pulse_seq[i][j];
            } else {
                squeeze_seq[i].push_back(cur);
                cur = pulse_seq[i][j];
            }
        }
        squeeze_seq[i].push_back(cur);
    }

    
    for(int i = 0; i < 2; i++){
        long long cur = 0;
        
        for(int j = 0; j < squeeze_seq[i].size(); j++){
            if(squeeze_seq[i][j] >= 0){
                if(cur >= 0)
                    cur += squeeze_seq[i][j];
                else
                    cur = squeeze_seq[i][j];
            } else {
                if(cur + squeeze_seq[i][j] > 0)
                    cur += squeeze_seq[i][j];
                else
                    cur = squeeze_seq[i][j];
            }
            answer = max(cur, answer);
        }
    }
    
    
    return answer;
}