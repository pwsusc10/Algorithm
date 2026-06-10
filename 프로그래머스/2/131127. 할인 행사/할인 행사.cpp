#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// 원하는 항목을 모두 살 수 있는 지 확인하는 함수
bool check_products(map<string, int> products){
    for(const auto& pair: products){
        if(pair.second > 0)
            return false;
    }
    return true;
}

int solution(vector<string> want, vector<int> number, vector<string> discount) {
    int answer = 0;
    bool debug = false;

    map<string, int> products;

    // 구매를 원하는 products 저장
    for(int i = 0; i < want.size(); i++){
        products.insert(make_pair(want[i], number[i]));
    }

    if(debug) {
        for(const auto& pair: products) {
            cout << pair.first << ", " << pair.second << endl;
        }
    }

    // 첫날부터 10일간의 세일 항목 저장.
    int next_day;
    for(int i = 0; i < 10; i++){
        if(products.find(discount[i]) != products.end())
            products[discount[i]]--;
    }

    for(int day = 0; day < discount.size(); day++){
        // 구매항목 확인
        if(check_products(products))
            answer++;

        // 다음날 처리 로직
        if(products.find(discount[day]) != products.end())
            products[discount[day]]++;

        next_day = day + 10;
        if(next_day < discount.size() && products.find(discount[next_day]) != products.end())
            products[discount[next_day]]--;
    }



    return answer;
}