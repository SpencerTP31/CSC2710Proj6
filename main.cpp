#include<iostream>
#include <iomanip>
#include <stack>
#include <queue>
#include "graph.h"
#include "List.h"

using namespace std;
ostream& bold_on(ostream& os)
{
    return os << "\e[1m";
}

ostream& bold_off(ostream& os)
{
    return os << "\e[0m";
}

void load(Graph<int> F, string  letters[], int &count);
int insert(string letters[], int &count, const string &checkLetter);
void print(int finalArr[], string letters[], int nodes);

int main(void)
{
    int edges;
    int nodes;
    int sets;
    cin >> sets;
    for (int i = 0; i < sets; i++)
    {
        bool cycle = false;
        int *topoArr;
        cin >> edges >> nodes;
        cout << setw(10) << bold_on << "Graph " << i+1 << ":" << bold_off << endl;
        topoArr = new int[nodes];
        Graph<int> F(nodes);
        string letters[nodes];
        load(F, letters, edges);
        F.TopologicalOrder(topoArr, cycle);
        if(!cycle)
        {
            print(topoArr, letters, nodes);
            cout << endl;
        }

        cout << endl;
    }
    return 0;
}

void load(Graph<int> F, string  letters[], int &count)
{
    string first;
    string second;
    int to;
    int from;
    int counter = 0;
    for(int i = 0; i < count; i++)
    {
        cin >> first >> second;
        to = insert(letters, counter, first);
        from = insert(letters, counter, second);
        F.AddEdge(to, from);
    }
}

int insert(string letters[], int &count, const string &checkLetter)
{
    for (int i = 0; i < count; i++)
    {
        if(letters[i] == checkLetter)
        {
            return i;
        }
    }
    letters[count++] = checkLetter;
    return count - 1;
}

void print(int finalArr[], string letters[], int nodes)
{
    int temp;
    for (int i = 0; i < nodes; ++i)
    {
        temp = finalArr[i];
        cout << letters[temp] << " ";
    }
}



