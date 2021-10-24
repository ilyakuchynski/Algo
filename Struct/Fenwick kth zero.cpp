#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Fenwick{
      vector<int> f;
      int n;
      void init(int _){
            n = _;
            f.resize(n + 1);
      }
      void upd(int pos, int x){
            for(; pos <= n; pos += pos & -pos){
                  f[pos] += x;
            }
      }
      int sum(int r){
            int ret = 0;
            for(; r > 0; r -= r & -r)
                  ret += f[r];
            return ret;
      }
      int sum(int l, int r){
            return sum(r) - sum(l - 1);
      }
      int kth(int k, int r){
            int j = 0;
            for(int i = 18; i >= 0; i --){
                  if(j + (1 << i) <= n && f[j + (1 << i)] < k){
                        k -= f[j + (1 << i)];
                        j += (1 << i);
                  }
            }
            ++ j;
            if(j > r)
                  return -1;
            return j;
      }
};

int main(){
      ios_base :: sync_with_stdio(0);
      cin.tie(0); cout.tie(0);
      int n; cin >> n;
      Fenwick t;
      t.init(n);
      vector<int> a(n + 1);
      for(int i = 1; i <= n; i ++){
            cin >> a[i];
            if(a[i] == 0)
                  t.upd(i, 1);
      }
      int q; cin >> q;
      while(q --){
            char tp; cin >> tp;
            if(tp == 's'){
                  int l, r, k;
                  cin >> l >> r >> k;
                  k += t.sum(1, l - 1);
                  cout << t.kth(k, r) << "\n";
            }else{
                  int p, x;
                  cin >> p >> x;
                  if(a[p] == 0)
                        t.upd(p, -1);
                  a[p] = x;
                  if(a[p] == 0)
                        t.upd(p, +1);
            }
      }
}
