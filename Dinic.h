//
// Created by Administrator on 2019/7/2.
//

class Dinic {
private:/*basic Graph information*/
    int n, m;
    int st, ed;

    struct Edge {
        int from;
        int to;
        long long w;
        int next;

        Edge() { from = to = w = next = 0; }

        Edge(int from, int to, long long w, int next) : from(from), to(to), w(w), next(next) {}
    };

    vector <Edge> e;
    vector<int> head;
private: /*level split*/
    vector<int> level;
    vector<bool> vis;

    bool level_split() {
        level = vector<int>(n + 1, 0);
        vis = vector<bool>(n + 1, false);
        queue<int> q;
        q.push(st);
        level[st] = 1;
        vis[st] = true;
        while (!q.empty()) {
            int fr = q.front();
            q.pop();
            for (int i = head[fr]; ~i; i = e[i].next) {
                int nx = e[i].to;
                if (e[i].w == 0)continue;
                if (!vis[nx]) {
                    vis[nx] = true;
                    q.push(nx);
                    level[nx] = level[fr] + 1;
                }
            }
        }
        return vis[ed] != 0;
    }

    long long augment(int u, long long flow) {
        if (u == ed) return flow;
        long long tmp = flow;
        for (int i = head[u]; ~i; i = e[i].next) {
            int v = e[i].to;
            if (level[v] == level[u] + 1 && e[i].w > 0) {
                long long f = augment(v, min(e[i].w, tmp));
                e[i].w -= f;
                e[i ^ 1].w += f;
                tmp -= f;
            }
        }
        return flow - tmp;
    }

public:
    Dinic(int n, int m, int st, int ed) : n(n), m(m), st(st), ed(ed) {
        head = vector<int>(n + 1, -1);
    }

    void addEdge(int u, int v, long long w);

    void addEdge_bi(int u, int v, long long w);

    long long max_flow();
};

void Dinic::addEdge(int u, int v, long long w) {
    e.emplace_back(u, v, w, head[u]);
    head[u] = (int) e.size() - 1;
}

void Dinic::addEdge_bi(int u, int v, long long w) {
    addEdge(u, v, w);
    addEdge(v, u, 0);
}

long long Dinic::max_flow() {
    long long flow = 0;
    while (level_split()) {
        flow += augment(st, INF);
    }
    return flow;
}
