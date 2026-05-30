#include <iostream>
#include <vector>
using namespace std;

// Функция для проверки, дружат ли два числа
bool are_friends(int a, int b) {
    return abs(a - b) < min(a, b) * 2;
}

int count_friend_sets(int n) {
    // dp[i] хранит количество способов получить сумму i
    vector<vector<int>> dp(n + 1);
    dp[0].push_back(0);  // Пустое множество для суммы 0
    
    // Перебираем числа от 1 до n
    for (int num = 1; num <= n; ++num) {
        // Для каждой суммы, которую мы уже можем составить
        for (int sum = n; sum >= num; --sum) {
            // Для каждого существующего подмножества этой суммы
            for (auto subset : dp[sum - num]) {
                // Проверяем, можем ли добавить num в подмножество
                bool valid = true;
                for (int x : dp[subset]) {
                    if (!are_friends(x, num)) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    dp[sum].push_back(subset);
                }
            }
        }
    }

    return dp[n].size();
}

int main() {
    int n;
    cin >> n;
    cout << count_friend_sets(n) << endl;
    return 0;
}
