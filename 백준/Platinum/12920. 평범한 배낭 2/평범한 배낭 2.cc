#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_WEIGHT 10000

using namespace std;

typedef struct {
    int weight;
    int value;
} item;

int N, M;
vector<item> items;
vector<int> dp(MAX_WEIGHT + 1, 0);

void input_data() {
    cin >> N >> M;

    int weight, value, cnt;
    for (int i = 0; i < N; i++) {
        cin >> weight >> value >> cnt;

        // 이진수를 사용해 package.
        for (int j = cnt; j > 0; j >>= 1) {
            int num = j - (j >> 1);
            items.push_back({ weight * num, value * num });
        }
    }
}

void solution() {
    for (int i = 0; i < items.size(); i++) {
        for (int j = M; j >= items[i].weight; j--)
            dp[j] = max(dp[j], dp[j - items[i].weight] + items[i].value);
    }

    cout << dp[M] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    input_data();
    solution();

    return 0;
}