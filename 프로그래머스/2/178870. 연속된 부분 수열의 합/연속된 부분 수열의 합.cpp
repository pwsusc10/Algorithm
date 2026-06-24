#include <string>
#include <vector>
#include <utility>

using namespace std;

int left = 0;
int right = 0;
int len = 21e9;
pair<int, int> pos;

vector<int> solution(vector<int> sequence, int k) {
    vector<int> answer;
    int cur = sequence[0];
    
    while(right < sequence.size() && left <= right) {
        if(cur < k){
            right++;
            if(right >= sequence.size())
                break;
            cur += sequence[right];
        } else if (cur > k) {
            cur -= sequence[left];
            left++;
        } else {
            if(len > right - left + 1) {
                len = right - left + 1;
                pos = make_pair(left, right);
            }
            right++;
            if(right >= sequence.size())
                break;
            cur += sequence[right];
        }
    }
    
    answer.push_back(pos.first);
    answer.push_back(pos.second);
    
    return answer;
}