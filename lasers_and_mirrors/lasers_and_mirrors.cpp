//http://www.usaco.org/index.php?page=viewproblem2&cpid=671i

#include<bits/stdc++.h>
#define X first
#define Y second

using namespace std;
const int MAXN = 100009;
typedef pair<int,int> pii;
int n, src_i, dest_i;
pii src, dest, p[MAXN];
vector<pii> graph[2*MAXN];

inline int vv(int x) {
    return n+x;
}

inline int hh(int x) {
    return x;
}

void add_edge(int u, int v, int w) {
//    cout << "Edge added -> " << u << " " << v << " " << w << "\n";
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
}

int bfs_01(int s, int e) {
    vector<int> dist(2*MAXN, (1<<30));
    dist[hh(s)] = dist[vv(s)] = 0;
    deque<int> q;
    q.push_back(hh(s));
    q.push_back(vv(s));
    while(!q.empty()) {
        int v = q.front();
        q.pop_front();
        for(pii child: graph[v]) {
            if(dist[child.first] <= dist[v] + child.second) continue;
            dist[child.first] = dist[v] + child.second;
            if(child.second == 0)
                q.push_front(child.first);
            else
                q.push_back(child.first);
        }
    }
    int ans = min(dist[hh(e)], dist[vv(e)]);
    if(ans == (1<<30))
        return -1;
    return ans;
}

int main() {

    freopen("lasers.in","r",stdin);
    freopen("lasers.out","w",stdout);

    cin >> n;
    n += 2;
    cin >> p[0].X >> p[0].Y >> p[1].X >> p[1].Y;
    src = p[0], dest = p[1];
    for(int i=2; i<n; i++)
        cin >> p[i].X >> p[i].Y;
    sort(p, p+n);
   
    map<int,int> last_found;
    last_found[p[0].Y] = 1;
    add_edge(hh(0), vv(0), 1); 
    for(int i=1; i<n; i++) {
        if(p[i] == src) src_i = i;
        if(p[i] == dest) dest_i = i;
        if(p[i].X == p[i-1].X)
            add_edge(vv(i), vv(i-1), 0);
        if(last_found[p[i].Y] != 0)
            add_edge(hh(i), hh(last_found[p[i].Y]-1), 0);
        add_edge(hh(i), vv(i), 1);
        last_found[p[i].Y] = i+1;
    }
  //  for(int i=0; i<n; i++)
  //      cout << p[i].X << " " << p[i].Y << "\n";
  //  cout << src_i << " " << dest_i << "\n";
    cout << bfs_01(src_i, dest_i) << "\n";
    return 0;
}
