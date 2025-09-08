#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;

int total_cnt;
vector<string> answer;
map<string, vector<string>> graph;
map<string, vector<bool>> visited;

void init_data(vector<vector<string>> &tickets){
    total_cnt = (int)tickets.size() + 1;

    // 1) 그래프 구성 (정렬 전)
    for (const auto &t : tickets){
        const string &st = t[0];
        const string &en = t[1];
        graph[st].push_back(en);
    }

    // 2) 각 출발지의 목적지 정렬
    for (auto &kv : graph){
        auto &v = kv.second;
        sort(v.begin(), v.end());
    }

    // 3) 정렬 이후 visited 재구성 (간선 수에 맞춰 초기화)
    visited.clear();
    for (auto &kv : graph){
        visited[kv.first] = vector<bool>(kv.second.size(), false);
    }
}

// 찾으면 true를 반환해 상향 조기 종료
bool dfs(const string &cur, vector<string> &path, int cnt){
    path.push_back(cur);
    cnt++;

    if (cnt == total_cnt){
        answer = path;
        return true; // 완성 경로 발견 → 즉시 종료
    }

    auto it = graph.find(cur);
    if (it != graph.end()){
        auto &nexts = it->second;
        auto &vis = visited[cur];
        for (int i = 0; i < (int)nexts.size(); i++){
            if (!vis[i]){
                vis[i] = true;
                if (dfs(nexts[i], path, cnt)) return true; // 상향 전파
                vis[i] = false;
            }
        }
    }

    path.pop_back();
    return false;
}

vector<string> solution(vector<vector<string>> tickets) {
    // 전역 컨테이너 초기화
    graph.clear();
    visited.clear();
    answer.clear();

    init_data(tickets);

    vector<string> temp;
    if (graph.find("ICN") != graph.end()){
        dfs("ICN", temp, 0);
    }
    return answer;
}
