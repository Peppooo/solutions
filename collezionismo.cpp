#include <cstdio>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>
#include <limits>
#include "defs.hpp"

using namespace std;

void solve(i32 t) {
    i32 N, K;
    cin >> N >> K;

    vector<i32> C(N);
    for (i32 i = 0; i < N; i++) {
        cin >> C[i];
    }

    sort(C.begin(),C.end());
    
    vector<pair<i32,i32>> diff(N-1);

    for(i32 i=0;i<N-1;i++) {
        diff[i].first = C[i+1]-C[i];
        diff[i].second = i;
    }


    sort(diff.rbegin(),diff.rend());

    // vector<i32> split(K);

    // split.front() = 0;
    
    // for(i32 i=1;i<K;i++) {
    //     split[i] = diff[i].second;
    //     cout << diff[i].first << ": " << diff[i].second << endl;
    // }

    // sort(split.begin(),split.end());

    i32 risposta = C[N-1]-C[0];

    for(i32 i=0;i<K-1;i++) {
        // i32 first = split[i],last = split[i+1];
        // cout << split[i] << endl;
        // risposta+=C[last]-C[first];
        risposta-=diff[i].first;
    }

    cout << "Case #" << t << ": " << risposta << "\n";
}



int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        solve(t);
    }

    return 0;
}
