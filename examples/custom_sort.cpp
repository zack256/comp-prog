#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;

#define REP(i, x) for (int i = 0; i < (x); i++)

struct Z {

    int a;
    int b;
    int c;

    Z (int a_, int b_, int c_) : a(a_), b(b_), c(c_) {}

    bool operator < (const Z &other) const {
        // Sort by b, then reversed by c, then by a.
        if (b == other.b) {
            if (c == other.c) {
                return a < other.a;
            }
            return c > other.c;
        }
        return b < other.b;
    }

};

void print_Z (Z z) {
    cout << "<" << z.a << "," << z.b << "," << z.c << ">";
}

void print_Zs (vector<Z> &zs) {
    REP (i, zs.size()) {
        print_Z(zs[i]);
        cout << " ";
    }
    cout << endl;
}

int main () {
    vi a_vals = { 2, 1, 4, 3, 5, 9, 3, 6, 1 };
    vi b_vals = { 4, 7, 1, 6, 4, 6, 4, 2, 4 };
    vi c_vals = { 3, 3, 8, 2, 7, 8, 7, 5, 7 };
    int n = a_vals.size();
    vector<Z> zs;
    REP (i, n) zs.push_back(Z(a_vals[i], b_vals[i], c_vals[i]));
    print_Zs(zs);
    sort(zs.begin(), zs.end());
    print_Zs(zs);
}