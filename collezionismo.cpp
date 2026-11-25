#include <cstdio>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <math.h>
#include <utility>
#include <vector>
#include "defs.h"

using namespace std;

void solve(i32 t) {
    i32 N, K;
    cin >> N >> K;

    vector<i32> C(N);
    for (i32 i = 0; i < N; i++) {
        cin >> C[i];
    }

    sort(C.begin(),C.end());
    
    vector<i32> K_l(K,N/K),K_i(K,0);

    K_l.back()+=N%K;
    {
        int l_idx = 0;
        for(int i=0;i<K;i++) {
            K_i[i] = l_idx;
            l_idx+=K_l[i];
        }
    } // compute K_i

    for(i32 i=0;i<K-1;i++) {
        i32 leftCost = 0,rightCost = 0;
        i32 leftCount = 0,rightCount = 0;

        for(i32 j=0;j<K_l[i+1]-1;j++) {
            i32 center = leftCount+K_i[i+1]-1+j;
            i32 iterLeftCost = (C[center]-C[center-1])-(C[center+1]-C[center]);
            cout << "iterLeftCost=" << iterLeftCost << endl;
            if(iterLeftCost < 0) {
                break;
            }
            leftCost+=iterLeftCost;
            leftCount++;
        }

        // for(i32 j=K_i[i+1]-1;j>K_i[i];j++) {
        //     i32 center = 
        // }
        
        
        if(leftCost > 0 || rightCost > 0) {
            if(leftCost < rightCost) { // move to right (cursor goes left)
                cout << "move to right" << endl;
                K_l[i+1]+= rightCount;K_i[i+1]-=rightCount;  // push to right
                K_l[i]  -= rightCount;                       // pop from left
            } 
            else {                     // move to left (cursor goes right)
                cout << "move to left" << endl;
                K_l[i+1]-= leftCount; K_i[i+1]+=leftCount;   // pop from right
                K_l[i]  += leftCount;                        // push to left
            }
        }

    }

        

    // for(int i=0;i<K;i++) {
    //     cout << endl << "i=" << i << " K_i[i]=" << K_i[i] << " K_l[i]=" << K_l[i] << endl;
    //     for(int j=0;j<K_l[i];j++) {
    //         // compute partitions sums
    //         cout << "\tC[" << K_i[i]+j << "]=" << C[K_i[i]+j] << endl;
    //     }
    // }

    
    int risposta = 0;

    for(int i=0;i<K;i++) {
        risposta+=C[K_i[i]+K_l[i]-1]-C[K_i[i]];
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
