#pragma once
#include "ListSequence.h"
#include "LinkedList.h"
#include "Sequence.h"
#include "Matrix.h"
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#define NO_ELEMENT "NO ELEMENT WITH GIVEN KEY"

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9'};

template <class Name, class Weight>
class Graph
{
public:

    template<class V_Name>
    class Vertex {
    private:
        V_Name name;
    public:
        Vertex(V_Name name)
        {
            this->name = name;
        }
        V_Name ReturnName()
        {
            return this->name;
        }
        void ChangeName(V_Name name)
        {
            this->name = name;
        }

    };

    template <class E_Name, class E_Weight>
    class Edge {
    private:
        E_Weight weight;
        Vertex<E_Name>* start;
        Vertex<E_Name>* end;
    public:
        Edge(E_Name first, E_Name second, E_Weight weight)
        {
            this->weight = weight;
            this->start = new Vertex<E_Name>(first);
            this->end = new Vertex<E_Name>(second);
        }

        E_Weight ReturnWeight()
        {
            return this->weight;
        }

        pair<Vertex<E_Name>*, Vertex<E_Name>*> getVertex() {
            return make_pair(start, end);
        }

        Vertex<E_Name>* GetFirst() {
            return this->start;
        }

        Vertex<E_Name>* GetSecond() {
            return this->end;
        }

    };

public:
    Graph(int (*cmp)(Name, Name))
    {
        this->VertexList = new ListSequence<Vertex<Name>*>();
        this->EdgeList = new ListSequence<Edge<Name, Weight>*>();
        this->cmp = cmp;
    }

    ListSequence<Edge<Name, Weight>*>* ReturnEdges() {
        return this->EdgeList;
    }
    ListSequence<Vertex<Name>*>* ReturnVertexes() {
        return this->VertexList;
    }

    int ReturnEdgeNumber()
    {
        return this->EdgeList->GetSize();
    }
    int ReturnVertexNumber()
    {
        return this->VertexList->GetSize();
    }

    void AddVertex(Name name) {

        Vertex<Name>* Add = new Vertex<Name>(name);
        bool contains = false;
        if (containsVertex(name) == -1)
        {
            VertexList->Append(Add);
        }
        else
        {
            cout << "This Vertex is already existing!" << endl;
        }
    }

    virtual void AddEdge(Name start, Name end, Weight weight)
    {
        if (this->containsEdge(start, end) == -1)
        {
            Edge<Name, Weight>* Add = new Edge<Name, Weight>(start, end, weight);
            Vertex<Name>* FAdd = new Vertex<Name>(start);
            Vertex<Name>* SAdd = new Vertex<Name>(end);
            this->EdgeList->Append(Add);

            if (containsVertex(start) == -1)
            {
                VertexList->Append(FAdd);
            }
            if (containsVertex(end) == -1)
            {
                VertexList->Append(SAdd);
            }
        }
        else {
            cout << "This Edge is already existing!" << endl;
        }
    }

    int containsVertex(Name name)
    {
        for (int i = 0; i < this->ReturnVertexNumber(); ++i)
        {
            if (cmp(this->VertexList->Get(i)->ReturnName(), name) == 2)
            {
                return i;
            }
        }
        return -1;
    }

    int containsEdge(Name start, Name end)
    {
        for (int i = 0; i < this->ReturnEdgeNumber(); ++i)
        {
            if (cmp(this->EdgeList->Get(i)->GetFirst()->ReturnName(), start) == 2 && cmp(this->EdgeList->Get(i)->GetSecond()->ReturnName(), end) == 2)
            {
                return i;
            }
        }
        return -1;
    }

    virtual void DeleteEdge(Name start, Name end)
    {
        if (containsEdge(start, end) != -1)
        {
            this->EdgeList->RemoveAt(containsEdge(start, end));
        }
        else
        {
            throw invalid_argument(NO_ELEMENT);
        }
    }

    void DeleteVertex(Name name)
    {
        if (containsVertex(name) != -1)
        {

            for (int i = 0; i < this->ReturnEdgeNumber(); ++i)
            {
                if (cmp(this->EdgeList->Get(i)->GetFirst()->ReturnName(), name) == 2)
                {
                    DeleteEdge(this->EdgeList->Get(i)->GetFirst()->ReturnName(), this->EdgeList->Get(i)->GetSecond()->ReturnName());
                    i--;
                }
                if (cmp(this->EdgeList->Get(i)->GetSecond()->ReturnName(), name) == 2)
                {
                    DeleteEdge(this->EdgeList->Get(i)->GetSecond()->ReturnName(), this->EdgeList->Get(i)->GetFirst()->ReturnName());
                    i--;
                }
            }
            this->VertexList->RemoveAt(this->containsVertex(name));
        }
        else
        {
            throw invalid_argument(NO_ELEMENT);
        }
    }

    CommonMatrix<Weight>* AdjMatrix()
    {
        CommonMatrix<Weight>* matrix = new CommonMatrix<Weight>(this->ReturnVertexNumber());

        for (int i = 0; i < this -> ReturnVertexNumber(); ++i)
        {
            for (int j = 0; j < this -> ReturnVertexNumber(); ++j)
            {
                matrix->SetElement(i, j, 1000000);
            }
        }

        for (int i = 0; i < this -> ReturnEdgeNumber(); ++i)
        {
            int first = 0;
            int second = 0;
            for (int j = 0; j < this -> ReturnVertexNumber(); ++j)
            {
                if ((this -> EdgeList -> Get(i)-> GetFirst() -> ReturnName() == VertexList -> Get(j) -> ReturnName()))  first = j;
                if ((this -> EdgeList -> Get(i)-> GetSecond() -> ReturnName() == VertexList -> Get(j) -> ReturnName()))  second = j;
            }
            if ((matrix->GetElement(first, second) > this -> EdgeList -> Get(i) -> ReturnWeight()))
            {
                matrix->SetElement(first, second, this -> EdgeList -> Get(i) -> ReturnWeight());
            }
        }

        for (int i = 0; i < this -> ReturnVertexNumber(); ++i)
        {
            matrix->SetElement(i, i, 0);
        }

        return matrix;
    }

    void Sort_Help(int p, bool visited[], ListSequence<Name> *stack)
    {
        visited[p] = true;
        for (int i = 0; i < this->ReturnEdgeNumber(); i++)
        {
            if(cmp(this -> EdgeList -> Get(i)-> GetFirst() -> ReturnName(), this -> VertexList->Get(p)->ReturnName()) == 2)
            {
                if (!visited[containsVertex(this -> EdgeList -> Get(i)-> GetSecond() -> ReturnName())])
                {
                    this->Sort_Help(containsVertex(this -> EdgeList -> Get(i)-> GetSecond() -> ReturnName()), visited, stack);
                }
            }
        }
        stack->Prepend(this->VertexList->Get(p)->ReturnName());
    }

    void cycleCheck(int p, int z)
    {
        for (int i = 0; i < this->ReturnEdgeNumber(); i++)
        {
            if(cmp(this -> EdgeList -> Get(i)-> GetFirst() -> ReturnName(), this -> VertexList->Get(p)->ReturnName()) == 2)
            {
                if (cmp(this -> EdgeList -> Get(i)-> GetSecond() -> ReturnName(), this -> VertexList->Get(z)->ReturnName()) == 2)
                {
                    cout << "Graph has Cycles!" << endl;
                    exit(0);
                }
                else
                {
                    cycleCheck(containsVertex(this -> EdgeList -> Get(i)-> GetSecond() -> ReturnName()),z);
                }
            }
        }
    }

    virtual void TopologicalSort()
    {
        ListSequence<Name> *stack = new ListSequence<Name>();
        bool *visited = new bool[this->ReturnVertexNumber()];
        for (int i = 0; i < this->ReturnVertexNumber(); i++)
        {
            visited[i] = false;
        }
        for (int i = 0; i < this->ReturnVertexNumber(); ++i)
        {
            cycleCheck(i, i);
        }
        for (int i = 0; i < this->ReturnVertexNumber(); ++i)
        {
            if (!visited[i])
            {
                this->Sort_Help(i, visited, stack);
            }
        }
        for (int j = 0; j < stack->GetSize(); j += 1)
        {
            this->VertexList->Get(j)->ChangeName(stack->Get(j));
        }
    }

    void EdgeNumSort()
    {
        int count = 0;
        int number = 0;
        int max = -1;
        ArraySequence<int>* Numbers = new ArraySequence<int>(this->ReturnVertexNumber());
        ListSequence<Name>* Names = new ListSequence<Name>();
        ListSequence<Name>* Names_final = new ListSequence<Name>();
        for (int i = 0; i < this->ReturnVertexNumber(); i++)
        {
            Names->Append(this->VertexList->Get(i)->ReturnName());
            for(int j = 0; j < this->ReturnEdgeNumber(); j += 1)
            {
                if(cmp(this -> EdgeList -> Get(j)-> GetFirst() -> ReturnName(), this -> VertexList->Get(i)->ReturnName()) == 2)
                {
                    count += 1;
                }
            }
            Numbers->Set(i, count);
            count = 0;
        }
        for (int i = 0; i < this->ReturnVertexNumber(); i++)
        {
            for (int r = 0; r < Numbers->GetSize(); ++r)
            {
                if (Numbers->Get(r) > max)
                {
                    max = Numbers->Get(r);
                    number = r;
                }
            }
            Numbers->Set(number, -1);
            Names_final->Append(Names->Get(number));
            max = -1;
        }
        for (int i = 0; i < Names_final->GetSize(); i += 1)
        {
            this->VertexList->Get(i)->ChangeName(Names_final->Get(i));
        }
    }

    virtual void RandomGraph(int Vnum, int Enum, int type)
    {
        int max;
        if (type == 1)
        {
            max = Vnum*(Vnum-1);
        }
        else
        {
            max = Vnum*(Vnum-1)/2;
        }
        if (Enum > max || Enum < 1 || Vnum > 61 || Vnum < 2)
        {
            cout << "Cant Do That!" << endl;
            exit(0);
        }
        for (int i = 0; i < Vnum; ++i)
        {
            this->AddVertex(encoding_table[i]);
        }

        if ( Enum == max)
        {
            for (int i = 0; i < this->ReturnVertexNumber(); ++i)
            {
                for (int j = 0; j < this->ReturnVertexNumber(); ++j)
                {
                    if (this->VertexList->Get(i) != this->VertexList->Get(j))
                    {
                        this->AddEdge(this->VertexList->Get(i)->ReturnName(), this->VertexList->Get(j)->ReturnName(), 1 + rand() % 100);
                    }
                }
            }
        }
        else
        {
            srand( time( 0 ) );
            int border = this->ReturnVertexNumber();
            while (Enum > 0)
            {
                int RandN1 = rand() % border ;
                int RandN2 = rand() % border ;
                if (this->containsEdge(this->VertexList->Get(RandN1)->ReturnName(), this->VertexList->Get(RandN2)->ReturnName()) == -1 && (RandN1 != RandN2))
                {
                    this ->AddEdge(this->VertexList->Get(RandN1)->ReturnName(), this->VertexList->Get(RandN2)->ReturnName(), 1 + rand() % 100);
                    --Enum;
                }
            }
        }

    }

    string Tostring(int type)
    {
        stringstream ss;
        string defaultColor = "grey";
        ss << ("digraph G") << "{" << endl;
        ss << "node [style=filled, colorscheme=spectral11];" << endl;
        for (int i = 0; i < this->ReturnVertexNumber(); i ++)
        {
            ss << '"' << this->VertexList->Get(i)->ReturnName() << '"' << ';' << endl;
        }
        for (int i = 0; i < this->ReturnEdgeNumber(); i ++)
        {
            if (type == 1)
            {
                ss << '"' << this->EdgeList->Get(i)->GetFirst()->ReturnName() << '"' << "->" << '"' << this->EdgeList->Get(i)->GetSecond()->ReturnName() << '"' <<'['<<"label="<< this->EdgeList->Get(i)->ReturnWeight() <<"];" << endl;
            }
            else
            {
                if (i % 2 == 1)
                {
                    ss << '"' << this->EdgeList->Get(i)->GetFirst()->ReturnName() << '"' << "->" << '"' << this->EdgeList->Get(i)->GetSecond()->ReturnName() << '"' <<'['<<"label="<< this->EdgeList->Get(i)->ReturnWeight()<<", dir=none" <<"];" << endl;
                }
            }


        }
        ss << '}' << endl;
        return ss.str();
    };

    string PathColorTostring(int type, ArraySequence<int>* array, int operation)
    {
        stringstream ss;
        int stopper;
        string defaultColor = "grey";
        ss << ("digraph G") << "{" << endl;
        ss << "node [style=filled, colorscheme=set312];" << endl;

        if (operation == 1)
        {
            for (int i = 0; i < array->GetSize(); i++)
            {
                ss << '"' << this->VertexList->Get(array->Get(i))->ReturnName() << '"' << "[color=4, fillcolor=9];" << endl;
            }
        }
        for (int i = 0; i < this->ReturnVertexNumber(); i ++)
        {
            if (operation == 2)
            {
                ss << '"' << this->VertexList->Get(i)->ReturnName() << '"' <<'['<<"fillcolor=" << array->Get(i) << ", color = black];" << endl;
            }
            else
            {
                ss << '"' << this->VertexList->Get(i)->ReturnName() << '"' << ';' << endl;
            }
        }

        if (type == 1)
        {
            for (int i = 0; i < this->ReturnEdgeNumber(); i++)
            {
                if (operation == 1)
                {
                    for (int j = 0; j < array->GetSize()-1;j++)
                    {
                        stopper = 0;
                        if (this->EdgeList->Get(i)->GetFirst()->ReturnName() == this->VertexList->Get(array->Get(j))->ReturnName() && this->EdgeList->Get(i)->GetSecond()->ReturnName() == this->VertexList->Get(array->Get(j+1))->ReturnName())
                        {
                            ss << '"' << this->EdgeList->Get(i)->GetFirst()->ReturnName() << '"' << "->" << '"' << this->EdgeList->Get(i)->GetSecond()->ReturnName() << '"' <<'['<<"color = red, label=<<font color=\"red\">"<< this->EdgeList->Get(i)->ReturnWeight() <<"</font>>];" << endl;
                            stopper = 1;
                            break;
                        }
                    }
                    if (stopper == 0)
                    {
                        ss << '"' << this->EdgeList->Get(i)->GetFirst()->ReturnName() << '"' << "->" << '"' << this->EdgeList->Get(i)->GetSecond()->ReturnName() << '"' <<'['<<"label="<< this->EdgeList->Get(i)->ReturnWeight() <<"];" << endl;
                    }

                }
                else
                {
                    ss << '"' << this->EdgeList->Get(i)->GetFirst()->ReturnName() << '"' << "->" << '"' << this->EdgeList->Get(i)->GetSecond()->ReturnName() << '"' <<'['<<"label="<< this->EdgeList->Get(i)->ReturnWeight() <<"];" << endl;
                }
            }
        }
        else
        {
            for (int i = 0; i < this->ReturnEdgeNumber(); i++)
            {
                if (i % 2 == 1)
                {
                    if (operation == 1)
                    {
                        for (int j = 0; j < array->GetSize()-1;j++)
                        {
                            stopper = 0;
                            if (this->EdgeList->Get(i)->GetFirst()->ReturnName() == this->VertexList->Get(array->Get(j))->ReturnName() && this->EdgeList->Get(i)->GetSecond()->ReturnName() == this->VertexList->Get(array->Get(j+1))->ReturnName())
                            {
                                ss << '"' << this->EdgeList->Get(i)->GetFirst()->ReturnName() << '"' << "->" << '"' << this->EdgeList->Get(i)->GetSecond()->ReturnName() << '"' <<'['<<"color = red, dir = none, label=<<font color=\"red\">"<< this->EdgeList->Get(i)->ReturnWeight() <<"</font>>];" << endl;
                                stopper = 1;
                                break;
                            }
                        }
                        if (stopper == 0)
                        {
                            ss << '"' << this->EdgeList->Get(i)->GetFirst()->ReturnName() << '"' << "->" << '"' << this->EdgeList->Get(i)->GetSecond()->ReturnName() << '"' <<'['<<"label="<< this->EdgeList->Get(i)->ReturnWeight()<<", dir=none" <<"];" << endl;
                        }

                    }
                    else
                    {
                        ss << '"' << this->EdgeList->Get(i)->GetFirst()->ReturnName() << '"' << "->" << '"' << this->EdgeList->Get(i)->GetSecond()->ReturnName() << '"' <<'['<<"label="<< this->EdgeList->Get(i)->ReturnWeight()<<", dir=none" <<"];" << endl;
                    }
                }
            }
        }
        ss << '}' << endl;
        return ss.str();
    };

    ~Graph() = default;

private:
    ListSequence<Vertex<Name>*>* VertexList;
    ListSequence<Edge<Name, Weight>*>* EdgeList;
    int (*cmp)(Name, Name);

};




