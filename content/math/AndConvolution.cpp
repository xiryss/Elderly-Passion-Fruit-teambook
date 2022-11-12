/**
 * Author: Iurii Pustovalov
 * Date: 2022-11-08
 * Description: Calculating and-convolution modulo smth
 * Time: O(n\log(n))
 */
void conv(vector<int>& a, bool x) {
  int n = a.size();
  for (int j = 0; (1 << j) < n; ++j) {
    for (int i = 0; i < n; ++i) {
      if (!(i & (1 << j))) {
        if (x)
          a[i] = add(a[i], a[i | (1 << j)]);
        else
          a[i] = sub(a[i], a[i | (1 << j)]);
      }
    }
  }
}  // https://judge.yosupo.jp/problem/bitwise_and_convolution
vector<int> andcon(vector<int> a, vector<int> b) {
  int n = 1;
  while (n < max(a.size(), b.size()))
    n *= 2;
  a.resize(n), b.resize(n);
  conv(a, 1), conv(b, 1);
  for (int i = 0; i < n; ++i)
    a[i] = mul(a[i], b[i]);
  conv(a, 0);
  return a;
}
