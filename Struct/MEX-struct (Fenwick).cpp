#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef LOCAL
#include "../debug.h"
#else
#define debug(...) 123
#endif

const int N = 2e5 + 20;
int f[N], cnt[N], n;

void upd(int pos, int x){
      cnt[pos] += x;
      if(cnt[pos] == 0 || cnt[pos] == 1){
            for(; pos <= n; pos += pos & -pos)
                  f[pos] += x;
      }
}

int mex(){
      int l = 0, s = 0;
      for(int j = 18; j >= 0; j --){
            if(l + (1 << j) <= n && f[l + (1 << j)] == (1 << j)){
                  l += (1 << j);
                  s += f[l];
            }
      }
      return l + 1;
}

int main() {
      ios_base :: sync_with_stdio(0);
      cin.tie(0); cout.tie(0);
      n = 100;
      upd(2, 1);
      upd(1, 1);
      upd(4, 1);
      upd(3,1);
      cout << mex();
}
