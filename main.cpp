#include <iostream>
#include "Graph.h"
#include "Function.h"
#include "Algorithms.h"
#include "UndirGraph.h"
using namespace algorithms;

const string WhatNameV = "Enter Vertex Name: ";
const string WhatNameE1 = "Enter Start Vertex Name: ";
const string WhatNameE2 = "Enter End Vertex Name: ";
const string WhatNameE3 = "Enter Weight: ";
const string Shortest = "The Shortest Path: ";


void ChooseRealization()
{
    cout << ("Choose type of graph:") << endl;
    cout << ("1 <- Directed") << endl;
    cout << ("2 <- Undirected") << endl;
}

void ChooseAction()
{
    cout << ("1 <- Add Vertex/Edge") << endl;
    cout << ("2 <- Delete Vertex/Edge") << endl;
    cout << ("3 <- Adjacency Matrix") << endl;
    cout << ("4 <- Find Shortest Path") << endl;
    cout << ("5 <- Find Highest Throughput Path") << endl;
}

void ChooseAddFunction()
{
    cout << ("What do you want to do?") << endl;
    cout << ("1 <- Add Vertex") << endl;
    cout << ("2 <- Add Edge") << endl;
    cout << ("0 <- Go back") << endl;
}

void ChooseDeleteFunction()
{
    cout << ("What do you want to do?") << endl;
    cout << ("1 <- Delete Vertex") << endl;
    cout << ("2 <- Delete Edge") << endl;
    cout << ("0 <- Go back") << endl;
}

template <class Name, class Weight>
void Actions(int action, Graph<Name, Weight>* graph)
{
    int choice, weight;
    char start, end, name, name1;
    ArraySequence<int>* Path;
    ArraySequence<char>* Path1;
    switch (action)
    {
        default:
            exit(1);
        case 1:

            while(true)
            {
                ChooseAddFunction();
                cin >> choice;
                if (choice == 1)
                {
                    cout << WhatNameV;
                    cin >> name;
                    cout << endl;
                    graph->AddVertex(name);
                }
                else if (choice == 2)
                {
                    cout << WhatNameE1;
                    cin >> name;
                    cout << endl;
                    cout << WhatNameE2;
                    cin >> name1;
                    cout << endl;
                    cout << WhatNameE3;
                    cin >> weight;
                    cout << endl;
                    graph->AddEdge(name, name1, weight);

                }
                else
                {
                    break;
                }

            }
            break;
        case 2:
            while(true)
            {
                ChooseDeleteFunction();
                cin >> choice;
                if (choice == 1)
                {
                    cout << WhatNameV;
                    cin >> name;
                    cout << endl;
                    graph->DeleteVertex(name);
                }
                else if (choice == 2)
                {
                    cout << WhatNameE1;
                    cin >> name;
                    cout << endl;
                    cout << WhatNameE2;
                    cin >> name1;
                    cout << endl;
                    graph->DeleteEdge(name, name1);
                }
                else
                {
                    break;
                }

            }
            break;
        case 4:
            weight = 0;
            cout << WhatNameE1;
            cin >> start;
            cout << endl;
            cout << WhatNameE2;
            cin >> end;
            cout << endl;
            if (graph->containsVertex(start) != -1 && graph->containsVertex(end) != -1)
            {
                Path = Dijkstra(start, end, graph, compareT1);
                if (Path->Get(0) == -1)
                {
                    cout << "This Path Doesnt Exist!" << endl;
                }
                cout << Shortest << endl;
                for(int i = 0; i < Path->GetSize()-1; i += 1)
                {
                    weight += graph->ReturnEdges()->Get(graph->containsEdge(graph->ReturnVertexes()->Get(Path->Get(i))->ReturnName(),
                                                                            graph->ReturnVertexes()->Get(Path->Get(i + 1)) -> ReturnName())) -> ReturnWeight();

                    cout << graph->ReturnVertexes()->Get(Path->Get(i))->ReturnName() << "  --->  ";
                }
                cout << graph->ReturnVertexes()->Get(Path->Get(Path->GetSize()-1))->ReturnName() << endl;
                cout << "The Weight is:  " << weight << endl;
            }
            else
            {
                cout << "Invalid Vertex Names! Try Again!" << endl;
            }
            break;

        case 5:
            weight = 10000;
            cout << WhatNameE1;
            cin >> start;
            cout << endl;
            cout << WhatNameE2;
            cin >> end;
            cout << endl;
            Path1 = Bandwidth(start, end, graph, compareT1);
            if (Path1->Get(0) == -1)
            {
                cout << "This Path Doesnt Exist!" << endl;
            }
            else
            {
                for (int i = 0; i < Path1->GetSize()-1; i++)
                {
                    if (graph->containsEdge(Path1->Get(i), Path1->Get(i+1)) && graph->ReturnEdges()->Get(graph->containsEdge(Path1->Get(i), Path1->Get(i+1)))->ReturnWeight() < weight)
                    {
                        weight = graph->ReturnEdges()->Get(graph->containsEdge(Path1->Get(i), Path1->Get(i+1)))->ReturnWeight();
                    }
                    cout <<  Path1->Get(i) << "  --->  ";
                }
                cout <<  Path1->Get(Path1->GetSize()-1) << endl;
                cout <<  "The Weight is - " << weight << endl;
            }
            break;

        case 3:

            CommonMatrix<int>* matrix = graph->AdjMatrix();
            ListSequence<Graph<char, int>::Vertex<char>*>* Names = graph->ReturnVertexes();

            cout  << "Adjacency Matrix:" << endl;
            cout << "    ";

            for (int i = 0; i < graph->ReturnVertexNumber(); i++)
            {
                cout << Names->Get(i)->ReturnName() << "    ";
            }
            cout << endl;
            for (int i = 0; i < graph->ReturnVertexNumber(); i++)
            {
                cout << "-----";
            }
            cout<<endl;

            for (int i = 0; i < graph->ReturnVertexNumber(); i++)
            {
                cout << Names->Get(i)->ReturnName() << " | ";
                for (int j = 0; j < graph->ReturnVertexNumber(); j++)
                {

                    cout.width(3);
                    cout.setf(ios::left);

                    if (matrix->GetElement(i, j) != 10000) {
                        cout << matrix->GetElement(i, j) << "  ";
                    }
                    else {
                        cout << "-" << "  ";
                    }
                }
                cout << endl;
            }
            break;
    }
}

void DirGraphMenu()
{
    Graph<char, int>* graph = new Graph<char, int>(compareT1);
    while(true)
    {
        cout << ("----------------------------------------------\n");
        ChooseAction();
        cout << ("6 <- Topological Sort") << endl;
        cout << ("0 <- Exit") << endl;
        cout << ("----------------------------------------------\n");
        int action = 0;
        cin >> action;
        if (action == 0)
        {
            cout << ("Exit!\n");
            break;
        }
        else if(action == 6)
        {
            graph->TopologicalSort();
            cout << "Sorted Vertex Names: ";
            for (int j = 0; j < graph->ReturnVertexNumber(); j += 1)
            {
                cout << graph->ReturnVertexes()->Get(j)->ReturnName() << "  ";
            }
            cout << endl;
        }
        else
        {
            Actions(action, graph);
        }    
    }

}

void UndirGraphMenu()
{
    UndGraph<char, int>* graph = new UndGraph<char, int>(compareT1);
    while(true)
    {
        cout << ("----------------------------------------------\n");
        ChooseAction();
        cout << ("6 <- Coloring") << endl;
        cout << ("0 <- Exit") << endl;
        cout << ("----------------------------------------------\n");
        int action = 0;
        cin >> action;
        if (action == 0)
        {
            cout << ("Exit!\n");
            break;
        }
        else if (action == 6)
        {
            cout << "Graph will be sorted based on the number of edges of vertex!" << endl;
            ArraySequence<int> Colors = Coloring(graph, compareT1);

            for (int i = 0; i < Colors.GetSize(); i += 1)
            {
                cout << "Vertex: " << graph -> ReturnVertexes()->Get(i)->ReturnName() << " - Color #" << Colors.Get(i) << endl;
            }
        }
        else
        {
            Actions(action, graph);
        }    
    }
}

int main()
{
    int choice;
    ChooseRealization();
    cin >> choice;
    while (choice != 1 && choice != 2)
    {
        cout << ("Wrong number, try again!") << endl;
        cin >> choice;
    }
    if (choice == 1)
    {
        DirGraphMenu();
    }
    else
    {
        UndirGraphMenu();
    }

}

