/**
Given an array a with n elements and Q queries of two types:
"1 x y": a[x] becomes y (1 <= x <= n; 1 <= y <= 2.000.000.000)
"2 x y": returns the minimum element from the range a[x..y] (1 <= x <= y <= n)

Answer to all second type queries.

Restrictions:
-> 1 <= n, Q <= 100.000
**/

#include <iostream>
#include <vector>

using namespace std;

const int INF = 0x3f3f3f3f, dim = 100000;

int n, Q, v[dim], tree[(dim << 2)];

void construct(int node, int l, int r) {
    if (l == r) {
        tree[node] = v[l];
        return;
    }
    else {
        int mid = ((l + r) >> 1);

        construct((node << 1) + 1, l, mid);
        construct((node << 1) + 2, mid + 1, r);

        tree[node] = min(tree[(node << 1) + 1], tree[(node << 1) + 2]);

        return;
    }
}

void update(int node, int l, int r, int pos, int val) {
    if (l == r) {
        tree[node] = val;
        return;
    }
    else {
        int mid = ((l + r) >> 1);

        if (l <= pos && pos <= mid) {
            update((node << 1) + 1, l, mid, pos, val);
        }
        else {
            update((node << 1) + 2, mid + 1, r, pos, val);
        }

        tree[node] = min(tree[(node << 1) + 1], tree[(node << 1) + 2]);
        return;
    }
    return;
}

int query(int node, int l, int r, int x, int y) {
    if (r < x || l > y)
        return INF;
    else {
        if (x <= l && r <= y)
            return tree[node];

        int mid = ((l + r) >> 1);

        return min(query((node << 1) + 1, l, mid, x, y), query((node << 1) + 2, mid + 1, r, x, y));
    }
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
	
    cin >> n;

    for (int i = 0; i < n; ++ i)
        cin >> v[i];

    for (int i = 0; i < (n << 2); ++ i)
        tree[i] = INF;

    construct(0, 0, n - 1);

    cin >> Q;

    for (int q = 0, t, x, y; q < Q; ++ q) {
        cin >> t >> x >> y;

        if (t == 1) {
            -- x;
            -- y;

            cout << query(0, 0, n - 1, x, y) << "\n";
        }
        else {
            -- x;

            update(0, 0, n - 1, x, y);
        }
    }
    return 0;
}

