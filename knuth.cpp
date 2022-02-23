#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef LOCAL
#include "../debug.h"
#else
#define debug(...) 123
#endif

const int N = 1005, K = 51, inf = 1e9;

int dp[K][N][N], opt[K][N][N], a[N];

int main(){
      ios_base :: sync_with_stdio(0);
      cin.tie(0); cout.tie(0);
      int n, k;
      cin >> n >> k;
      for(int i = 1; i <= n; i ++)
            cin >> a[i];
      fill(**dp, **dp + K * N * N, inf);
      sort(a + 1, a + n + 1);
      for(int t = 0; t <= k; t ++)
            for(int i = 1; i <= n; i ++)
                  opt[t][0][i] = 1, opt[t][i][n + 1] = n;
      for(int i = 1; i <= n; i ++)
            dp[0][i][i] = 0, opt[0][i][i] = i;
      for(int t = 1; t <= k; t ++){
            for(int i = 1; i <= n; i ++){
                  for(int j = n; j >= 1; j --){
                        int L = opt[t][i - 1][j], R = opt[t][i][j + 1];
                        if(!L) L = i;
                        else L = max(L, i);
                        if(!R) R = j - 1;
                        else R = min(R, j);
                        for(int h = L; h <= R; h ++){
                              int v = dp[t - 1][i][h] + dp[t - 1][h + 1][j] + abs(a[j] - a[h]);
                              if(dp[t][i][j] > v){
                                    dp[t][i][j] = v;
                                    opt[t][i][j] = h;
                              }
                        }
                  }
            }
            for(int i = 0; i <= n + 1; i ++){
                  for(int j = 0; j <= n + 1; j ++){
                        if(dp[t - 1][i][j] < dp[t][i][j]){
                              dp[t][i][j] = dp[t - 1][i][j];
                              opt[t][i][j] = opt[t - 1][i][j];
                        }
                  }
            }
      }
      cout << dp[k][1][n];
}
