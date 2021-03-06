struct Line{
  ll k, b;
  mutable ll p;
  bool operator< (const Line& o) const {
    return k < o.k;
  }
  bool operator< (const ll& x) const {
    return p < x;
  }
};

struct ConvexHull : multiset<Line, less<>>{
  const ll inf = 1e18;
  ll dv(ll a, ll b){
    return a / b - (a % b && (a ^ b) < 0);
  }
  bool bad(iterator x, iterator y){
    if(y == end()){
      x->p = inf;
      return false;
    }
    if(x->k == y->k)
      x->p = (x->b > y->b ? inf : -inf);
    else
      x->p = dv(x->b - y->b, y->k - x->k);
    return x->p >= y->p;
  }
  void add(ll k, ll b){
    auto z = insert({k, b, 0}), y = z ++, x = y;
    while(bad(y, z))
      bad(y, z = erase(z));
    if(x != begin() && bad(--x, y))
      bad(x, erase(y));
    while((y = x) != begin() && bad(--x, y))
      bad(x, erase(y));
  }
  ll query(ll x){
    assert(!empty());
    auto it = lower_bound(x);
    return it->k * x + it->b;
  }
};
