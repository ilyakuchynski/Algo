#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 20;

int p[N], c[N], cn[N], pn[N], cnt[N];

int main(){
      ios_base :: sync_with_stdio(0);
      cin.tie(0); cout.tie(0);
      string s; cin >> s;
      s += "#";
      int n = s.size();
      for(const char& x : s)
            ++ cnt[x];
      for(int i = 1; i < 256; i ++)
            cnt[i] += cnt[i - 1];
      for(int i = 0; i < n; i ++)
            p[--cnt[s[i]]] = i;
      int cl = 0;
      for(int i = 1; i < n; i ++){
            if(s[p[i]] != s[p[i - 1]])
                  ++ cl;
            c[p[i]] = cl;
      }
      int k = 0;
      while((1 << k) < n){
            for(int i = 0; i < n; i ++){
                  pn[i] = p[i] - (1 << k);
                  if(pn[i] < 0)
                        pn[i] += n;
            }
            fill(cnt, cnt + cl + 1, 0);
            for(int i = 0; i < n; i ++)
                  ++ cnt[c[pn[i]]];
            for(int i = 1; i <= cl; i ++)
                  cnt[i] += cnt[i - 1];
            for(int i = n - 1; i >= 0; i --)
                  p[--cnt[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            cl = 0;
            for(int i = 1; i < n; i ++){
                  int m1 = (p[i] + (1 << k)) % n, m2 = (p[i - 1] + (1 << k)) % n;
                  if(c[p[i]] != c[p[i - 1]] || c[m1] != c[m2])
                        ++ cl;
                  cn[p[i]] = cl;
            }
            for(int i = 0; i < n; i ++)
                  c[i] = cn[i];
            ++ k;
      }
      for(int i = 0; i < n; i ++)
            cout << p[i] << " ";
}
