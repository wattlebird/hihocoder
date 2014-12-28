//Author: Testla
/*added SLF and LLL*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100000
#define MAXM 1000000

struct edge {
    int to;
    int weight;
} edges[MAXM * 2];

int q[MAXN], in[MAXN + 1], head[MAXN + 1], next[MAXM + 1], d[MAXN + 1];

int main(void) {
    int n, m, s, t, from, to, weight, i, start, end, e, current_vertex, current_d, current_to, queue_size, sum;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    memset(head + 1, 0, n * sizeof(int));
    i = 1;
    while (i <= (m << 1)) {
        scanf("%d%d%d", &from, &to, &weight);
        edges[i].to = to;
        edges[i].weight = weight;
        next[i] = head[from];
        head[from] = i;
        ++i;
        edges[i].to = from;
        edges[i].weight = weight;
        next[i] = head[to];
        head[to] = i;
        ++i;
    }
    memset(in + 1, 0, n * sizeof(int));
    memset(d + 1, 0x7f, n * sizeof(int));
    d[s] = 0;
    start = 0;
    end = 1;
    q[0] = s;
    in[s] = 1;
    sum = 0;
    while (start != end) {
        queue_size = (end - start + MAXN) % MAXN;
        while (d[q[start]] * queue_size > sum) {
            q[end] = q[start];
            start = (start + 1) % (MAXN + 1);
            end = (end + 1) % (MAXN + 1);
        }
        current_vertex = q[start];
        sum -= d[q[start]];
        start = (start + 1) % MAXN;
        current_d = d[current_vertex];
        e = head[current_vertex];
        while (e) {
            current_to = edges[e].to;
            if (current_d + edges[e].weight < d[current_to]) {
                d[current_to] = current_d + edges[e].weight;
                if (!in[current_to]) {
                    if (d[current_to] < d[q[start]]) {
                        start = (start - 1 + MAXN) % MAXN;
                        q[start] = current_to;
                    } else {
                        q[end] = current_to;
                        end = (end + 1) % MAXN;
                    }
                    sum += d[current_to];
                    in[current_to] = 1;
                }
            }
            e = next[e];
        }
        in[current_vertex] = 0;
    }
    printf("%d\n", d[t]);
    return 0;
}
