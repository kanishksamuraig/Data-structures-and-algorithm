#include <bits/stdc++.h>
using namespace std;

int coinChange(vector<int> &coins, int amount)
{
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    for (int coin : coins)
        for (int j = coin; j <= amount; j++)
            if (dp[j - coin] != INT_MAX)
                dp[j] = min(dp[j], dp[j - coin] + 1);
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

void activitySelection(vector<pair<int, int>> &activities)
{
    sort(activities.begin(), activities.end(), [](pair<int, int> a, pair<int, int> b)
         { return a.second < b.second; });
    int lastFinish = 0;
    cout << "Selected activities:\n";
    for (auto &act : activities)
    {
        if (act.first >= lastFinish)
        {
            cout << act.first << " - " << act.second << "\n";
            lastFinish = act.second;
        }
    }
}

int main()
{
    int choice;
    do
    {
        cout << "\nChoose Algorithm:\n";
        cout << "1. Coin Change\n2. Activity Selection\n0. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            vector<int> coins = {1, 2, 5};
            int amount;
            cout << "Enter amount: ";
            cin >> amount;
            cout << "Minimum coins required: " << coinChange(coins, amount) << "\n";
        }
        else if (choice == 2)
        {
            int n;
            cout << "Enter number of activities: ";
            cin >> n;
            vector<pair<int, int>> activities(n);
            cout << "Enter start and finish times:\n";
            for (int i = 0; i < n; i++)
                cin >> activities[i].first >> activities[i].second;
            activitySelection(activities);
        }
    } while (choice != 0);
    return 0;
}
