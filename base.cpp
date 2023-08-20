#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;

typedef vector<int> vi;
typedef vector<ll> vl;

#define mp make_pair
#define pb push_back

#define REP(i, x) for (int i = 0; i < (x); i++)

template<typename T>
void print_vector (vector<T> &v, bool commas = false) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
        if (commas) cout << ",";
        cout << " ";
    }
    cout << endl;
}

template<typename T>
void print_2d_matrix (vector<vector<T>> &v, bool commas = false) {
    for (int i = 0; i < v.size(); i++) print_vector(v[i], commas);
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t, i, j;
    cin >> t;
    while (t--) {
    }
}