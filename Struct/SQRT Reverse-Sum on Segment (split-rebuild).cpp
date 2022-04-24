#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef LOCAL
#include "../debug.h"
#else
#define debug(...) 123
#endif

const int N = 2e5 + 20;
const int B = 400;

int a[N], b[N], n;
list<tuple<int, int, ll>> v;

void build(){
      for(int i = 0; i < n; i += B){
            ll sum = 0;
            for(int j = i; j <= min(i+B-1,n-1); j ++)
                  sum += a[j];
            v.emplace_back(i, min(i+B-1,n-1), sum);
      }
}

void rebuild(){
      int j = 0;
      for(auto [x, y, z] : v){
            int s = (x < y ? +1 : -1);
            for(int i = x; i != y; i += s){
                  b[j++] = a[i];
            }
            b[j++] = a[y];
      }
      for(int i = 0; i < n; i ++)
            a[i] = b[i];
      v.clear();
      build();
}

void split(int d){
      if(!d)
            return;
      int j = 0;
      for(auto it = v.begin(); it != v.end(); ++ it){
            auto [x, y, z] = *it;
            j += abs(x - y) + 1;
            if(j == d)
                  break;
            if(j < d)
                  continue;
            int t = j - d, w = (x < y ? -1 : +1);
            get<0>(*it) = y + w * (t - 1);
            ll nz = a[y];
            for(int k = y + w * (t - 1); k != y; k -= w)
                  nz += a[k];
            get<2>(*it) = nz;
            v.insert(it, make_tuple(x, y + w * t, z - nz));
            break;
      }
}

void rev(int l, int r){
      split(l-1);
      split(r);
      auto L = v.begin();
      int j = 0;
      for(; j + 1 != l; ++ L)
            j += abs(get<0>(*L)-get<1>(*L))+1;
      auto R = L;
      for(; j + abs(get<0>(*R)-get<1>(*R))+1 != r; ++ R)
            j += abs(get<0>(*R)-get<1>(*R))+1;
      while(true){
            if(L == R){
                  swap(get<0>(*L), get<1>(*L));
                  return;
            }
            auto x = *L;
            auto y = *R;
            *L = y;
            *R = x;
            swap(get<0>(*L), get<1>(*L));
            swap(get<0>(*R), get<1>(*R));
            ++ L;
            if(L == R)
                  break;
            -- R;
      }
}

ll query(int l, int r){
      split(l-1);
      split(r);
      ll sum = 0;
      auto L = v.begin();
      int j = 0;
      for(; j + 1 != l; ++ L)
            j += abs(get<0>(*L)-get<1>(*L))+1;
      for(; j + abs(get<0>(*L)-get<1>(*L))+1 != r; ++ L){
            j += abs(get<0>(*L)-get<1>(*L))+1;
            sum += get<2>(*L);
      }
      sum += get<2>(*L);
      return sum;
}

int main() {
      ios_base :: sync_with_stdio(0);
      cin.tie(0); cout.tie(0);
      int q;
      cin >> n >> q;
      for(int i = 0; i < n; i ++)
            cin >> a[i];
      build();
      int cnt = 0;
      while(q --){
            int tp, l, r;
            cin >> tp >> l >> r;
            if(tp == 0){
                  cout << query(l, r) << "\n";
            }else{
                  rev(l, r);
            }
            ++ cnt;
            if(cnt > B){
                  cnt = 0;
                  rebuild();
            }
      }
}
