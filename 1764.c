#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v;
    int w;
} Edge;

typedef struct {
    int parent;
    int rank;
} DSU;

int find_set(DSU dsu[], int x) {
    if (dsu[x].parent != x)
        dsu[x].parent = find_set(dsu, dsu[x].parent);
    return dsu[x].parent;
}

void union_set(DSU dsu[], int a, int b) {
    a = find_set(dsu, a);
    b = find_set(dsu, b);
    if (a == b) return;

    if (dsu[a].rank < dsu[b].rank)
        dsu[a].parent = b;
    else if (dsu[b].rank < dsu[a].rank)
        dsu[b].parent = a;
    else {
        dsu[b].parent = a;
        dsu[a].rank++;
    }
}

int cmp(const void *a, const void *b) {
    int w1 = ((Edge*)a)->w;
    int w2 = ((Edge*)b)->w;
    return (w1 - w2);
}

int main() {
    int M, N;

    while (scanf("%d %d", &M, &N) == 2 && (M || N)) {

        Edge *edges = (Edge*) malloc(N * sizeof(Edge));

        for (int i = 0; i < N; i++) {
            scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        }

        qsort(edges, N, sizeof(Edge), cmp);

        DSU *dsu = (DSU*) malloc(M * sizeof(DSU));
        for (int i = 0; i < M; i++) {
            dsu[i].parent = i;
            dsu[i].rank = 0;
        }

        long long mst = 0;
        int edges_used = 0;

        for (int i = 0; i < N && edges_used < M - 1; i++) {
            if (find_set(dsu, edges[i].u) != find_set(dsu, edges[i].v)) {
                union_set(dsu, edges[i].u, edges[i].v);
                mst += edges[i].w;
                edges_used++;
            }
        }

        printf("%lld\n", mst);

        free(edges);
        free(dsu);
    }

    return 0;
}

