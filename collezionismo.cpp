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
    
    vector<i32> K_l(K,N/K),K_i(K,0);

    K_l.back()+=N%K;
    {
        i32 l_idx = 0;
        for(i32 i=0;i<K;i++) {
            K_i[i] = l_idx;
            l_idx+=K_l[i];
        }
    } // compute K_i


    bool move = true;
    while(move) {
        move = false;
        for(i32 i=0;i<K-1;i++) {
            i32 leftCost  = 0, maxLeftCost = -1; i32 leftCount = 0;

            for(i32 j=0;j<K_l[i+1]-1;j++) {
                i32 center = K_i[i+1]+j;
                leftCost += (C[center+1]-C[center])-(C[center]-C[center-1]);
                if(leftCost > maxLeftCost) {
                    maxLeftCost=leftCost;
                    leftCount = j+1;
                }
            }

            i32 rightCost = 0, maxRightCost = -1; i32 rightCount = 0;

            for(i32 j=0;j<K_l[i]-1;j++) {
                i32 center = K_i[i+1]-j-1;
                rightCost += (C[center]-C[center-1])-(C[center+1]-C[center]);
                if(rightCost > maxRightCost) {
                    maxRightCost=rightCost;
                    rightCount = j+1;
                }
            }
            
            if(maxLeftCost > 0 || maxRightCost > 0) {
                move = true;
                if(maxLeftCost < maxRightCost) { // move to right (cursor goes left)
                    K_l[i+1] += rightCount; K_i[i+1]-=rightCount;  // push to right
                    K_l[i]   -= rightCount;                       // pop from left
                } 
                else {                     // move to left (cursor goes right)
                    K_l[i+1] -= leftCount; K_i[i+1]+=leftCount;   // pop from right
                    K_l[i]   += leftCount;                        // push to left
                }
            }

        }
    }
    
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
    freopen("output.txt", "w", stdout);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        solve(t);
    }

    return 0;
}
