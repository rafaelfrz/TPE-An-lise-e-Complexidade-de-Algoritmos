#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXC 10000
#define MAXV 50000
#define INF 0x3f3f3f3f

typedef struct {
    int v, w, next;
} Edge;

Edge edges[2 * MAXV * 2];
int head[2 * MAXC + 5];
int ec;

void add_edge(int u, int v, int w) {
    edges[ec].v = v;
    edges[ec].w = w;
    edges[ec].next = head[u];
    head[u] = ec++;
}

typedef struct {
    int node;
    int dist;
} HeapNode;

HeapNode heap[400000];
int hsize;

void heap_swap(int a, int b) {
    HeapNode t = heap[a];
    heap[a] = heap[b];
    heap[b] = t;
}

void heap_push(int node, int dist) {
    int i = ++hsize;
    heap[i].node = node;
    heap[i].dist = dist;

    while (i > 1 && heap[i].dist < heap[i/2].dist) {
        heap_swap(i, i/2);
        i /= 2;
    }
}

HeapNode heap_pop() {
    HeapNode top = heap[1];
    heap[1] = heap[hsize--];

    int i = 1;
    while (1) {
        int l = 2*i, r = l+1, smallest = i;
        if (l <= hsize && heap[l].dist < heap[smallest].dist) smallest = l;
        if (r <= hsize && heap[r].dist < heap[smallest].dist) smallest = r;
        if (smallest == i) break;
        heap_swap(i, smallest);
        i = smallest;
    }
    return top;
}

int dist[2 * MAXC + 5];

int main() {
    int C, V;

    while (scanf("%d %d", &C, &V) == 2) {

        for (int i = 0; i < 2*C; i++) head[i] = -1;
        ec = 0;

        for (int i = 0; i < V; i++) {
            int a, b, g;
            scanf("%d %d %d", &a, &b, &g);
            a--; b--;

            add_edge(a*2 + 0, b*2 + 1, g);
            add_edge(a*2 + 1, b*2 + 0, g);
            add_edge(b*2 + 0, a*2 + 1, g);
            add_edge(b*2 + 1, a*2 + 0, g);
        }

        int total_nodes = 2*C;
        for (int i = 0; i < total_nodes; i++) dist[i] = INF;

        hsize = 0;
        dist[0] = 0;
        heap_push(0, 0);

        while (hsize) {
            HeapNode top = heap_pop();
            int u = top.node;
            int d = top.dist;

            if (d > dist[u]) continue;

            for (int e = head[u]; e != -1; e = edges[e].next) {
                int v = edges[e].v;
                int w = edges[e].w;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    heap_push(v, dist[v]);
                }
            }
        }

        int ans = dist[(C-1)*2 + 0];

        if (ans >= INF) printf("-1\n");
        else printf("%d\n", ans);
    }

    return 0;
}

