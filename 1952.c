#include <stdio.h>
#include <string.h>

#define MAXN 101
#define INF 1000000000

typedef struct {
    int x, y, z;
} Node;

int dist[MAXN][MAXN][MAXN];

int main() {
    int N, M, L;
    scanf("%d %d %d", &N, &M, &L);

    int sx, sy, sz;
    int tx, ty, tz;

    scanf("%d %d %d", &sx, &sy, &sz);
    scanf("%d %d %d", &tx, &ty, &tz);

    sx--, sy--, sz--;
    tx--, ty--, tz--;

    int moves[24][3];
    int idx = 0;
    int base[3] = {0, 1, 2};

    int perm[6][3] = {
        {0,1,2},{0,2,1},{1,0,2},
        {1,2,0},{2,0,1},{2,1,0}
    };

    for (int p = 0; p < 6; p++) {
        for (int sxn = -1; sxn <= 1; sxn += 2) {
            for (int syn = -1; syn <= 1; syn += 2) {
                int dx = perm[p][0] == 0 ? 0 : perm[p][0] == 1 ? sxn : syn;
                int dy = perm[p][1] == 0 ? 0 : perm[p][1] == 1 ? sxn : syn;
                int dz = perm[p][2] == 0 ? 0 : perm[p][2] == 1 ? sxn : syn;

                dx = (perm[p][0] == 0 ? 0 : perm[p][0] * (perm[p][0] == 1 ? sxn : syn));
                dy = (perm[p][1] == 0 ? 0 : perm[p][1] * (perm[p][1] == 1 ? sxn : syn));
                dz = (perm[p][2] == 0 ? 0 : perm[p][2] * (perm[p][2] == 1 ? sxn : syn));

                moves[idx][0] = dx;
                moves[idx][1] = dy;
                moves[idx][2] = dz;
                idx++;
            }
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            for (int k = 0; k < L; k++)
                dist[i][j][k] = INF;

    static Node queue[101*101*101];
    int front = 0, back = 0;

    dist[sx][sy][sz] = 0;
    queue[back++] = (Node){sx, sy, sz};

    while (front < back) {
        Node u = queue[front++];
        int d = dist[u.x][u.y][u.z];

        if (u.x == tx && u.y == ty && u.z == tz) {
            printf("%d\n", d);
            return 0;
        }

        for (int i = 0; i < 24; i++) {
            int nx = u.x + moves[i][0];
            int ny = u.y + moves[i][1];
            int nz = u.z + moves[i][2];

            if (nx >= 0 && nx < N &&
                ny >= 0 && ny < M &&
                nz >= 0 && nz < L &&
                dist[nx][ny][nz] == INF) {

                dist[nx][ny][nz] = d + 1;
                queue[back++] = (Node){nx, ny, nz};
            }
        }
    }

    return 0;
}

