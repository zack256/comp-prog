#include <iostream>

using namespace std;

typedef long long ll;

ll linear_exponentiation (ll b, ll x, ll mod) {
    b %= mod;
    ll res = 1;
    while (x--) {
        res *= b;
        res %= mod;
    }
    return res;
}

ll binary_exponentiation_recursive (ll b, ll x, ll mod) {
    b %= mod;
    if (!x) return 1;
    ll half_powered = binary_exponentiation_recursive(b, x / 2, mod);
    ll res = x % 2 ? b % mod : 1;
    res *= half_powered; res %= mod;
    res *= half_powered; res %= mod;
    return res;
}

ll binary_exponentiation_iterative (ll b, ll x, ll mod) {
    b %= mod;
    ll res = 1;
    ll a = b;
    while (x) {
        if (x % 2) {
            res *= a;
            res %= mod;
        }
        a *= a;
        a %= mod;
        x /= 2;
    }
    return res;
}

int main () {
    ll t, b, x, mod;
    cin >> t;
    while (t--) {
        cin >> b >> x >> mod;
        cout << linear_exponentiation(b, x, mod) << endl;
        cout << binary_exponentiation_recursive(b, x, mod) << endl;
        cout << binary_exponentiation_iterative(b, x, mod) << endl;
    }
}