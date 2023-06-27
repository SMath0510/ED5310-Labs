#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define int long long
#define pi 3.142857

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


int gr(int r)
{
   uniform_int_distribution<int> uid(0,r-1);
   int val = uid(rng);
   return val+1;
}

int glr(int l, int r)
{
    int dif = r-l+1;
    int x = gr(dif) + l-1;
    return x;
}

string rndstr(int len){
    string s;
    for(int i = 0; i < len; i++){
        s += (char)(gr(26) + 'a' - 1);
    }
    return s;
}

#define cout outputFile

int32_t main()
{
    string file="input/tc10.txt";
    
    ofstream outputFile;
	outputFile.open(file);
    
    int n = 75000;
    cout << n << "\n";
    for (int i = 0; i < n; i++){
        int dist = glr (100, 10000);
        double x = dist * cos((double)i * 2 * pi / (double)n);
        double y = dist * sin((double)i * 2 * pi / (double)n);
        cout << x << " " << y << "\n";
    }
    
}