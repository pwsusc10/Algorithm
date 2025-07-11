#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<int> arr;
int x, n;

void input_data(){
    cin >> n;

    arr.clear();
    arr.resize(n);
    for(int i = 0 ; i < n; i++)
        cin >> arr[i];

    sort(arr.begin(), arr.end());
}

bool find_target(int idx, int target){
    int st, en, mid;

    st = idx;
    en = arr.size() - 1;
    mid = (st + en) / 2;

    while(st <= en){
        if(arr[mid] == target)
            return true;
        else if(arr[mid] < target)
            st = mid + 1;
        else
            en = mid - 1;
        mid = (st + en) / 2;
    }
    return false;
}

void solution(){
    for(int i = 0; i < arr.size() - 1; i++){
        if(arr[i] > x / 2)
            break;
        
        if(find_target(i + 1, x - arr[i])){
            cout << "yes " << arr[i] << " " << x - arr[i] << "\n";
            return;
        }
    }

    cout << "danger\n";
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    while(cin >> x){
        x = x * pow(10, 7);
        input_data();
        solution();
    }
    
    return 0;
}