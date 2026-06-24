#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

set<int> s;

int solution(vector<int> elements) {
    // w : window size
    for(int w = 1; w <= elements.size(); w++){
        int cur = 0;
        for(int i = 0; i < w; i++)
            cur += elements[i];
        
        s.insert(cur);
        
        for(int i = 0; i < elements.size(); i++){
            cur -= elements[i];
            cur += elements[(i + w) % elements.size()];
            
            s.insert(cur);
        }
    }
    
    // for (const auto& el : s) {
    //     cout << el << endl;
    // }
    
    return s.size();
}