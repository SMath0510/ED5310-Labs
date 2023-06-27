/* Shaun */

#include<bits/stdc++.h>
#include<fstream>
using namespace std;
using namespace std::chrono;

// error for decimal point precision 
const long double err = 0.005;

/* Classes required for the algorithm */
class Vertex{
    public : 
        /* Coordinates of the Vertex / Vector */
        long double x, y, z;

        /* Constructor to set the value of the Vertex */
        Vertex(){
            x = 0;
            y = 0;
            z = 0;
        }
        Vertex(long double a, long double b, long double c) {
            x = a;
            y = b;
            z = c;
        } 
        
        /* Subtraction operator overloading */
        Vertex operator-(const Vertex &other) const{
            Vertex retVertex = Vertex(x - other.x, y - other.y, z - other.z);
            return retVertex;
        }

        void print(){
            cout << x << ", " << y << ", " << z << "\n";
        }

};

/* 
Class Face which stores : 
1. The indices of the three pointList that it contains 
2. The outward pointing normal
*/

class Face {
    public: 
        int point1, point2, point3; // pointList on the face
        Vertex normal; // normal vector

        Face(int p1, int p2, int p3, Vertex n){
            point1 = p1;
            point2 = p2;
            point3 = p3;
            normal = n;
        }
};

/* Parameters to be used througout the algorithm */
vector<Vertex> pointList;
vector<vector<bool>> insideHull;
vector<Face> convexHull;

/* Classical Vector functions that we need in the later part of algorithm */

long double dotProduct(Vertex v1, Vertex v2) {
    long double retValue = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return retValue;
}

Vertex crossProduct (Vertex v1, Vertex v2) {
    Vertex retVertex(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
    return retVertex;
}

Vertex subtract (Vertex v1, Vertex v2) {
    long double X = v1.x - v2.x, Y = v1.y - v2.y, Z = v1.z - v2.z;
    Vertex retVertex(X, Y, Z);
    return retVertex;
}

/* Function to add and remove a Face to the face List of the Hull */
void addFace (int a, int b, int c) {
    Vertex v1 = subtract(pointList[c], pointList[a]);
    Vertex v2 = subtract(pointList[b], pointList[a]);
    Vertex faceNormal = crossProduct(v1, v2);
    Face face(a, b, c, faceNormal);
    convexHull.push_back(face);
    insideHull[a][b] = insideHull[b][c] = insideHull[c][a] = true;
}

void removeFace (Face &f) {
    int a = f.point1, b = f.point2, c = f.point3;
    insideHull[a][b] = insideHull[b][c] = insideHull[c][a] = false;
}

/* Checking if or not the vertex is visible from the face */
bool isVisible(Vertex v, Face f){
    if(dotProduct(subtract(v, pointList[f.point1]), f.normal) > err){
        return true;
    }
    return false;
}

/* Function to create the Hull */

void beginHull(){
    addFace(0, 1, 2);
    addFace(0, 2, 1);
}

void createHull() {
    int n = pointList.size();
    // assuming that n >= 3 for the rest of the code
    /* Initializing the Hull */
    beginHull();

    /* Looping over the remaining points */
    
    for(int i = 3; i < n; i++) {
        vector<Face> tempHull; // Temp Hull to add and remove the relevant faces
        int hullSize = convexHull.size();

        /* If point is outside some face remove it, else add it to the temp list */
        for(int j = 0; j < hullSize; j++) {
            if(isVisible(pointList[i], convexHull[j])) {
                removeFace(convexHull[j]);
            }
            else {
                tempHull.push_back(convexHull[j]);
            }
        }

        convexHull = tempHull;
        hullSize = convexHull.size();

        /* Add the ith point and the edges of the face to the Hull,
        if that edge isn't inside the Hull */
        for(int j = 0; j < hullSize; j++) {
            int p1 = convexHull[j].point1;
            int p2 = convexHull[j].point2;
            int p3 = convexHull[j].point3;
            if(!insideHull[p2][p1]) {
                addFace(p2, p1, i);
            }
            if(!insideHull[p3][p2]) {
                addFace(p3, p2, i);
            }
            if(!insideHull[p1][p3]) {
                addFace(p1, p3, i);
            }
        }
    }
    
}

/* Function for generating the stl File for visualization */
void createSTL(){
    int hullSize = convexHull.size();
    ofstream fout;
    fout.open("showHull.stl");
    fout  <<  "solid ConvexHull"  <<  "\n";

    /* Printing the faces as per the stl Syntax */
    for(int i = 0 ; i < hullSize ; i++){

        fout << "facet normal " << convexHull[i].normal.x << " " << convexHull[i].normal.y << " " << convexHull[i].normal.z << "\n";
        fout << "\touter loop" << "\n";
        fout << "\t\tvertex " << pointList[convexHull[i].point1].x << " " << pointList[convexHull[i].point1].y << " " << pointList[convexHull[i].point1].z << "\n";
        fout << "\t\tvertex " << pointList[convexHull[i].point2].x << " " << pointList[convexHull[i].point2].y << " " << pointList[convexHull[i].point2].z << "\n";
        fout << "\t\tvertex " << pointList[convexHull[i].point3].x << " " << pointList[convexHull[i].point3].y << " " << pointList[convexHull[i].point3].z << "\n";
        fout << "\tendloop" << "\n";
        fout << "endfacet" << "\n";
    }

    fout << "endsolid ConvexHull" << "\n";
    fout.close();
}

int main()
{
    /* Number of pointList in the input */
    int n;
    cin >> n;
    pointList.resize(n);
    /* Taking in the pointList */
    for(int i = 0; i < n; i++){
        cin >> pointList[i].x >> pointList[i].y >> pointList[i].z;
    }

    insideHull.resize(n, vector<bool> (n, false)); //If or not the edge is inside the Hull

    auto startTime = high_resolution_clock::now(); 

    /* Function to create Hull*/
    createHull();
    int hullSize = convexHull.size();

    /* The indices of pointList that form the face */
    for(int i = 0; i < hullSize; i++){
        cout  <<  convexHull[i].point1  <<  " "  <<  convexHull[i].point2  <<  " "  <<  convexHull[i].point3  <<  "\n";
    }

    auto stopTime1 = high_resolution_clock::now(); 
    // Program executed 
    createSTL();
    // stl file created 

    /* Recording the time */
    auto stopTime2 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stopTime1 - startTime);
    auto duration2 = duration_cast<microseconds>(stopTime2 - startTime);
    cout << "Time [Program] " << duration1.count() << "ms" << "\n";
    cout << "Time [STL File] " << duration2.count() << "ms" << "\n";
}