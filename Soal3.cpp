#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

const int N = 6;                 // A..F
const char NAMA[N] = {'A','B','C','D','E','F'};
int adj[N][N];                   // adjacency matrix berbobot (0 = tidak ada sisi)

void tambahSisi(int u, int v, int w) { adj[u][v] = adj[v][u] = w; }

void bfs(int start) {
    bool vis[N] = {false};
    queue<int> q;
    q.push(start); vis[start] = true;
    cout << "BFS : ";
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << NAMA[u] << " ";
        for (int v = 0; v < N; v++)
            if (adj[u][v] && !vis[v]) { vis[v] = true; q.push(v); }
    }
    cout << "\n";
}

void dfsRek(int u, bool vis[]) {
    vis[u] = true;
    cout << NAMA[u] << " ";
    for (int v = 0; v < N; v++)
        if (adj[u][v] && !vis[v]) dfsRek(v, vis);
}
void dfs(int start) {
    bool vis[N] = {false};
    cout << "DFS : ";
    dfsRek(start, vis);
    cout << "\n";
}

void dijkstra(int src, int dst) {
    int dist[N], prev[N];
    bool done[N] = {false};
    for (int i = 0; i < N; i++) { dist[i] = INT_MAX; prev[i] = -1; }
    dist[src] = 0;
    for (int c = 0; c < N; c++) {
        int u = -1;
        for (int i = 0; i < N; i++)
            if (!done[i] && (u == -1 || dist[i] < dist[u])) u = i;
        if (u == -1 || dist[u] == INT_MAX) break;
        done[u] = true;
        for (int v = 0; v < N; v++)
            if (adj[u][v] && dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
                prev[v] = u;
            }
    }
    if (dist[dst] == INT_MAX) { cout << "Tidak ada rute dari " << NAMA[src] << " ke " << NAMA[dst] << "\n"; return; }
    vector<int> rute;
    for (int v = dst; v != -1; v = prev[v]) rute.push_back(v);
    reverse(rute.begin(), rute.end());
    cout << "Rute terpendek : ";
    for (size_t i = 0; i < rute.size(); i++) {
        cout << NAMA[rute[i]];
        if (i + 1 < rute.size()) cout << " -> ";
    }
    cout << "\nTotal jarak    : " << dist[dst] << "\n";
}

void tampilMatriks() {
    cout << "   ";
    for (int i = 0; i < N; i++) cout << NAMA[i] << "  ";
    cout << "\n";
    for (int i = 0; i < N; i++) {
        cout << NAMA[i] << "  ";
        for (int j = 0; j < N; j++) cout << adj[i][j] << "  ";
        cout << "\n";
    }
}

int bacaVertex(const char *pesan) {
    char c;
    while (true) {
        cout << pesan; cin >> c;
        c = toupper(c);
        if (c >= 'A' && c <= 'F') return c - 'A';
        cout << "Vertex tidak valid (A-F).\n";
    }
}

int main() {
    // A=0 B=1 C=2 D=3 E=4 F=5
    tambahSisi(0,1,4); tambahSisi(0,2,2); tambahSisi(1,2,1);
    tambahSisi(1,3,5); tambahSisi(1,4,3); tambahSisi(2,3,8);
    tambahSisi(2,4,6); tambahSisi(3,4,2); tambahSisi(3,5,4);
    tambahSisi(4,5,3);

    cout << "=== SISTEM PENCARIAN RUTE LINGKUNGAN KAMPUS ===\n";
    cout << "Adjacency Matrix:\n"; tampilMatriks();

    int awal = bacaVertex("\nVertex awal   (A-F): ");
    int tujuan = bacaVertex("Vertex tujuan (A-F): ");

    cout << "\n-- Penelusuran graf dari " << NAMA[awal] << " --\n";
    bfs(awal);
    dfs(awal);
    cout << "\n-- Dijkstra " << NAMA[awal] << " ke " << NAMA[tujuan] << " --\n";
    dijkstra(awal, tujuan);
    return 0;
}
