#include <stdio.h>
#include <string.h>

int main() {
    int R, K;
    while (scanf("%d %d", &R, &K) == 2) {
        int deg[101];
        memset(deg, 0, sizeof(deg));

        for (int i = 0; i < K; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            deg[a]++;
            deg[b]++;
        }

        static char dp[5001];
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;

        for (int i = 1; i <= R; i++) {
            int d = deg[i];
            for (int s = K; s >= d; s--) {
                if (dp[s - d]) dp[s] = 1;
            }
        }

        if (dp[K]) printf("S\n");
        else       printf("N\n");
    }

    return 0;
}
