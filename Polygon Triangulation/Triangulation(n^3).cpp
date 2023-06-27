#include<bits/stdc++.h>
using namespace std;

struct Vertex{
    int x;
    int y;
    Vertex *next;
    Vertex *prev;
};

struct Vector{
    int i;
    int j;
};

struct Connected{
    int x1,y1,x2,y2;
};

struct Line{
    float slope;
    float intercept;
};

struct Triangle{
    int x1,x2,x3,y1,y2,y3;
};

class Doubly_Circular_Linked{
    private:
    
        Vertex * head;
        Vertex * tail;
        int size;
        
    public:
    
        Doubly_Circular_Linked(){
            head = new Vertex;
            tail = new Vertex;
            size = 0;
;        }
    
        void print_list(int mode){
            // Forward Printing
            Vertex *ptr = head;
            if(mode == 1){
                for(int i = 1; i <= size; i++){
                    cout<<check_reflex(ptr)<<" -- ";
                    cout<<ptr->x<<" "<<ptr->y<<endl;
                    ptr = ptr->next;
                }
            }
            // Reverse Printing
            if(mode == -1){
                for(int i = 1; i <= size; i++){
                    cout<<ptr->x<<" "<<ptr->y<<endl;
                    ptr = ptr->prev;
                }
            }
        }
            
        bool check_reflex(Vertex * ptr){
            Vertex * next_vertex = ptr->next;
            Vertex * prev_vertex = ptr->prev;
            Vector v1,v2;
            v1.i = ptr->x - next_vertex->x;
            v1.j = ptr->y - next_vertex->y;
            v2.i = ptr->x - prev_vertex->x;
            v2.j = ptr->y - prev_vertex->y;
            int cross = (v2.i * v1.j) - (v1.i * v2.j);
            // int modulo1 = sqrt((v1.i * v1.i) + (v1.j * v1.j));
            // int modulo2 = sqrt((v2.i * v2.i) + (v2.j * v2.j));
            if(cross > 0) {
                return true;
            }
            else{
                return false;
            }
        }
        
        void del(Vertex * ptr){
            if(size == 0) return;
            size--;
            (ptr->prev)->next = ptr->next;
            (ptr->next)->prev = ptr->prev;
            ptr->prev = NULL;
            ptr->next = NULL;
        }
        
        void add(Vertex * ptr){
            if(size == 0){
                head = ptr;
                tail = ptr;
            }
            else{
                tail->next = ptr;
                ptr->next = head;
                ptr->prev = tail;
                head->prev = ptr;
                tail = ptr;
            }
            size++;
            // cout<<size<<endl;
        }
        
        int get_size(){
            return size;
        }
        
        Vertex * get_head(){
            return head;
        }
};

// Checks if or not the two vertices are on the same sides of the line L
bool Same_Side(Line L, Vertex * v1, Vertex * v2){
    float value1 = (v1->y) - (L.slope)*(v1->x) - L.intercept;
    float value2 = (v2->y) - (L.slope)*(v2->x) - L.intercept;
    if(value1 * value2 > 0) return true;
    return false;
}

int main(){
    // n is the number of vertices
    int n;
    cin>>n; 
    // cout<<"Enter the list of vertices in Clockwise Order"<<endl;
    vector<Connected> pairs;
    Doubly_Circular_Linked vertices;
    for(int i = 1; i<=n; i++){
        Vertex * v = new Vertex;
        int a,b; cin>>a>>b;
        v->x = a;
        v->y = b;
        v->prev = NULL;
        v->next = NULL;
        vertices.add(v);
    }
    // cout<<"List of Vertices"<<endl;
    // vertices.print_list(1);

    Vertex * ptr = vertices.get_head();
    // cout<<"The coordinates of the head are "<<ptr->x<<" "<<ptr->y<<endl;
    // vertices.del(vertices_head -> next);
    // vertices.print_list(1);
    Doubly_Circular_Linked reflex_vertices;
    int vertices_count = vertices.get_size();
    for(int i = 1; i <= vertices_count; i++){

        // cout<<ptr->x<<" "<<ptr->y<<" -- "<<vertices.check_reflex(ptr)<<endl;
        if(vertices.check_reflex(ptr) == 1){
            Vertex * tptr = new Vertex;
            tptr->x = ptr->x;
            tptr->y = ptr->y;
            tptr->next = NULL;
            tptr->prev = NULL;
            reflex_vertices.add(tptr);
        }
        ptr = ptr -> next;
        // cout<<ptr->x<<" "<<ptr->y<<endl;
    }
    // cout<<"The list of Reflex Vertices in the Polygon"<<endl;
    // reflex_vertices.print_list(1);
    // cout<<endl;
    // del(&v[1], n);
    // print_list(head,1,n+1);
    // print_list(tail,-1,n+1);
    // int reflex_vertex_count = reflex_vertices.get_size();
    vector<Triangle> Triangle_list;
    ptr = vertices.get_head();
    for(int i = 1; i <= vertices_count ; i++){
        Connected points;
        points.x1 = ptr->x;
        points.y1 = ptr->y;
        points.x2 = ptr->next->x;
        points.y2 = ptr->next->y;
        pairs.push_back(points);
        ptr = ptr->next;
    }
    ptr = vertices.get_head();
    while(vertices_count > 3){
        vertices_count = vertices.get_size();
        for(int i = 1; i <= vertices_count; i++){
            if(vertices.check_reflex(ptr) == 1){
                // cout<<"Checking the vertex "<<ptr->x<<" "<<ptr->y<<endl;
                Vertex * next_vertex = ptr->next;
                Vertex * prev_vertex = ptr->prev;
                // cout<<"The next vertex is "<<next_vertex->x<<" "<<next_vertex->y<<endl;
                // cout<<"The prev vertex is "<<prev_vertex->x<<" "<<prev_vertex->y<<endl;
                Vertex * tptr = next_vertex->next;
                Line L;
                L.slope = (next_vertex->y - prev_vertex->y)/(next_vertex->x - prev_vertex->x);
                L.intercept = ((prev_vertex->y * next_vertex->x) - (next_vertex->y * prev_vertex->x)) / (next_vertex->x - prev_vertex->x);
                // cout<<"The obtained line is y = x*"<<L.slope<<" + "<<L.intercept<<" is a valid line"<<endl;
                bool valid_diagonal = true;
                for(int i = 1; i<=(vertices_count - 3); i++){
                    if(Same_Side(L, ptr, tptr)){
                        // cout<<tptr->x<<" "<<tptr->y<<" is on the same side as the point"<<endl;
                        valid_diagonal = false; 
                        break;
                    }
                    tptr = tptr->next;
                }
                if(valid_diagonal){
                    Triangle T;
                    T.x1 = ptr->x;
                    T.y1 = ptr->y;
                    T.x2 = next_vertex->x;
                    T.y2 = next_vertex->y;
                    T.x3 = prev_vertex->x;
                    T.y3 = prev_vertex->y;
                    Triangle_list.push_back(T);
                    // cout<<"y = x*"<<L.slope<<" + "<<L.intercept<<" is a valid line"<<endl;
                    tptr = ptr -> next;
                    vertices.del(ptr);
                    ptr = tptr;
                    break;
                    // reflex_vertices.del(ptr);
                }
                else{
                    ptr = ptr->next;
                }
            }
            else{
                ptr = ptr->next;
            }
            // cout<<ptr->x<<" "<<ptr->y<<endl;
        }
        vertices_count = vertices.get_size();
        // cout<<"After the iteration the vertex count is "<<vertices_count<<endl;
        // reflex_vertex_count = reflex_vertices.get_size();
    }
    for(int i = 0; i<Triangle_list.size(); i++){
        Triangle T = Triangle_list[i];
        // cout<<"{ ("<<T.x1<<","<<T.y1<<"), ("<<T.x2<<","<<T.y2<<"), ("<<T.x3<<","<<T.y3<<") }"<<endl;
        Connected c;
        c.x1 = T.x1;
        c.y1 = T.y1;
        c.x2 = T.x2;
        c.y2 = T.y2;
        pairs.push_back(c);
        c.x1 = T.x3;
        c.y1 = T.y3;
        c.x2 = T.x2;
        c.y2 = T.y2;
        pairs.push_back(c);
        c.x1 = T.x1;
        c.y1 = T.y1;
        c.x2 = T.x3;
        c.y2 = T.y3;
        pairs.push_back(c);
    }

    ofstream outfile;
    outfile.open("lines.txt");
    for(int i = 0; i<pairs.size(); i++){
        outfile<<pairs[i].x1<<" "<<pairs[i].y1<<" "<<pairs[i].x2<<" "<<pairs[i].y2<<endl;
    }
    
}