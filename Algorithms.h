#ifndef LAB3_ALGORITHMS_H
#define LAB3_ALGORITHMS_H
#include "Graph.h"
#include "Function.h"
#include "UndirGraph.h"



namespace algorithms
{
    template <class Name, class Weight>
    ArraySequence<int>* Dijkstra(Name first_one, Name last_one, Graph<Name, Weight>* graph, int (*cmp)(Weight, Weight))
    {
        int min;
        CommonMatrix<Weight>* matrix = graph->AdjMatrix();
        ArraySequence<Weight> Path(graph->ReturnVertexNumber());
        ArraySequence<bool> Marked(graph->ReturnVertexNumber());
        ArraySequence<int>* Parent = new ArraySequence<int>();
        int start, temp, temp1, end;

        start = graph->containsVertex(first_one);
        end = graph->containsVertex(last_one);
        if (start == -1 || end == -1)
        {
            Parent->Append(-1);
            return Parent;
        }

        for (int i = 0; i < graph->ReturnVertexNumber(); i++)
        {
            Path.Set(i, 1000000);
            Marked.Set(i, false);
        }
        Path.Set(start, 0);
        temp = start;
        for (int i = 0; i < graph->ReturnVertexNumber(); i++)
        {
            Marked.Set(temp, true);
            min = 1000000;
            for (int j = 0; j < graph->ReturnVertexNumber(); j++)
            {
                if ((j != temp) && cmp((matrix->GetElement(temp, j) + Path.Get(temp)), Path.Get(j)) == 0)
                {
                    Path.Set(j, matrix->GetElement(temp, j) + Path.Get(temp));
                }
                if (Path.Get(j) < min && !Marked.Get(j) && (j != temp))
                {
                    temp1 = j;
                    min = Path.Get(j);
                }
            }
            if (min == 1000000)
            {
                break;
            }
            else
            {
                temp = temp1;
            }
        }

        int weight = Path.Get(end);
        if (weight == 1000000)
        {
            Parent->Append(-1);
            return Parent;
        }
        Parent->Append(end);
        while(end != start)
        {
            for (int i = 0; i < graph->ReturnVertexNumber(); i++)
            {
                if (matrix->GetElement(i, end) != 0)
                {
                    int temp2 = weight - matrix->GetElement(i, end);
                    if (temp2 == Path.Get(i))
                    {
                        weight = temp2;
                        end = i;
                        Parent->Prepend(i);
                    }
                }
            }
        }
        return Parent;
    }

    template <class Name, class Weight>
    ArraySequence<int>* Coloring(UndGraph<Name, Weight>* graph, int (*cmp)(Name, Name))
    {
        graph->EdgeNumSort();

        int next = 0;
        int num = 1;
        ArraySequence<int>* Color= new ArraySequence<int>();
        ArraySequence<int> Marked(graph->ReturnVertexNumber());
        for(int i = 0; i < graph->ReturnVertexNumber(); i += 1)
        {
            Color->Append( -1);
            Marked.Set(i, 0);
        }
        for(int i = 0; i < graph->ReturnVertexNumber(); i += 1)
        {
            if (Color->Get(i) == -1)
            {

                for(int j = 0; j < graph->ReturnVertexNumber(); j += 1)
                {
                    for(int k = 0; k < graph->ReturnEdgeNumber(); k += 1)
                    {
                        if (graph->ReturnEdges()->Get(k)->GetFirst()->ReturnName() == graph->ReturnVertexes()->Get(j)->ReturnName() && Marked.Get(j) == 0 && Color->Get(j)==-1)
                        {
                            Marked.Set(graph->containsVertex(graph->ReturnEdges()->Get(k)->GetSecond()->ReturnName()),1);
                        }
                    }
                }
                for (int z = 0; z < graph->ReturnVertexNumber(); z += 1)
                {
                    if (Marked.Get(z) == 0 && Color->Get(z) == -1)
                    {
                        Color->Set(z, num);
                        next = 1;
                    }
                    Marked.Set(z, 0);
                }
                if (next == 1)
                {
                    next = 0;
                    num += 1;
                }

            }
        }
        return Color;
    }

    template <class Name, class Weight>
    ArraySequence<int>* Bandwidth(Name first_one, Name last_one, Graph<Name, Weight>* graph, int (*cmp)(Weight, Weight))
    {
        Weight temp;
        ArraySequence<Name>* Path = new ArraySequence<Name>();
        ArraySequence<int>* IPath = new ArraySequence<int>();
        ArraySequence<Weight>* weights = new ArraySequence<Weight>();

        for (int i = 0; i < graph->ReturnEdgeNumber(); i += 1)
        {
            if (weights->Contains(graph->ReturnEdges()->Get(i)->ReturnWeight()) == false)
            {
                weights->Append(graph->ReturnEdges()->Get(i)->ReturnWeight());
            }
        }
        int size = weights->GetSize();
        int d = size / 2;
        while (d > 0)
        {
            for (int i = 0; i < size - d; i++)
            {
                int j = i;
                while (j >= 0 && cmp(weights->Get(j) , weights->Get(j + d)) == 1)
                {
                    temp = weights->Get(j);
                    weights->Set(j, weights->Get(j + d));
                    weights->Set(j + d, temp);
                    j--;
                }
            }
            d = d / 2;
        }

        for (int i = weights->GetSize()-1; i >= 0; i--)
        {

            Graph<Name, Weight>* graph1 = new Graph<Name, Weight>(compareT1);
            for (int j = 0; j < graph->ReturnEdgeNumber(); j++)
            {
                if (graph->ReturnEdges()->Get(j)->ReturnWeight() >= weights->Get(i))
                {
                    graph1->AddEdge(graph->ReturnEdges()->Get(j)->GetFirst()->ReturnName(),graph->ReturnEdges()->Get(j)->GetSecond()->ReturnName() ,graph->ReturnEdges()->Get(j)->ReturnWeight());
                }
            }

            ArraySequence<int>* Dij = Dijkstra(first_one, last_one, graph1, compareT1);
            if (Dij->Get(0) != -1)
            {
                for (int k = 0; k < Dij->GetSize(); k++)
                {
                    Path->Append(graph1->ReturnVertexes()->Get(Dij->Get(k))->ReturnName());
                    IPath->Append(graph->containsVertex(graph1->ReturnVertexes()->Get(Dij->Get(k))->ReturnName()));
                }
                delete(graph1);
                return IPath;
            }
            delete(graph1);

        }
        IPath->Append(-1);
        return IPath;
    }



}

#endif
