/**
 * Author: Iurii Pustovalov
 * Date: 2022-11-08
 * Description: Calculating xor-convolution of 2 vectors modulo smth
 * Time: O(n\log(n))
 */
void fwht(vector<int>& a) {
  int n = a.size();
  for (int l = 1; l < n; l <<= 1) {
    for (int i = 0; i < n; i += 2 * l) {
      for (int j = 0; j < l; ++j) {
        int u = a[i + j], v = a[i + j + l];
        a[i + j] = add(u, v), a[i + j + l] = sub(u, v);
      }
    }
  }
}  // https://judge.yosupo.jp/problem/bitwise_xor_convolution
vector<int> xorconvo(vector<int> a, vector<int> b) {
  int n = 1;
  while (n < max(a.size(), b.size()))
    n *= 2;
  a.resize(n), b.resize(n);
  fwht(a), fwht(b);
  int in = inv(n);
  for (int i = 0; i < n; ++i)
    a[i] = mul(a[i], mul(b[i], in));
  fwht(a);
  return a;
}
