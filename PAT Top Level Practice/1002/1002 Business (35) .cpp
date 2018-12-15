#include <iostream>
#include <algorithm>
using namespace std;

typedef struct pnode {
    int profit;
    int lasting_days;
    int deadline;
} * Project;

bool compare(pnode a, pnode b) {
    return a.deadline < b.deadline;
}

int main()
{
    int n;
    cin >> n;
    Project p = new pnode[n + 1];
    for (int i = 1; i < n + 1; i ++) {
        cin >> p[i].profit >> p[i].lasting_days >> p[i].deadline;
    }
    sort(p + 1, p + n + 1, compare);
    int last_deadline = p[n].deadline;
    int **dp = new int * [n + 1];
    //dp[i][j]表示对前i个项目，在时间j前能获得的最大利润
    for (int i = 0; i < n + 1; i ++) {
        dp[i] = new int[last_deadline + 1];
        dp[i][0] = 0;
    }
    fill(dp[0], dp[0] + last_deadline + 1, 0);    
    for (int i = 1; i < n + 1; i ++)
        for (int j = 1; j <= last_deadline; j ++) {
            if (j < p[i].lasting_days)
                dp[i][j] = dp[i - 1][j];
            else if (j <= p[i].deadline) 
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - p[i].lasting_days] + p[i].profit);
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][p[i].deadline]);
        }
    cout << dp[n][last_deadline] << endl;
    return 0;
}
