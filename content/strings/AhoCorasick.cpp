/**
 * Author: Igor Markelov (stole from emaxx-algo)
 * Date: 2022-11-18
 * Description: Build aho-corasick automaton.
 * Time: O(n)
 */

int go(int v, char c);

int get_link(int v) {
  if (t[v].link == -1)
    if (v == 0 || t[v].p == 0)
      t[v].link = 0;
    else
      t[v].link = go(get_link(t[v].p), t[v].pch);
  return t[v].link;
}

int go(int v, char c) {
  if (t[v].go[c] == -1)
    if (t[v].next[c] != -1)
      t[v].go[c] = t[v].next[c];
    else
      t[v].go[c] = v == 0 ? 0 : go(get_link(v), c);
  return t[v].go[c];
}
