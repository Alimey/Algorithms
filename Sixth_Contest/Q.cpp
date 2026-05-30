#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n;
    long long k;
    cin >> n >> k;

    vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }

    // Map to store DP states for each x-coordinate
    map<int, vector<int>> dp;
    dp[0] = vector<int>(17, 0); // y-coordinates from 0 to 16
    dp[0][0] = 1; // Starting point

    for (int i = 1; i <= n; i++) {
        map<int, vector<int>> new_dp;
        for (int x = a[i - 1]; x <= b[i - 1]; x++) {
            new_dp[x] = vector<int>(17, 0);
        }

        for (auto &[x, counts] : dp) {
            if (x < a[i - 1] || x > b[i - 1]) continue;
            for (int y = 0; y <= 16; y++) {
                if (y <= c[i - 1]) continue; // Restricted area
                
                // Transitions
                if (y > 0) {
                    new_dp[x + 1][y - 1] = (new_dp[x + 1][y - 1] + counts[y]) % MOD;
                }
                new_dp[x + 1][y] = (new_dp[x + 1][y] + counts[y]) % MOD;
                if (y < 16) {
                    new_dp[x + 1][y + 1] = (new_dp[x + 1][y + 1] + counts[y]) % MOD;
                }
            }
        }

        dp = move(new_dp); // Update DP to the next layer
    }

    // Calculate final result
    long long result = 0;
    for (int y = 0; y <= 16; y++) {
        if (y > c[n - 1]) { // Проверка на запрещенную область для последнего сегмента
            result = (result + dp[k][y]) % MOD;
        }
    }


    cout << result << endl;
    return 0;
}
