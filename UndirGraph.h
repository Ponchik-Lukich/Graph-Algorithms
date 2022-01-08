#pragma once

#include "Graph.h"
const string IMPOSSIBLE = "Impossible to do this in undirected graph";
using namespace std;

template <class Name, class Weight>
class UndGraph : virtual public Graph<Name, Weight>
{
public:
    template<class V_Name>
    class Vertex : virtual public Vertex<Name>{};

    template <class E_Name, class E_Weight>
    class Edge : virtual public Edge<Name, Weight>{};

public:
    UndGraph(int (*cmp)(Name, Name)) : Graph<Name, Weight>(cmp) {};

    void AddEdge(Name start, Name end, Weight weight) override
    {
        if (this->containsEdge(start, end) == -1)
        {
            Graph<Name, Weight>::AddEdge(start, end, weight);
            Graph<Name, Weight>::AddEdge(end, start, weight);
        }
        else {
            cout << "This Edge is already existing!" << endl;
        }
    }

    void DeleteEdge(Name start, Name end)
    {
        if (this->containsEdge(start, end) != -1)
        {
            Graph<Name, Weight>::DeleteEdge(start, end);
            Graph<Name, Weight>::DeleteEdge(end, start);
        }
        else
        {
            throw invalid_argument(NO_ELEMENT);
        }
    }

    void TopologicalSort() override
    {
        throw invalid_argument(IMPOSSIBLE);
    }

};