// NOTA: si raccomanda di usare questo template anche se non lo si capisce completamente.

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <string.h>
#include <vector>

using namespace std;


int main() {
    // decommenta le due righe seguenti se vuoi leggere/scrivere da file
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    int T;
    cin >> T;
    for (int test = 1; test <= T; ++test) {
        int N1, N2, N3, N4; // lunghezza stringhe
        cin >> N1 >> N2 >> N3 >> N4;

        int M; // lunghezza virus
        cin >> M;

        vector<string> strs(4);

        for(int i=0;i<4;i++) {
            cin >> strs[i];
        }

        int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
        
        // std::sort(strs.begin(), strs.end(),
        // [](const std::string& a, const std::string& b) {
        //     return a.size() < b.size();
        // });
        
        vector<int> pos1; // eligible according to first two shortest strings (indecies relative to strs[1])
        for(int i=0;i<strs[0].size()-M+1;i++) {
            for(int j=0;j<strs[1].size()-M+1;j++) {
                if(!memcmp(strs[0].data()+i,strs[1].data()+j,M)) {
                    pos1.push_back(j);
                }
            }
        }

        vector<int> pos2;
        for(int i : pos1) {
            for(int j=0;j<strs[2].size()-M+1;j++) {
                if(!memcmp(strs[1].data()+i,strs[2].data()+j,M)) {
                    pos2.push_back(j);
                }
            }
        }

        int pos3;
        for(int i : pos2) {
            for(int j=0;j<strs[3].size()-M+1;j++) {
                if(!memcmp(strs[2].data()+i,strs[3].data()+j,M)) {
                    pos3 = j;
                    goto found;
                }
            }
        }

        found:


        vector<int> p(4);
        p[3] = pos3;
        for(int i=0;i<3;i++) {
            for(int j=0;j<strs[i].size()-M+1;j++) {
                if(!memcmp(strs[i].data()+j,strs[3].data()+pos3,sizeof(char)*M)) {
                    p[i] = j;
                }
            }            
        }
        

        cout << "Case #" << test << ": ";
        cout << p[0] << " " << p[1] << " " << p[2] << " " << p[3] << endl;
    }

    return 0;
}
