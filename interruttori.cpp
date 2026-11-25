#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

#define ui64 uint64_t

struct node {
    vector<int> edges;
    node(): edges(vector<int>(0)) {};
};

void solve(int t) {
    int N, A, B;
    cin >> N >> A >> B;

    vector<int> Z(A);
    
    vector<node> graph(N); // grafo che rappresenta le lampadine

    for (int i = 0; i < A; i++) {
        cin >> Z[i];
    }

    for (int i = 0; i < B; i++) {
        int x,y;
        cin >> x >> y;

        graph[x].edges.push_back(y);
        graph[y].edges.push_back(x);
    }

    vector<ui64> min_steps(N,UINT64_MAX); // numero minimo di step per arrivare ad un interruttore singolo
    
    for(int i=0;i<A;i++) { 
        vector<bool> visited(N,false);
        vector<ui64> depth(N,1);

        queue<int> q;

        int start = Z[i];
        q.push(start);
        visited[start] = true;

        while(!q.empty()) {
            int next = q.front();q.pop();
            for(auto nb : graph[next].edges) {
                if(!visited[nb]) {
                    visited[nb] = true;
                    depth[nb] = depth[next]+1;
                    q.push(nb);
                }
            }
        }
 
        for(int j=0;j<N;j++) {
            min_steps[j] = min(min_steps[j],depth[j]);
        }
    }


    auto max_it = max_element(min_steps.begin(),min_steps.end());

    ui64 idx = max_it-min_steps.begin();
    ui64 num = *max_it;

    cout << "Case #" << t << ": " << idx << " " << num << "\n";
}

int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        solve(t);
    }

    return 0;
}