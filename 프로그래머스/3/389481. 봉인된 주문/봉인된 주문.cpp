#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 문자열 -> 인덱스 (삭제 전)
ll get_index(const string& s) {
    ll idx = 0;
    int len = s.size();
    // 더 짧은 문자열 개수 다 더하기
    ll pow26 = 1;
    for (int l = 1; l < len; l++) {
        pow26 *= 26;
        idx += pow26;
    }
    // 같은 길이에서 사전 순 위치
    pow26 = 1;
    for (int i = 0; i < len; i++) {
        int d = s[i] - 'a';
        int remain = len - i - 1;
        ll block = 1;
        for (int j = 0; j < remain; j++) block *= 26;
        idx += (ll)d * block;
    }
    return idx + 1; // 1-indexed
}

// 인덱스 -> 문자열 (삭제 전)
string get_string_by_num(ll n) {
    // 길이 결정
    ll total = 0;
    ll pow26 = 26;
    int len = 1;
    while (total + pow26 < n) {
        total += pow26;
        len++;
        pow26 *= 26;
    }
    n -= total; // len자리 안에서의 위치

    string s(len, 'a');
    n--; // 0-indexed
    for (int i = len-1; i >= 0; i--) {
        s[i] = 'a' + (n % 26);
        n /= 26;
    }
    return s;
}

string solution(long long n, vector<string> bans) {
    vector<ll> ban_idx;
    ban_idx.reserve(bans.size());
    for (auto &b : bans) ban_idx.push_back(get_index(b));
    sort(ban_idx.begin(), ban_idx.end());

    // 이분 탐색: 삭제 전 인덱스 mid일 때 삭제 후 몇 번째?
    ll lo = 1, hi = (ll)4e15; // 충분히 크게 (11자리까지)
    ll ans = -1;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        ll removed = upper_bound(ban_idx.begin(), ban_idx.end(), mid) - ban_idx.begin();
        ll rank_after = mid - removed;
        if (rank_after >= n) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return get_string_by_num(ans);
}
