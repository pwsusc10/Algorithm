#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int answer;
vector<vector<int>> g_info;
vector<vector<vector<bool>>> visited;

void dfs(int idx, int a_sum, int b_sum, int n, int m) {
    // 이미 둘 중 하나라도 잡히면 실패
    if (a_sum >= n || b_sum >= m) {
        return;
    }

    // 현재 A 흔적이 이미 기존 답보다 크거나 같으면 볼 필요 없음
    if (a_sum >= answer) {
        return;
    }

    // 모든 물건을 처리한 경우
    if (idx == g_info.size()) {
        answer = min(answer, a_sum);
        return;
    }

    // 같은 상태를 이미 본 적 있으면 중복 탐색 방지
    if (visited[idx][a_sum][b_sum]) {
        return;
    }
    visited[idx][a_sum][b_sum] = true;

    // 1. 현재 물건을 A가 훔치는 경우
    dfs(idx + 1,
        a_sum + g_info[idx][0],
        b_sum,
        n,
        m);

    // 2. 현재 물건을 B가 훔치는 경우
    dfs(idx + 1,
        a_sum,
        b_sum + g_info[idx][1],
        n,
        m);
}

int solution(vector<vector<int>> info, int n, int m) {
    g_info = info;
    answer = 1e9;

    int len = info.size();

    // idx: 0 ~ len
    // a_sum: 0 ~ n - 1
    // b_sum: 0 ~ m - 1
    visited.assign(len + 1,
                   vector<vector<bool>>(n,
                   vector<bool>(m, false)));

    dfs(0, 0, 0, n, m);

    if (answer == 1e9) {
        return -1;
    }

    return answer;
}