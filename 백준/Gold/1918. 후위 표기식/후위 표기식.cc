#include <iostream>
#include <stack>
#include <string>
using namespace std;

string origin_str;

bool is_alphabet(char ch){
    return (ch >= 'A' && ch <= 'Z');
}

int calculate_priority(char ch) {
    if(ch == '+' || ch == '-') return 1;
    if(ch == '*' || ch == '/') return 2;
    return 0; // '('는 우선순위 0으로 취급
}

void solution(){
    stack<char> opt_str;

    for(char ch : origin_str){
        if(is_alphabet(ch)){
            cout << ch;
        }
        else if(ch == '('){
            opt_str.push(ch);
        }
        else if(ch == ')'){
            while(!opt_str.empty() && opt_str.top() != '('){
                cout << opt_str.top();
                opt_str.pop();
            }
            if(!opt_str.empty()) opt_str.pop(); // '(' 제거
        }
        else { // 연산자 처리
            while(!opt_str.empty() && calculate_priority(opt_str.top()) >= calculate_priority(ch)){
                cout << opt_str.top();
                opt_str.pop();
            }
            opt_str.push(ch);
        }
    }

    // 남은 연산자 출력
    while(!opt_str.empty()){
        cout << opt_str.top();
        opt_str.pop();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> origin_str;
    solution();

    return 0;
}
