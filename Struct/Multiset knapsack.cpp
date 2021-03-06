const int N = 1e3;
const int mod = 1e9 + 7;
int dp[N + 1];

void add(int x){
  for(int i = N - x; i >= 0; i --){
    dp[i + x] += dp[i];
    if(dp[i + x] >= mod)
      dp[i + x] -= mod;
  }
}

void rem(int x){
  for(int i = x; i <= N; i ++){
    dp[i] -= dp[i - x];
    if(dp[i] < 0)
      dp[i] += mod;
  }
}

dp[0] = 1
