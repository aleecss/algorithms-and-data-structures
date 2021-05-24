/**
Given an array a with n elements and Q queries of two types:
"1 x y": a[x] becomes y (1 <= x <= n; 1 <= y <= 2.000.000.000)
"2 x y": returns the minimum element from the range a[x..y] (1 <= x <= y <= n)

Answer to all second type queries.

Restrictions:
-> 1 <= n, Q <= 100.000
**/

#include <iostream>
#include <cmath>

using namespace std;

const int INF = 0x3f3f3f3f, dim_1 = 200000, dim_2 = 500;

int n, Q, bucket, v[dim_1], b[dim_2];

void update(int pos, int val) {
    int bx = pos / bucket, res = INF;

    v[pos] = val;

    for (int i = bx * bucket; i < (bx + 1) * bucket; ++ i)
        res = min(res, v[i]);

    b[bx] = res;

    return;
}

int query(int l, int r) {
    int bx = l / bucket + 1, by = r / bucket - 1, res = INF;

    if (bx == by) {
        for (int i = l; i <= r; ++ i)
            res = min(res, v[i]);

        return res;
    }

    for (int i = bx; i <= by; ++ i)
        res = min(res, b[i]);

    for (int i = l; i < bx * bucket; ++ i)
        res = min(res, v[i]);

    for (int i = r; i >= (by + 1) * bucket; -- i)
        res = min(res, v[i]);

    return res;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    bucket = sqrt(n);

    for (int i = 0; i < dim_2; ++ i)
        b[i] = INF;

    for (int i = 0; i < n; ++ i) {
        cin >> v[i];

        b[i / bucket] = min(b[i / bucket], v[i]);
    }

    cin >> Q;

    for (int q = 1, t, x, y; q <= Q; ++ q) {
        cin >> t >> x >> y;

        if (t == 1) {
            -- x;
            -- y;

            cout << query(x, y) << "\n";
        }
        else {
            -- x;

            update(x, y);
        }
    }

    return 0;
}

/// Complexity: O(N + Q * sqrt N).
