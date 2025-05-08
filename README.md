# Algorithm

Algorithm 정리 및 문제 풀이 기록

## Dynamic Programming
[BOJ-12920](/백준/Platinum/12920. 평범한 배낭 2/) 평범한 배낭 2
- 기본적인 배낭(knapsack)문제는 O(N * W)로 해결 가능하다.
  - N : item 수
  - W : 배낭의 최대 무게
- item의 개수가 여러 개라면 O(N * W * K)로 해결 가능하다.
  - K : 물건의 개수 
- O(N * W * K)는 시간 초과에 걸릴 가능성이 높다. 모든 수는 이진수 변환이 가능함으로 이를 활용해 package함으로써, O(N * W * logk)로 해결이 가능하다.
  - weight : 3, value : 2, count : 13인 item이 있다고 하자.
  - 11 => 0b1101이므로 해당 아이템을 8, 4, 2, 1개로 package할 수 있다.
    - 하지만 8, 4, 2, 1을 모두 담는 다면, 15개로 가진 count를 초과할 수 있다.
    - 이를 처리하기 위한 기법은 다음과 같다.
        ```cpp
        for (int i = cnt; i > 0; i >>= 1) {
            int num = i - (i >> 1);
            items.push_back({ weight * num, value * num });
        }
        ```
        1. 15 - 6 => 9
        2. 6 - 3 => 3
        3. 3 - 1 => 1
    - 이처럼 K를 logK로 만들어 해결할 수 있다.
    - 다음과 같이 packaging한다면, "package한 item과 같은 입력이 들어오면 안되는 것 아닌가"라고 생각할 수 있지만 중복을 제거하기 위해서 packaging하는 것이 아닌 item의 개수를 줄이기 위함이다.
## Segment Tree

[BOJ-6549](/백준/Platinum/6549. 히스토그램에서 가장 큰 직사각형/) 히스토그램에서 가장 큰 직사각형

- 단순히 구간별 최소 높이를 저장하는 것이 아니라, 최소 높이의 인덱스를 저장함으로써 해당 구간을 나누어 분할 정복(Divide & Conquer) 방식으로 접근할 수 있었다.
