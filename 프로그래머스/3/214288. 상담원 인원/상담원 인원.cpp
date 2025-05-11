
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;


struct Waiting {
  int start;
  int time;
  
  Waiting(int start, int time) : start(start), time(time) {}
  
  bool operator<(const Waiting &right) const {
    return start > right.start;
  }
};

vector<priority_queue<Waiting> > list;
vector<vector<int> > mentors;
int max_waiting_time = 21e8;

// 1. 입력 처리.
void input_data(int k, vector<vector<int>> &reqs) {
  
  list.resize(k + 1);
  mentors.resize(k + 1);
  
  // 1.1. 신청 시각을 기준으로 정렬.
  for(int i = 0; i < reqs.size(); i++) {
    list[reqs[i][2]].push(Waiting(reqs[i][0], reqs[i][1]));
  }
}

// 2.1. 참여자들의 대기 시간 계산.
void calculate_waiting_time(int k) {
  int waiting_time = 0;
  vector<priority_queue<Waiting> > waiting_list = list;
  vector<vector<int> > temp_mentors = mentors;

  for(int i = 1; i <= k; i++){
    while(!waiting_list[i].empty()) {
      Waiting waiting = waiting_list[i].top();
      waiting_list[i].pop();

      // 2.1.1. 가장 빠른 멘토 idx 찾기.
      int fast_mentor_idx = 0;
      for(int j = 0; j < temp_mentors[i].size(); j++) {
        if (temp_mentors[i][j] < temp_mentors[i][fast_mentor_idx]) {
          fast_mentor_idx = j;
        }
      }
      // 2.1.2. 빠른 멘토와 매칭.
      // cout << "waiting.start: " << waiting.start << ", waiting.time: " << waiting.time << endl;
      // cout << "mentors[i][fast_mentor_idx]: " << mentors[i][fast_mentor_idx] << endl;
      if(temp_mentors[i][fast_mentor_idx] > waiting.start) {
        // cout << "add waiting_time: " << temp_mentors[i][fast_mentor_idx] - waiting.start << endl;
        waiting_time += (temp_mentors[i][fast_mentor_idx] - waiting.start);
        temp_mentors[i][fast_mentor_idx] += waiting.time;
      }else {
        temp_mentors[i][fast_mentor_idx] = waiting.start + waiting.time;
      }
      // cout << "after mentors[i][fast_mentor_idx]: " << mentors[i][fast_mentor_idx] << "\n-------------------\n";
    }
  }
  
  // 2.2. 대기 시간의 최솟값을 갱신.
  max_waiting_time = min(max_waiting_time, waiting_time);
}

// 2. 재귀로 유형별 멘토 인원 분배. <= O(4 * 10^3)
void make_mentor_group (int k, int idx, int rest) {
  if (idx > k) {
    calculate_waiting_time(k);

    // for(int i = 1; i <= k; i++) 
    //   cout << mentors[i].size() << " ";
  }else if (idx == k) {
    mentors[idx].resize(rest, 0);
    make_mentor_group(k, idx + 1, 0);
    mentors[idx].clear(); 
  } else {
    for(int i = 1; i <= rest - (k - idx); i++) {
      mentors[idx].resize(i, 0);
      make_mentor_group(k, idx + 1, rest - i);
      mentors[idx].clear();
    }
  }
}

int solution(int k, int n, vector<vector<int>> reqs) {
  input_data(k, reqs);
  make_mentor_group(k, 1, n);
  
  // 3. 대기 시간의 최솟값을 출력.
  return max_waiting_time;
}