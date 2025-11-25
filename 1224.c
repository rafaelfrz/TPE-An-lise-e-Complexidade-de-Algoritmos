#include <stdio.h>

#define MAXN 10000

long long a[MAXN];
long long dpA[MAXN], dpW[MAXN];
long long nxtA[MAXN], nxtW[MAXN];

int main() {
    int N;
    while (scanf("%d", &N) == 1) {

        for (int i = 0; i < N; i++)
            scanf("%lld", &a[i]);

        for (int i = 0; i < N; i++) {
            dpA[i] = a[i];
            dpW[i] = 0;
        }

        for (int len = 2; len <= N; len++) {
            for (int L = 0; L + len <= N; L++) {
                int R = L + len - 1;

                // turno do Alberto
                long long x = a[L] + dpW[L + 1];
                long long y = a[R] + dpW[L];
                nxtA[L] = (x > y ? x : y);

                // turno do Wanderley
                long long m1 = dpA[L + 1];
                long long m2 = dpA[L];
                nxtW[L] = (m1 < m2 ? m1 : m2);
            }

            for (int i = 0; i + len <= N; i++) {
                dpA[i] = nxtA[i];
                dpW[i] = nxtW[i];
            }
        }

        printf("%lld\n", dpA[0]);
    }

    return 0;
}

