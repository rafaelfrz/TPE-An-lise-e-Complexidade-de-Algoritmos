#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    int u, v;
    double w;
} Edge;

typedef struct {
    int parent, rank;
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
    double w1 = (*(Edge*)a).w;
    double w2 = (*(Edge*)b).w;
    return (w1 < w2) ? -1 : (w1 > w2);
}

int main() {
    int C;
    scanf("%d", &C);

    while (C--) {
        int n;
        scanf("%d", &n);

        double x[500], y[500];
        for (int i = 0; i < n; i++)
            scanf("%lf %lf", &x[i], &y[i]);

        int m = n*(n-1)/2;
        Edge *edges = malloc(m * sizeof(Edge));

        int k = 0;
        for (int i = 0; i < n; i++)
            for (int j = i+1; j < n; j++) {
                double dx = x[i] - x[j];
                double dy = y[i] - y[j];
                double dist_cm = sqrt(dx*dx + dy*dy);
                edges[k].u = i;
                edges[k].v = j;
                edges[k].w = dist_cm / 100.0;
                k++;
            }

        qsort(edges, m, sizeof(Edge), cmp);

        DSU dsu[500];
        for (int i = 0; i < n; i++) {
            dsu[i].parent = i;
            dsu[i].rank = 0;
        }

        double mst = 0.0;
        int used = 0;

        for (int i = 0; i < m && used < n-1; i++) {
            if (find_set(dsu, edges[i].u) != find_set(dsu, edges[i].v)) {
                union_set(dsu, edges[i].u, edges[i].v);
                mst += edges[i].w;
                used++;
            }
        }

        printf("%.2f\n", mst);
        free(edges);
    }

    return 0;
}

