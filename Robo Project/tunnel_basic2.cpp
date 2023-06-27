#include<bits/stdc++.h> 
#include<fstream>
using namespace std; 

const double pi = 3.14159265359;

// Class to store the points and related functions
class Point{
    private:

    public:

        double x; // x coordinate of the point
        double y; // y coordinate of the point

    Point(){}

    Point(double a, double b){
        x = a;
        y = b;
    }

    // function to rotate the points about the center by theta radians
    void rotate(double theta, Point center){ // theta in radian
        double c = cos(theta);
        double s = sin(theta);
        double nextX = center.x + (x - center.x)*c - (y - center.y)*s;
        double nextY = center.y + (y - center.y)*c + (x - center.x)*s;
        x = nextX; y = nextY;
    }

    // printing the point
    void print(){
        cout << x << " " << y << endl;
    }
};

// Function to append / write a vector content into a file
void writefile(string fileName, vector<double> &v){
    ofstream myfile;
    myfile.open(fileName + ".txt", ios::app);
    if (myfile.is_open()) {
        for(int i = 0; i < v.size(); i ++){
            myfile << v[i] << " " ;
        }
        myfile << endl;
        myfile.close();
    }
    else cout << "Unable to open file";
}

int main(){ 

    // Taking the input
    int n;
    cin >> n;
    vector<Point> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i].x >> v[i].y;
    }
    
    // Defining the rotation angle and the center
    double theta = pi/180;
    double ans = 1e10;
    Point center(0, 0);
    for(int i = 0; i < n; i++){
        center.x += v[i].x;
        center.y += v[i].y;
    }
    center.x /= n;
    center.y /= n;

    // Defining parameters of the function
    int numReps = (2*pi / theta);
    vector<double> X(n), Y(n);
    double Top = 0, Bottom = 0;

    // Running the function in a loop
    for(int rep = 1; rep <= numReps; rep++){
        double leftMost = 1e9, rightMost = -1e9, topMost = -1e9, bottomMost = 1e9;
        for(int i = 0; i < n; i++){
            leftMost = min(leftMost, v[i].x);
            rightMost = max(rightMost, v[i].x);
            topMost = max(topMost, v[i].y);
            bottomMost = min(bottomMost, v[i].y);
            v[i].rotate(theta, center); // rotating the point
        }
        if(ans > rightMost - leftMost){
            for(int i = 0; i < n; i++) {X[i] = v[i].y; Y[i] = v[i].x;}
            ans = rightMost - leftMost;
            Bottom = leftMost;
            Top = rightMost;
        }
        if(ans > topMost - bottomMost){
            for(int i = 0; i < n; i++) {X[i] = v[i].x; Y[i] = v[i].y;}
            ans = topMost - bottomMost;
            Top = topMost;
            Bottom = bottomMost;
        }
    }

    // Writing the content into the output file
    writefile("out", X);
    writefile("out", Y);
    vector<double> line1 = {0, Top};
    vector<double> line2 = {0, Bottom};
    writefile("out", line1);
    writefile("out", line2);
    
    // The minimum distance
    cout << "The minimum distance required is " << ans << endl;
}