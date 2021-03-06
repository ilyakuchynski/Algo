#define Matrix vector<vector<ll>>
const ll mod = 1e9 + 7;

Matrix mult(Matrix a, Matrix b){
  if(a[0].size() != b.size())
    swap(a, b);
  assert(a[0].size() == b.size());
  Matrix res(a.size(), vector<ll>(b[0].size()));
  for(int i = 0; i < a.size(); i ++)
    for(int j = 0; j < b[0].size(); j ++)
      for(int k = 0; k < a[0].size(); k ++)
        (res[i][j] += a[i][k] * b[k][j]) %= mod;
  return res;
}

Matrix bpow(Matrix a, ll deg){
  if(deg == 1)
    return a;
  if(deg % 2)
    return mult(a, bpow(a, deg - 1));
  auto x = bpow(a, deg / 2);
  return mult(x, x);
}
