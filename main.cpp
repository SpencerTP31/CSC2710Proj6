/*
 * Author: Spencer Peters
 * Date: 11/19/18
 * Class: CSC-2710
 * File Location: ~/CSC2710/Proj6
 *
 * This program loads in a graph and outputs it in topological order
 *
 * To compile g++ main.cpp and then use IO redirection to run, a.out < (filename)
 */
#include<iostream>
#include <iomanip>
#include <stack>
#include <queue>
#include "graph.h"
#include "List.h"

using namespace std;
//This was just me playing around with different i/o stream manipulation
ostream& bold_on(ostream& os)
{
    return os << "\e[1m";
}

ostream& bold_off(ostream& os)
{
    return os << "\e[0m";
}

//Function Prototypes
void load(Graph<int> F, string  letters[], int &count);
int insert(string letters[], int &count, const string &checkLetter);
void print(int finalArr[], string letters[], int nodes);

/*Main Function:
 *      Main is used to call the other functions needed to properly traverse the graph in topological order
 */
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
        //Me using setw playing with iomanip
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

/*load Function:
 *      File loads in data from the text file and loads it into a graph
 *
 *precondition:
 *      This function takes
 *      F the graph the nodes will be stored in
 *      letters an empty array that will later hold the letters used in the graph
 *      count a counter for the amount of edges sent from main
 *
 *post condition:
 *      Once the function has completed the F will be filled with the correct nodes
 *      letters will be filled with the letters in the graph with no duplicates
 *      and count will not be changed
 */
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

/*insert Function:
 *      Converts the letters to a number and checks to see if a letter is in the letters array
 *      yet and if not inserts it
 *
 *precondition:
 *      Takes the string of letters in order to determine whether the letter has been used or not yet
 *      and takes the checkLetter to convert to a number which is the position the letter is in in the array
 *      of letters
 *post condition:
 *      Once the function has completed the checkLetter will either be inserted into the letters array or the
 *      subscript of the letter in the array will be returned
 */
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

/*print Function:
 *      Prints the final array sorted in topological order
 *
 *precondition:
 *      takes the sorted array and the letters and prints them
 *
 *post condition:
 *      Once the function is complete the output will be properly displayed
 */
void print(int finalArr[], string letters[], int nodes)
{
    int temp;
    for (int i = 0; i < nodes; ++i)
    {
        temp = finalArr[i];
        cout << letters[temp] << " ";
    }
}



