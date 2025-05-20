#include <iostream>
#include <iomanip>
#include <sstream>

#include <cstdio>
#include <cstring>
#include <string>

#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>
#include <stack>

#include <algorithm>
#include <cmath>
#include <functional>
#include <limits>

#define REP(i, n) for (int (i) = 0; (i) < (int)(n); (i)++)
#define FOR(i, a, b) for (int (i) = (int)(a); (i) <= (int)(b); (i)++)
#define FORD(i, a, b) for (int (i) = (int)(a); (i) >= (int)(b); (i)--)

constexpr double eps = 1e-5;
template<class T> auto eq_float(T left, T right) -> bool { return abs(left - right) < eps; }

using namespace std;

using uint_64 = unsigned long long;
using int_64 = long long;
using uint = unsigned int;
using uint_8 = unsigned char;
