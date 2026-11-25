// NOTA: si raccomanda di usare questo template anche se non lo si capisce completamente.

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <math.h>

using namespace std;

unsigned long long powll(unsigned long long X,unsigned long long E) {
    unsigned long long ans = 1;
    for(size_t i = 0;i<E;i++) {
        ans*=X;
    }
    return ans;
}

bool prime(int n) {
    if(n == 1) return false;
    if(n == 2 || n == 3) return true;
    for(int i=2;i<n;i++) {
        if(n%i == 0) return false;
    }
    return true;
}

struct v_exp {
    unsigned long long v=6,po=6; // value^po
};

vector<unsigned long long> prime_table;

inline bool static_prime(unsigned long long v) {
    return binary_search(prime_table.begin(),prime_table.end(),v);
}

v_exp max_prime_div(unsigned long long a) {
    if(static_prime(a)) return {a,1};
    v_exp div = {0,0};
    for(int i=a-1;i>1;i--) {
        if(a%i == 0 && static_prime(i)) {
            div.v = i;
            break;
        }
    }

    do {
        a/=div.v;
        div.po++;
    } while(a%div.v == 0);
    return div;
}

void compute_prime_table(const size_t new_count) {
    if(prime_table.empty()) prime_table.push_back(2); // first prime number
    prime_table.reserve(prime_table.size()+new_count);
    for(size_t i=0;i<new_count;i++) {
        unsigned long long start = prime_table.back();
        bool found = false;
        while(!found) {
            start++;
            if(prime(start)) found = true;    
        }
        prime_table.push_back(start);
    }
}

void compute_prime_table_until(unsigned long long stop_value) {
    
    if(prime_table.empty()) prime_table.push_back(2); // first prime number
    while(true) {
        unsigned long long start = prime_table.back();
        bool found = false;
        while(!found) {
            start++;
            if(prime(start)) found = true;    
        }
        if(start >= stop_value) break;
        prime_table.push_back(start);
    }
}

inline long long LCM(vector<unsigned long long>& values) {
    unordered_map<unsigned long long,unsigned long long> map;
    
    for(auto& i : values) {
        if(i==1) continue;
        auto div = max_prime_div(i);
        if(!map.count(div.v)) map[div.v] = div.po;
        else map[div.v] = max(map[div.v],div.po);
    }
    vector<pair<unsigned long long,unsigned long long>> vec(map.begin(),map.end());
    long long ans = 1;
    for(auto& v : vec) {
        //cout << v.first << "^" << v.second << " * ";
        ans*=powll(v.first,v.second);
    }
    return ans;
}

int main(int argc,char* argv[]) {

    // decommenta le due righe seguenti se vuoi leggere/scrivere da file
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    int T;
    cin >> T;
    for (int test = 1; test <= T; ++test) {
        int N;
        cin >> N;

        vector<unsigned long long> V(N);
        for (int i = 0; i < N; ++i)
            cin >> V[i];

        compute_prime_table_until(2*(*max_element(V.begin(),V.end()))); 

        

        


        cout << "Case #" << test << ": ";
        cout << LCM(V) << endl;
        
    }



    return 0;
}

