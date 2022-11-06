/**
 * Author: Igor Markelov
 * Date: 2022-11-05
 * Source: https://github.com/zemen/Jinotega-notebook/blob/master/algo/structures/ordered_set.cpp
 * Description: A set (not multiset!) with support for finding the n'th
 * element, and finding the index of an element.
 * To get a map, change \texttt{null\_type}.
 * Time: O(\log N)
 */

#include <ext/pb_ds/assoc_container.hpp> /** keep-include */
#include <ext/pb_ds/tree_policy.hpp>     /** keep-include */

typedef __gnu_pbds::tree<int, __gnu_pbds::null_type, std::less<int>, __gnu_pbds::rb_tree_tag,
                         __gnu_pbds::tree_order_statistics_node_update>
    oset;

#include <iostream> /** keep-include */

int main() {
  oset X;
  X.insert(1);
  X.insert(2);
  X.insert(4);
  X.insert(8);
  X.insert(16);

  std::cout << *X.find_by_order(1) << std::endl;  // 2
  std::cout << *X.find_by_order(2) << std::endl;  // 4
  std::cout << *X.find_by_order(4) << std::endl;  // 16
  std::cout << std::boolalpha << (end(X) == X.find_by_order(6)) << std::endl;  // true

  std::cout << X.order_of_key(-5) << std::endl;   // 0
  std::cout << X.order_of_key(1) << std::endl;    // 0
  std::cout << X.order_of_key(3) << std::endl;    // 2
  std::cout << X.order_of_key(4) << std::endl;    // 2
  std::cout << X.order_of_key(400) << std::endl;  // 5
}