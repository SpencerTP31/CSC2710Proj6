/*NOTE:
  1) This code is NOT properly documented, however there are some
     instructive comments.
  2) If you want to compile this code, you will need a List, Stack,
     and maybe a queue class.  I'll include the list class.
*/

#include<iostream>
#include <stack>
#include <queue>
#include<limits.h>
#include"List.h"

using namespace std;
#ifndef GRAPH
#define GRAPH

enum colortype {white,gray,black};
#define NIL -1

template<class T>
class Graph
{
private:
    int n;
    int *count;
    colortype *color;  //white - unexplored
    //gray, black - discovered vertices. if (u,v) and
    //vertex u is black, then vertex v is either gray or
    //black, that is all vertices adjacent to black vertices
    //have been discovered.  Gray vertices may have some
    //adjacent white vertices, they represent the frontier
    //between discovered and undiscovered vertices.
    int *dist;    //distance from source s to vertex u
    int *pred;    //predecessor of u
    int *dt;    //discovery time
    int *ft;    //finished time
    //u is white before dt[u], gray between dt[u] and ft[u]
    //and black after ft[u].
    int time;
    List<T> *headnodes;
public:
    Graph(const int vertices=0):n(vertices)
    {
        headnodes = new List<T>[n];   //holds the graph
        count = new int[n];           //used in Topological order
        color = new colortype[n];
        dist = new int[n];
        pred = new int[n];
        dt = new int[n];
        ft = new int[n];
        for(int i=0;i<n;i++)   //used in topological ordering
            count[i]=0;         //count is the in-degree for a vertex.
    }
    ~Graph()
    {
        /*delete []headnodes;
        delete []count;
        delete []color;
        delete []dist;
        delete []pred;
        delete []dt;
        delete []ft;*/
    }


    //adds edge <i.j> to the graph
    //count[j] is tracking the in-degree of vertex j.
    //if there is a weight on the edge, then you need to modify
    //the item your are adding, add a struct element that contains
    //j and the weight.
    bool AddEdge(int i, int j)
    {
        count[j]++;
        return headnodes[i].add(j);
    }



    void DFS(void)
    {
        int u;
        for(int u=0;u<n;u++) {
            color[u]=white;
            pred[u]=NIL;
        }
        time=0;              //this will find continue even if the
        //graph is not connected.
        cout<<"DFS - ";
        for(int u=0;u<n;u++)
            if(color[u]==white)
                DFSVisit(u);
        cout<<endl;
    }
    void DFSVisit(int u)
    {
        color[u]=gray;
        cout<<u<<"  ";   //vertex you are processing
        time++;
        dt[u]=time;
        typename List<T>::Iterator li = headnodes[u].begin();
        int v;
        while(li != headnodes[u].end()) {
            v=*li;
            //cout here to print the edges considering.
            if(color[v]==white) {
                //cout here to print the edges used in the solution.
                pred[v]=u;
                DFSVisit(v);
            }
            ++li;
        }
        color[u]=black;
        ft[u]=++time;
    }


    //BFS starting at vertex s
    void BFS(int s)
    {
        int u,v;

        //use a for loop to initialize each vertex color, dist, pred
        //NOTE - dist is the number of edges traversed to get to a vertex
        //to white, INT_MAX, and NIL respectively.
        for(int i=0;i<n;i++) {



        }

        //set the color of s to gray
        //        dist of s to 0
        //        pred of s to NIL

        //istanciate a Queue and enqueue s

        cout<<"BFS - ";
        //while(!Q.isEmpty())
        {
            //dequeue a vertex, name it u and output it's value


            //iterate through the adjacency List of u (use list iterator)
            //use v to hold the vertex adjacent from u
            //if v is white,
            //   color it gray,
            //   dist to v one more than dist to u
            //   pred of v is u
            //   enqueue v

            //after processing the adjacency List of u, color it black
        } //end of while
        cout<<endl;
    }


    void PrintPath(int s, int v)
    {
        //print the vertices on a shortest path from s to v,
        //assumes BFS (or something) has setup pred.
        //could recurse itself to death!
        if(v==s)
            cout<<s<<" ";
        else if (pred[v]==NIL)
            cout<<"no path from "<<s<<" to "<<v<<" exists."<<endl;
        else {
            PrintPath(s,pred[v]);
            cout<<v<<" ";
        }
    }

/*TopologicalOrder Function:
 *      Uses the graph with the load nodes and puts them in a stack in order to sort them
 *
 *precondition:
 *      takes finalArr[] which is an empty array that will hold the numbers once
 *      topological has ran
 *      isCycle is reference flag that will be triggered if a cycle is found
 *
 *post condition:
 *      Once the function is complete the correct topological order will be stored in the finalArr[]
 *      and if isCycle is set the true the print function will not be ran in main
 */
    void TopologicalOrder(int finalArr[], bool &isCycle)
    {
        stack<int> S;
        int i, u;
        for (i = 0; i < n; i++)
        {
            if(count[i] == white)
            {
                S.push(i);
            }
        }
        for (i = 0; i < n; i++)
        {
            if(S.empty())
            {
                isCycle = true;
                cout << "No Topological Ordering Possible" << endl;
                i = n;
            }
            else
            {
                u = S.top();
                finalArr[i] = u;
                S.pop();
                typename List<T>::Iterator Li = headnodes[u].begin();
                int v;
                while (Li != headnodes[u].end()) {
                    v = *Li;
                    count[v]--;
                    if (count[v] == 0) {
                        S.push(v);
                    }
                    ++Li;
                }
            }
        }
    }
};

#endif
