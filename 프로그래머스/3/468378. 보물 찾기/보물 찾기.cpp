#include <string>
#include <vector>

using namespace std;

extern int excavate(int);

int dp[201][201]; // dp[i][j]: i ~ j 구간에서 보물을 확실히 찾기 위한 최소 보장 비용
int idx[201][201]; // idx[i][j]: i ~ j 구간에서 최적의 첫 굴착 위치 k
int answer;
const int INF = 1e9;

int solution(vector<int> depth, int money) {
    int w = depth.size();
    for (int i = 1; i <= w; i++) {
        dp[i][i] = depth[i - 1];
        idx[i][i] = i;
    }
    for (int i = w; i > 0; i--) {
        for (int j = i + 1; j <= w; j++) {
            dp[i][j] = INF;

            for (int k = i; k <= j; k++) {
                int left_cost = (k - 1 >= i) ? dp[i][k - 1] : 0;
                int right_cost = (k + 1 <= j) ? dp[k + 1][j] : 0;
                int worst = depth[k - 1] + max(left_cost, right_cost);

                if (worst < dp[i][j]) {
                    dp[i][j] = worst;
                    idx[i][j] = k;
                }
            }
        }
    }

    int left = 1, right = w;
    while (left <= right) {
        int k = idx[left][right];
        int res = excavate(k);

        if (res == 0) {
            answer = k;
            break;
        }
        else if (res == -1) right = k - 1;
        else left = k + 1;
    }
    return answer;
}