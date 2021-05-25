/**
Given a permutation {p[1], p[2] ... p[n]} of the set {1, 2, 3 ... n}, find for all i (1 <= i <= n) the number of indices (j), that respect the following conditions:
-> 1 <= j < i
-> p[j] < p[i]

Restrictions: 
-> 1 <= n <= 100.000
**/

#include <iostream>

using namespace std;

const int dim = 100000;
int n, tree[dim + 1];

void update(int p, int val) {
    for (int i = p; i <= n; i += ((i ^ (i - 1)) & i))
        tree[i] += val;
    return;
}

int query(int p) {
    int ret = 0;
    for (int i = p; i >= 1; i -= ((i ^ (i - 1)) & i))
        ret += tree[i];
    return ret;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1, x; i <= n; ++ i) {
        cin >> x;

        update(x, 1);

        cout << query(x - 1) << " ";
    }
    return 0;
}
