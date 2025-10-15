#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct puddle {
    int st, en;

    bool operator<(const puddle &p) const {
        return st > p.st;
    }
};

int N, L, ans;
priority_queue<puddle> pq;

void input_data() {
    cin >> N >> L;

    for(int i = 0; i < N; i++) {
        int st, en;
        cin >> st >> en;
        pq.push({st, en});
    }
}

void solve() {
    int prev = 0;

    while(!pq.empty()) {
        puddle p = pq.top();
        pq.pop();

        // cout << p.st << " " << p.en << "\n";

        if(p.en <= prev)
            continue;
        else if(prev > p.st)
            p.st = prev;
        
        int dist = p.en - p.st;

        if(dist % L == 0) {
            ans += dist / L;
            prev = p.en;
        }
        else {
            ans += dist / L + 1;
            prev = p.st + (dist / L + 1) * L;
        }
    }
}

void print_result() {
    cout << ans << "\n";
}

int main() {
    input_data();
    solve();
    print_result();

    return 0;
}