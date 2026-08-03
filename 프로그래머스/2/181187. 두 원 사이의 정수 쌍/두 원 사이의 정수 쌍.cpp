#include <string>
#include <vector>

using namespace std;

/*
 * x^2 + y^2 >= r^2를 만족하는
 * 가장 작은 정수 x를 찾는다.
 */
long long calculate_small(long long y, long long r) {
    long long st = 0;
    long long en = r;

    while (st < en) {
        long long mid = (st + en) / 2;

        if (y * y + mid * mid >= r * r) {
            en = mid;
        } else {
            st = mid + 1;
        }
    }

    return st;
}

/*
 * x^2 + y^2 <= r^2를 만족하는
 * 가장 큰 정수 x를 찾는다.
 */
long long calculate_big(long long y, long long r) {
    long long st = 0;
    long long en = r;

    while (st < en) {
        // 최댓값 탐색이므로 가운데 값을 올림 처리
        long long mid = (st + en + 1) / 2;

        if (y * y + mid * mid <= r * r) {
            st = mid;
        } else {
            en = mid - 1;
        }
    }

    return st;
}

long long solution(int r1, int r2) {
    long long answer = 0;

    /*
     * y를 1부터 시작한다.
     *
     * 각 y에서 x >= 0인 점을 구한 뒤,
     * 원점을 기준으로 90도씩 회전한 네 점을 계산한다.
     */
    for (long long y = 1; y <= r2; y++) {
        long long small = calculate_small(y, r1);
        long long big = calculate_big(y, r2);

        if (small <= big) {
            answer += big - small + 1;
        }
    }

    return answer * 4;
}