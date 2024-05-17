// gives index of new array if element was added into array.
// [0, 1, 2, 3, 4, 5]
// 0 -> 0, 1 -> 1, etc... (maps existing element to index)
// 0.5 -> 1, 1.5 -> 2, etc... (maps element in between elements to right index)
// -1 -> 0, 6 -> 6, etc...
// assumes elements in array are unique.

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

typedef vector<int> vi;
typedef vector<ll> vl;

#define REP(i, x) for (int i = 0; i < (x); i++)

int binary_search_helper (vl &a, ll x, int lo, int hi) {
    // a.size() >= 2
    if (lo + 1 == hi) {
        if (x <= a[lo]) return lo;
        if (x <= a[hi]) return hi;
        return hi + 1;
    }
    int mid = (hi + lo) / 2;
    if (x < a[mid]) {
        return binary_search_helper(a, x, lo, mid);
    } else if (x > a[mid]) {
        return binary_search_helper(a, x, mid, hi);
    } else {
        return mid;
    }
}

int binary_search (vl &a, ll x) {
    if (!a.size()) return 0;
    if (x < a[0]) return 0;
    if (x > a[a.size() - 1]) return a.size();
    if (a.size() == 1) return 0;
    return binary_search_helper(a, x, 0, a.size() - 1);
}

int main () {
    int n;
    cin >> n;
    vl a (n);
    REP (i, n) cin >> a[i];
    int q;
    cin >> q;
    ll x;
    REP (i, q) {
        cin >> x;
        cout << binary_search(a, x) << endl;
    }
}