#include <bits/stdc++.h>

using namespace std;

struct pt {
    double x, y;
};

// Check the orientation of three points
int orientation(pt a, pt b, pt c) {
    double v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}

// Check if three points are in clockwise order
bool cw(pt a, pt b, pt c) {
    return orientation(a, b, c) == -1;
}

// Check if three points are collinear
bool collinear(pt a, pt b, pt c) { 
    return orientation(a, b, c) == 0; 
}


pt p0;
// Compare two points based on their polar angle with respect to p0 to sort them
bool compar (pt a, pt b) {
    if (collinear(p0, a, b))
        return (p0.x - a.x) * (p0.x - a.x) + (p0.y - a.y) * (p0.y - a.y) < (p0.x - b.x) * (p0.x - b.x) + (p0.y - b.y) * (p0.y - b.y);
    return cw(p0, a, b);
}

// Get the convex hull of a set of points in O(nlogn) time using Graham's Scan
void convex_hull(vector<pt>& a) {
    p0 = a[0];
    for (int i = 1; i < (int)a.size(); i++)
        if ((a[i].y < p0.y) || ((a[i].y == p0.y) && a[i].x < p0.x)) 
            p0 = a[i];
    sort(a.begin(), a.end(), compar);

    vector<pt> stak;
    for (int i = 0; i < (int)a.size(); i++) {
        while (stak.size() > 1 && !cw(stak[stak.size()-2], stak.back(), a[i]))
            stak.pop_back();

        stak.push_back(a[i]);
    }

    a = stak;
}

// Parse Input and get the points in a vector
vector<pt> parse_input () {
    int n;
    cin >> n;
    if (n < 3) exit(0); // Invalid input
    vector<pt> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i].x >> a[i].y;
    return a;
}

// Get the distance between a point (p2) and a line (p0, p1)
double get_dist (pt p0, pt p1, pt p2) {
    return abs((p1.y - p0.y) * p2.x - (p1.x - p0.x) * p2.y + p1.x * p0.y - p1.y * p0.x) / sqrtl((p1.y - p0.y) * (p1.y - p0.y) + (p1.x - p0.x) * (p1.x - p0.x));
}

// Get the farthest point from a line (a[curr_line], a[(curr_line + 1) % n]) given the farthest point from the previous line (a[curr_max])
int update_farthest_point (vector<pt>& a, int curr_line = 0, int curr_max = 2) {
    int n = a.size();
    pt left = a[curr_line], right = a[(curr_line + 1) % n];
    int next_max = (curr_max + 1) % n;

    while (get_dist(left, right, a[next_max]) > get_dist(left, right, a[curr_max])) {
        curr_max = next_max;
        next_max = (curr_max + 1) % n;
    }
    return curr_max;
}

int min_line = 0, min_max = 2;

// Get the minimum width of the tunnel
double get_min_width (vector<pt>& a) {
    int curr_line = 0, curr_max = 2;
    curr_max = update_farthest_point(a, curr_line, curr_max);
    double min_width = get_dist(a[curr_line], a[(curr_line + 1) % a.size()], a[curr_max]);

    // Iterate through all the lines and get the minimum width among them
    while (curr_line + 1 < (int)a.size()) {
        curr_line++;
        curr_max = update_farthest_point(a, curr_line, curr_max);
        
        if (get_dist(a[curr_line], a[(curr_line + 1) % a.size()], a[curr_max]) < min_width) {
            min_width = get_dist(a[curr_line], a[(curr_line + 1) % a.size()], a[curr_max]);
            min_line = curr_line;
            min_max = curr_max;
        }
    }

    return min_width;
}

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

int main (){
    vector<pt> a = parse_input();
    vector<double> X, Y;
    for (int i = 0; i < (int)a.size(); i++)
        X.push_back(a[i].x);

    for (int i = 0; i < (int)a.size(); i++)
        Y.push_back(a[i].y);

    convex_hull(a);
    get_min_width(a);

    pt left = a[min_line], right = a[(min_line + 1) % a.size()], top = a[min_max];
    double slope = (right.y - left.y) / (right.x - left.x);
    double intercept1 = left.y - slope * left.x;
    double intercept2 = top.y - slope * top.x;

    // Writing the content into the output file
    writefile("out", X);
    writefile("out", Y);
    vector<double> line1 = {slope, intercept1};
    vector<double> line2 = {slope, intercept2};
    writefile("out", line1);
    writefile("out", line2);
    
    //cout << fixed << setprecision(10) << get_min_width(a) << endl;

          
    return 0;
}