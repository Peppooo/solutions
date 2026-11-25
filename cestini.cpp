#include <iostream>
#include <string>
#include <vector>

using namespace std;

void solve(int t) {
    int N, M, Q;
    cin >> N >> M >> Q;

    string S;
    cin >> S;

    vector<vector<char>> cestini(M,vector<char>(0,0));

    cestini[0].resize(S.size());
    copy(S.begin(),S.end(),cestini[0].begin());

    string risposta;

    for (int i = 0; i < Q; i++) {
        char type;
        int a, b;
        cin >> type >> a >> b;

        if (type == 's') { // sposta
            cestini[b].push_back(cestini[a].back());
            cestini[a].pop_back();            
        } else { // domanda
            risposta.push_back(cestini[a][b]);
        }  
    }


    cout << "Case #" << t << ": " << risposta << endl;
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
