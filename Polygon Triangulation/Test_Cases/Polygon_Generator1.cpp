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
    for(int ii = 0; ii<1; ii++){
        char name[10] = "TC00.txt";
        name[3] = '0' + ii;
        name[2] = '0' + 1;
        freopen (name, "w", stdout);
        int U = 20, L = 10, ub = 400, lb = 350;
        int n = (rand() % (U - L + 1)) + L;
        
        // printf("%d \n", n);
        float x,y;
        cout<<n<<endl;
        // n = 10;
        for (int i = 0; i < n; i++)
        { 
            float d = (rand() % (ub - lb + 1)) + lb;
            // cout<<d<<endl;
            x=cos((2*pi*i)/((float)n))*d;
            y=sin((2*pi*i)/((float)n))*d;
            cout<<x<<" "<<y<<endl;
            // printf("%d %d \n", x, y);
        }

        fclose(stdout);
    }
	return(0);
}
