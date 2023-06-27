// Importing the Libraries
#include<bits/stdc++.h>
// #include <GL/glut.h>

using namespace std;

// Global vector storing the coordinates of the triangles
vector<vector<pair<float,float>>> vector_triangle;

// void plotTriangulatedPolygon( ){
//     glClear(GL_COLOR_BUFFER_BIT);
//     for (auto vertex: vector_triangle){
//         for (int i=0; i<3; i++){
//             pair<float,float> a = vertex[i], b = vertex[(i+1)%3];
//             glBegin(GL_LINES);
//                 glVertex3f(a.first/800.0, a.second/600.0, 0.0);
//                 glVertex3f(b.first/800.0, b.second/600.0, 0.0);
//             glEnd();
//         }
//     }
//     glFlush();
// }

// void Plot_Function(int argc, char** argv){
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_SINGLE);
//     glutInitWindowSize(1000, 750);
//     glutInitWindowPosition(150, 100);
//     glutCreateWindow("Plot of the Triangulated Polygon");
//     glutDisplayFunc(plotTriangulatedPolygon);
//     glutMainLoop();
// }

void Print_the_Triangles(){
    cout << vector_triangle.size() << endl;

    for (auto vertex: vector_triangle){
        cout<<"(";
        for (int i=0; i<2; i++){
            cout << "(" << vertex[i].first << "," << vertex[i].second << ") ,";
        }
        cout << "(" << vertex[2].first << "," << vertex[2].second << ")"<<endl;
    }

}


int main(int argc, char** argv){
    vector<pair<float,float>> vertices;
    int num_vertices;
    cin >> num_vertices;
    vertices.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++){
        cin >> vertices[i].first >> vertices[i].second;
    }

    list<int> vertex_list, ears, reflex_vertices, convex_vertices;
    for (int i=0; i<num_vertices; i++) vertex_list.push_back(i);

    // Find the Convex and Reflex Vertices
    for (auto iterator=vertex_list.begin(); iterator!=vertex_list.end(); iterator++){
        // current - the vertex we are checking the nature of
        int current = *iterator;
        // previous is the vertex before current in anticlockwise order
        int previous = (current+vertex_list.size()-1)%vertex_list.size();
        // next is the vertex that is after current in anticlockwise order
        int next = (current+1)%vertex_list.size();

        // The coordinates of the vertices
        float a1 = vertices[previous].first;
        float b1 = vertices[previous].second;
        float a2 = vertices[current].first;
        float b2 = vertices[current].second;
        float a3 = vertices[next].first;
        float b3 = vertices[next].second;

        // Calulating the Cross Product
        float crossproduct = (a2-a1)*(b3-b1) - (b2-b1)*(a3-a1);

        // If Cross Product > 0 then its is convex (given the clockwise sense of vertex), else it is reflex vertex
        if (crossproduct > (float)0.00005) convex_vertices.push_back(current);
        else reflex_vertices.push_back(current);
    }

    // Find the Ears
    for (auto iterator=convex_vertices.begin(); iterator!=convex_vertices.end(); iterator++){
        // Lemma : All ears are convex vertices, Hence we just check convex vertices
        int current = *iterator;
        int previous = (current+vertex_list.size()-1)%vertex_list.size();
        int next = (current+1)%vertex_list.size();

        // Calculating the vertices of the triangle for further computation
        float a1 = vertices[previous].first;
        float b1 = vertices[previous].second;
        float a2 = vertices[current].first;
        float b2 = vertices[current].second;
        float a3 = vertices[next].first;
        float b3 = vertices[next].second;

        // Maintaining a boolean value to check for the ear
        bool check_for_ear = true;

        // Lemma : If some vertex lies within the triangle of the ear, then it is a reflex vertex. Hence we check only for the reflex vertices to optimize the code
        if (reflex_vertices.size()!=0) { 
            for (auto iterator2=reflex_vertices.begin(); iterator2!=reflex_vertices.end(); iterator2++){
                // We do not check for the adjacent vertices (as they are the ones forming the triangle)
                if (*iterator2==previous || *iterator2==current || *iterator2==next) {
                    continue;
                }
                else{
                    // Calculating the coordinates of the vertex under test
                    float a4 = vertices[*iterator2].first;
                    float b4 = vertices[*iterator2].second;

                    // Evaluating the Cross Products
                    float crossproduct1 = (a2-a1)*(b4-b1) - (b2-b1)*(a4-a1);
                    float crossproduct2 = (a3-a2)*(b4-b2) - (b3-b2)*(a4-a2);
                    float crossproduct3 = (a1-a3)*(b4-b3) - (b1-b3)*(a4-a3);

                    // If all of these > 0 then this implies that the point lies inside the triangle
                    if (crossproduct1 > 0.00005 && crossproduct2 > 0.00005 && crossproduct3 > 0.00005){
                        // If its inside the triangle then it is not an ear
                        check_for_ear = false;
                        break;
                    }
                }
            }
        }
        if (check_for_ear) ears.push_back(current);
    }

    // Triangulating the Polygon 
    // We need to triangulate the sub-polygons having less than 4 vertices
    while (vertex_list.size() >= 3){
        // Working on an ear and removing it from the polygon
        int ear = ears.front();
        ears.pop_front();
        // Finding the current ear in the list
        auto ear_iterator = find(vertex_list.begin(), vertex_list.end(), ear);
        int previous;
        if (ear_iterator == vertex_list.begin()){
            // Previous of the first element is the last element in the list. Circular Behaviour of the Polygon
            auto temporary_iterator = vertex_list.end();
            temporary_iterator--;
            previous = *temporary_iterator;
        }
        else {
            auto temporary_iterator = ear_iterator;
            temporary_iterator--;
            previous = *temporary_iterator;
        }
        int next;
        auto temporary_iterator = ear_iterator;
        temporary_iterator++;
        if (temporary_iterator == vertex_list.end()) {
            // Next of the last vertex is the first vertex by the circular nature of the polygon
            next = *vertex_list.begin();
        }
        else {
            next = *temporary_iterator;
        }
        vector<pair<float,float>> triangle = {vertices[previous], vertices[ear], vertices[next]};
        vector_triangle.push_back(triangle);
        // Removing the ear from all the lists as it has been triangulated
        vertex_list.remove(ear);
        convex_vertices.remove(ear);
        ears.remove(ear);
        // Removing previous and next from the potential ears as they can no more triangulate with current-ear
        ears.remove(previous);
        ears.remove(next);

        // Redefining the convex/ reflex nature of the previous and next vertices
        reflex_vertices.remove(previous);
        reflex_vertices.remove(next);
        convex_vertices.remove(previous);
        convex_vertices.remove(next);

        // Getting the coordinates of previous and next so that we can compute their nature

        float a1 = vertices[previous].first;
        float b1 = vertices[previous].second;
        float a2 = vertices[next].first;
        float b2 = vertices[next].second;

        // Updating the nature of previous and next
        auto previous_iterator = find(vertex_list.begin(), vertex_list.end(), previous);
        auto next_iterator = find(vertex_list.begin(), vertex_list.end(), next);
        int previous_of_previous;
        if (previous_iterator==vertex_list.begin()) {
            auto temporary_iterator = vertex_list.end();
            temporary_iterator--;
            previous_of_previous = *temporary_iterator;
        }
        else {
            auto temporary_iterator = previous_iterator;
            temporary_iterator--;
            previous_of_previous = *temporary_iterator;
        }
        int next_of_next;
        temporary_iterator = next_iterator;
        temporary_iterator++;
        if (temporary_iterator==vertex_list.end()) next_of_next = *vertex_list.begin();
        else next_of_next = *temporary_iterator;

        // Coordinates of previous of previous
        float a3 = vertices[previous_of_previous].first;
        float b3 = vertices[previous_of_previous].second;

        // Calculating the cross product
        float crossproduct = (a1-a3)*(b2-b3) - (b1-b3)*(a2-a3);

        // Boolean variables to check nature of the vertices
        bool previous_is_convex = false, next_is_convex = false;

        if (crossproduct > 0.00005){
            convex_vertices.push_back(previous);
            previous_is_convex = true;
        }
        else{
            reflex_vertices.push_back(previous);
        }

        // Coordinates of next of next
        a3 = vertices[next_of_next].first;
        b3 = vertices[next_of_next].second;

        // Calculating the cross product
        crossproduct = (a2-a1)*(b3-b1) - (b2-b1)*(a3-a1);

        if (crossproduct > 0.00005){
            convex_vertices.push_back(next);
            next_is_convex = true;
        }
        else{
            reflex_vertices.push_back(next);
        }

        // Checking if or not the previous and next are ears in the new polygon
        if (previous_is_convex){
            bool previous_is_ear = true;
            // Iterating through all the reflex vertices
            for (auto iterator2=reflex_vertices.begin(); iterator2!=reflex_vertices.end(); iterator2++){
                if (*iterator2 == previous || *iterator2 == next || *iterator2 == previous_of_previous)  {
                    //Should not check for one of the vertices of the triangle
                    continue;
                }
                float a3 = vertices[previous_of_previous].first;
                float b3 = vertices[previous_of_previous].second;
                float a4 = vertices[*iterator2].first;
                float b4 = vertices[*iterator2].second;
                float crossproduct1 = (a1-a3)*(b4-b3) - (b1-b3)*(a4-a3);
                float crossproduct2 = (a2-a1)*(b4-b1) - (b2-b1)*(a4-a1);
                float crossproduct3 = (a3-a2)*(b4-b2) - (b3-b2)*(a4-a2);

                if (crossproduct1 > 0.00005 && crossproduct2 > 0.00005 && crossproduct3 > 0.00005){
                    previous_is_ear = false;
                    break;
                }
            }
            if (previous_is_ear) ears.push_back(previous);
        }
        if (next_is_convex){
            bool next_is_ear = true;
            // Iterating through all the reflex vertices
            for (auto iterator2=reflex_vertices.begin(); iterator2!=reflex_vertices.end(); iterator2++){
                if (*iterator2 == previous || *iterator2 == next || *iterator2 == next_of_next)  {
                    //Should not check for one of the vertices of the triangle
                    continue;
                }
                float a3 = vertices[next_of_next].first;
                float b3 = vertices[next_of_next].second;
                float a4 = vertices[*iterator2].first;
                float b4 = vertices[*iterator2].second;

                float crossproduct1 = (a2-a1)*(b4-b1) - (b2-b1)*(a4-a1);
                float crossproduct2 = (a3-a2)*(b4-b2) - (b3-b2)*(a4-a2);
                float crossproduct3 = (a1-a3)*(b4-b3) - (b1-b3)*(a4-a3);

                if (crossproduct1 > 0.00005 && crossproduct2 > 0.00005 && crossproduct3 > 0.00005){
                    next_is_ear = false;
                    break;
                }
            }
            if (next_is_ear) ears.push_back(next);
        }
    }
    Print_the_Triangles();
    //plot the Triangle
    // Plot_Function(argc, argv);

    return 0;
}