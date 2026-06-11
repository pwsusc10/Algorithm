#include <string>
#include <vector>

using namespace std;

bool can_cross(const vector<int>& stones, int k, int people) {
    int cnt = 0;

    for (int stone : stones) {
        if (stone < people) {
            cnt++;
        } else {
            cnt = 0;
        }

        if (cnt >= k) {
            return false;
        }
    }

    return true;
}

int solution(vector<int> stones, int k) {
    int left = 1;
    int right = 200000000;
    int answer = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (can_cross(stones, k, mid)) {
            answer = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return answer;
}
// 문제 해결 1.
// deque window를 만들어 slicing.
// deque에서 나올 때마다 값을 감소.
// window안의 값이 모두 0인 경우까지 반복.
// 시간 복잡도 : (2 * 10^5) * (2 * 10^8) => 4 * 10^13

// 문제 해결 2.
// stones 배열을 중복이 없는 내림차순 자료형 set에 저장.
// set의 값중 가장 작은 값을 모든 stone에 감소시킨 후, 건널 수 있는지 확인.
// 건널 수 없을 때 까지 반복.
// 시간 복잡도 : (2 * 10^5) * (2 * 10^5) => 4 * 10^10

// 문제 해결 3.
// 몇 명까지 건널 수 있나를 묻는 것이므로 1~200000 을 이분 탐색 처리.
// 시간 복잡도 : (2 * 10^5) * log(2 * 10^5) <= 2 * 10^6 