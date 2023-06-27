// A C++ Program to generate test cases for
// array filled with random numbers
#include<bits/stdc++.h>
using namespace std;

const int MAX = 1e9;
#define pi 3.142857
int main()
{
    // Number of files in one go
    // int N = 10;
    for(int ii = 0; ii<10; ii++){
        char name[10] = "TC00.txt";
        name[3] = '0' + ii;
        name[2] = '0' + 0;
        // freopen (name, "w", stdout);
        int U = 25, L = 10, ub = 50, lb = 10;
        int n = (rand() % (U - L + 1)) + L;
        
        // printf("%d \n", n);
        float x, y, z;
        cout << n << endl;
        // n = 10;
        for (int i = 0; i < n; i++)
        { 
            long double d = (rand() % (ub - lb + 1)) + lb;
            long phi = (rand() % (7));
            x = cos(2*pi / n) * sin(phi) * d;
            y = cos(2*pi / n) * cos(phi) * d;
            z = sin(2*pi / n) * d;
            cout << x << " " << y << " " << z << " \n";
        }

        // fclose(stdout);
    }
	return(0);
}