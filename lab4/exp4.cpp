#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <stack>
#define UNVISITED 0
#define VISITED 1
#define INFINITY 9999;
using namespace std;

template <typename E> class AQueue{
        private:
        int maxSize;               // Maximum size of queue
        int front;                 // Index of front element
        int rear;                  // Index of rear element
        E *listArray;           // Array holding queue elements

        public:
        AQueue(int size =100) {  // Constructor 
            // Make list array one position larger for empty slot
            maxSize = size+1;
            rear = 0;  front = 1;
            listArray = new E[maxSize];
        }

        ~AQueue() { delete [] listArray; } // Destructor

        void clear() { rear = 0; front = 1; } // Reinitialize

        void enqueue(const E& it) {     // Put "it" in queue
            if(((rear+2)%maxSize)==front) {cout<<"FULL"; return;}
            rear = (rear+1) % maxSize;       // Circular increment
            listArray[rear] = it;
        }

        E dequeue() {           // Take element out
            if(length()==0) {cout<<"EMPTY";return 0;}
            E it = listArray[front];
            front = (front+1) % maxSize;    // Circular increment
            return it;
        }

        const E& frontValue() const {  // Get front value
            if(length()==0) {cout<<"EMPTY";return 0;}
            return listArray[front];
        }

        virtual int length() const         // Return length
        { return ((rear+maxSize) - front + 1) % maxSize; }
    };

AQueue<int>* Q;

class MSTedge{ // a class denoting an edge in the MST 
    public:
        int s; // index of starter vertex
        int d; // index of end vertex
        int wt; // weight of the edge
        MSTedge(int s1, int d1, int wt1) // the constructor
        {
            s=s1;
            d=d1;
            wt=wt1;
        }

        bool operator >(const MSTedge& e2) //overloaded > operator used in sorted MST edge
        {
            if(wt>e2.wt) // return ture if the weight exceeds the other's
                {
                return true;
                }
            else if(wt==e2.wt) // if the weight is equal to each other
                {
                if(s>e2.s) // choose the smaller starter one
                    return true;
                }
                return false;
        }

};

class graph{// the class denotes graph and its operators
    private:
        int numv,nume; // number of vertex , and number of edges
        int **matrix; // the physical space claimed for storing items of the matrix
        int *mark; // a mark array to denote the status of a vertax (whether visited)
        bool hascycle; // a marker used in the detection of cycles
        int count=0; // counter in iterations
        stack<MSTedge> MST; // storing the graph's MST
    public:
        graph(int numv) // the constructor receiving the number of vertexes
        {
            init(numv); // call the initial function
        }
  
        void init(int n)
        {
            int i;
            numv=n; //set the number of vertexes
            nume=0; //set the number of edges to be zero
            mark=new int[n]; // claim space for the mark array
            for(i=0;i<numv;i++) // initialize the mark array to be all UNVISITED
                mark[i]=UNVISITED; 
            matrix = (int**) new int*[numv]; //claim space for the matrix
            for(i=0;i<numv;i++) 
                matrix[i]=new int[numv]; 
            for(i=0;i<numv;i++)
                for(int j=0;j<numv;j++) // initialize the matrix to be all 0
                    matrix[i][j]=0;
        }

        int n() {return numv;} //return the current number of vertexes

        int e() {return nume;} //return the current number of edges

        int first(int v) //return index of the first correlated vertex
        {
            for (int i=0;i<numv;i++)
                if(matrix[v][i]!=0) return i;
            return numv;
        }

        int next(int v, int w) // return index of the next correlated vertex after w
        {
            for (int i=w+1;i<numv;i++)
                if(matrix[v][i]!=0) return i;
            return numv;
        }

        void setedge(int v1, int v2, int wt) // set the edge
        {
            if(wt<=0) { cout<<"Invalid weight!"; return;}
            if(matrix[v1][v2]==0 && matrix[v1][v2]==0) nume++;
            matrix[v1][v2]=wt; //because it's a undirected graph
            matrix[v2][v1]=wt;
        }

        void deledge(int v1, int v2) //delete the edge
        {
            if(matrix[v1][v2]!=0 && matrix[v1][v2]!=0) nume--; // if it is a edge let the number of edges decrease
            matrix[v1][v2]=0; //because it's a undirected graph
            matrix[v2][v1]=0;
        }

        bool isedge(int i, int j)  //judge whether a given pair is an edge
        {
            return matrix[i][j]!=0; 
        }

        int weight(int i, int j) //return the weight of an edge
        {
            return matrix[i][j];
        }

        int getmark(int v)// judge whether a given index of vertex has been visited
        {
            return mark[v];
        }

        void setmark(int v, int val) //set the mark number of a vertex
        {
            mark[v]=val;
        }

        void DFS() // depth first search to be called 
        {
            count=0;//set the counter for iteration to be 0
            int v; // the index used in DFS
            for (v=0;v<numv;v++) //initialize status of vertexes
                setmark(v,UNVISITED); 
            for(v=0;v<numv;v++) 
                if(getmark(v)==UNVISITED) //if the vertex hasn't be visited
                    DFShelp(v); //call the help function
        }

        void DFShelp(int v) // Depth first search
        { 
            cout<<v+1;           // Take appropriate action
            if(count++!=numv-1) cout<<" "; // the print principle
            else cout<<endl; 
            setmark(v, VISITED); //set the mark to be visited
            for (int w=first(v); w<n(); w = next(v,w)){ 
              if(getmark(w)==VISITED) //if meets an vertex that has be visited
                hascycle=1; //has a cycle
              else if (getmark(w) == UNVISITED)
               DFShelp(w);//search
            }
        }

        void BFS() // broad first search
        {
            int v;
            count=0;//set the counter for iteration to be 0
            for (v=0;v<numv;v++)
                setmark(v,UNVISITED); //initialize status of vertexes
                Q = new AQueue<int>(numv);//queue
            for(v=0;v<numv;v++) 
                if(getmark(v)==UNVISITED)
                    BFShelp(v,Q); //search regressive
        }

        void BFShelp(int start, AQueue<int>* Q)  //helper function
        {
            int v, w;
            Q->enqueue(start);         // Initialize Q
            setmark(start, VISITED);
            while (Q->length() != 0) { // Process all vertices on Q
                v = Q->dequeue();
                cout<<v+1;          // Take appropriate action
                if(count++!=numv-1) cout<<" ";
                else cout<<endl;
                for (w=first(v); w<n(); w = next(v,w))
                if (getmark(w) == UNVISITED) {
                    setmark(w, VISITED);
                    Q->enqueue(w);
                }
            }
        }

        int minVertex(int* D) // Find min cost vertex
        { 
            int i, v = -1;
            // Initialize v to some unvisited vertex
            for (i=0; i<numv; i++)
                if (getmark(i) == UNVISITED) { v = i; break; }
            for (i++; i<numv; i++)  // Now find smallest D value
                if ((getmark(i) == UNVISITED) && (D[i] < D[v]))
                v = i;
            return v;
        }


        void Dijkstra(int* D, int s,int* p) //to get minium path
        {
            int i, v, w;
            int it;
            for (it=0;it<numv;it++)
                setmark(it,UNVISITED);
            for (i=0; i<numv; i++) {      // Process the vertices
                v = minVertex(D);
                if(D[v]==9999) //if the vertex cannont be reached
                {
                    return;
                }
                setmark(v, VISITED); //set the vertex to be visited
                for (w=first(v); w<numv; w =next(v,w)){ // iterate through his correlated vertexes
                    if (D[w] > (D[v] + weight(v, w)))
                        {
                            p[w]=v; // the array memorizing path
                            D[w] = D[v] + weight(v, w); // the path
                        }
                }
            }
        }

        void AddEdgetoMST(int v1, int v2) //add an edge to MST
        {
            if(v1>v2) // ensure that the started index is less than the end index
            {
                int temp;
                temp=v1;
                v1=v2; // change the value if s>e
                v2=temp;
            }
            int wt=weight(v1,v2); //set the weight
            MSTedge e(v1,v2,wt); // call constructor to construct a MSTedge 
            MST.push(e); //put the MST edge into our MST
        }

        void Prim(int* D, int s) // Prim's MST algorithm
        { 
            int it;
            for (it=0;it<numv;it++)
                setmark(it,UNVISITED);
            int V[numv];                     // Store closest vertex
            int i, w;
            for (i=0; i<numv; i++) {         // Process the vertices
                int v = minVertex(D);
                setmark(v, VISITED);
                if (v != s)
                AddEdgetoMST(V[v], v);         // Add edge to MST
                if (D[v] == 9999) return;    // Unreachable vertices
                for (w=first(v); w<numv; w = next(v,w))
                if (D[w] > weight(v,w)) {
                    D[w] = weight(v,w);       // Update distance
                    V[w] = v;                    // Where it came from
                }
            }
        }

        void cycle() // judge if there is a cycle in the graph 
        {
            if(hascycle==1) cout<<"YES";
            else cout<<"NO";
        }

        stack<MSTedge> asdSort(stack<MSTedge>&  s) //sort the  MST into wanted order 
        {
            stack<MSTedge> s1; // the temporary one
            while(!s.empty())
            {
                MSTedge t=s.top(); //change the place
                s.pop();
                while(!s1.empty()&&t>s1.top())
                {
                    s.push(s1.top());
                    s1.pop();
                }
                s1.push(t); //read the t into the MST
            }
            return s1; // return the result
        }

        void printMST() // print our the MST 
        {
            stack<MSTedge> temp=asdSort(MST);
            while(!temp.empty())
            {
                MSTedge temp1=temp.top();
                temp.pop();
                cout<<temp1.s+1<<' '<<temp1.d+1<<' '<<temp1.wt<<endl;
            }
        }

};


int main()
{
    int numv,nume; 
    scanf("%d%d",&numv,&nume); 
    graph g(numv); 
    for(int i=0;i<nume;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        g.setedge(a-1,b-1,c);
    }
    g.BFS();
    g.DFS();
    int D[numv];
    for (int i=0; i<numv; i++)  // Initialize 
        D[i] = INFINITY;
    D[0] = 0;
    int p[numv]; //path array
    for(int i=0;i<numv;i++)
        p[i]=0;
    g.Dijkstra(D,0,p);
    for(int i=1;i<numv;i++) // print the right oder of the shortest path
    {
        stack<int> path;
        path.push(p[i]);
        while(1)
        {
            if(path.top()!=0)
                path.push(p[path.top()]);
            else break;
        }
        while(!path.empty())
        {
            cout<<(path.top())+1<<' ';
            path.pop();
        }
        cout<<i+1<<' '<<D[i]<<endl;
    }
    int D1[numv]; // disistra array
    for (int i=0; i<numv; i++)     // Initialize the array
        D1[i] = INFINITY;
    D1[0] = 0;
    g.Prim(D1,0); //call prim
    g.printMST(); //call printMST
    g.cycle(); //call if there is a cycle
    getchar();
    getchar();
    
}