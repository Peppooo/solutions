#include <iostream>
#include <vector>
#include <cassert>
#include "defs.h"

using namespace std;

int count_sq(const vector<u8>& m,int w,int sq_h,int sq_w,int y,int x,int min) {
    int s = 0;
    for(int j=0;j<sq_h;j++) {
        for(int i=0;i<sq_w;i++) {
            s += m[ (i+x)+(j+y)*w ]; 
        }
        if(s >= min) {
            return s;
        }
    }
    return s;
} // naive approach

struct SAT {
    vector<i64> sum;
    i32 w,h;
    SAT(i32 _w,i32 _h):w(_w),h(_h) {
        sum = vector<i64>(_w*_h,0);
    }
    void preprocess(vector<i32>& mat) {
        assert(w*h==mat.size());
        for(i32 j=0;j<h;j++) {
            i64 row_sum = 0;
            for(i32 i=0;i<w;i++) {
                i32 f = i+j*w;
                row_sum+=mat[f];
                if(f < w) {
                    sum[f] = row_sum;
                }
                else {
                    sum[f] = row_sum+sum[f-w];
                }
            }
        }
    }
    i64 query(i32 x,i32 y,i32 q_w,i32 q_h) {
        q_w--;
        q_h--;
        i64 out = sum[(x+q_w)+(y+q_h)*w];
        if(x>0 && y>0) {
            out+=sum[(x-1)+(y-1)*w];    
        }
        if(x>0) {
            out-=sum[(x-1)+(y+q_h)*w];
        } 
        if(y>0) {
            out-=sum[(x+q_w)+(y-1)*w];
        }
        return out;
    }    
};

void solve(int t) {
    int h0, w0, K, h1, w1;
    cin >> h0 >> w0 >> K >> h1 >> w1;

    vector<i32> m(w0*h0,0); // i = x+y*w0

    for (int i = 0; i < K; i++) {
        int y,x;
        cin >> y >> x;
        m[x+y*w0]++;
    }

    i64 risposta = 1<<30;

    SAT sat(w0,h0);
    sat.preprocess(m);

    for(i32 j = 0;j<(h0-h1+1);j++) {
        for(i32 i=0;i<(w0-w1+1);i++) {  
            risposta = min(risposta,sat.query(i,j,w1,h1));
        }
    }  
    

    cout << "Case #" << t << ": " << risposta << "\n";
}

int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T = 0;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        solve(t);
    }

    return 0;
}
