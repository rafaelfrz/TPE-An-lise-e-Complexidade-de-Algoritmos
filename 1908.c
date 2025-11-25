#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 120000
#define INF 0x3f3f3f3f

typedef struct {
    int to;
    int w;
    int next;
} Edge;

Edge edges[200000];
int head[MAXN];
int ec = 0;

void add_edge(int u, int v, int w) {
    edges[ec].to = v;
    edges[ec].w = w;
    edges[ec].next = head[u];
    head[u] = ec++;
}

int deque[MAXN];
int dq_front, dq_back;

int dist[MAXN];

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    for (int i = 0; i < N + K + 5; i++) head[i] = -1;
    ec = 0;

    for (int i = 0; i < K; i++) {
        int L;
        scanf("%d", &L);

        int line_node = N + i;
        for (int j = 0; j < L; j++) {
            int c;
            scanf("%d", &c);
            c--;

            add_edge(c, line_node, 1);

            add_edge(line_node, c, 0);
        }
    }

    int total_nodes = N + K;

    for (int i = 0; i < total_nodes; i++)
        dist[i] = INF;

    dq_front = dq_back = 0;

    dist[0] = 0;
    deque[dq_back++] = 0;

    while (dq_front != dq_back) {
        int u = deque[dq_front++];
        if (dq_front >= MAXN) dq_front = 0;

        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            int w = edges[e].w;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;

                if (w == 0) {
                    dq_front = (dq_front == 0 ? MAXN - 1 : dq_front - 1);
                    deque[dq_front] = v;
                } else {
                    deque[dq_back] = v;
                    dq_back = (dq_back + 1) % MAXN;
                }
            }
        }
    }

    printf("%d\n", dist[N-1]);

    return 0;
}

