#include "gtest/gtest.h"
#include "../../ListSequence.h"
#include "../../ArraySequence.h"
#include "../../Graph.h"
#include "../../UndirGraph.h"
#include "../../Algorithms.h"
#include "../../Complex.h"
#include "../../Function.h"


using namespace algorithms;

int arr[] = {1, 2, 3, 4, 5};
float arr2[] = {1.1, 2.2, 3.3, 4.4, 5.5};
int arr3[] = {4, 323, -999, 8, 5};
double arr4[] = {1.112, 5.3, 1.111, 2.5, 7.9, 525.0, -76.5};
complex arr5[] = {complex(3,3), complex(1,1), complex(2,2), complex(1, 2)};

Graph<char, int>* graph = new Graph<char, int>(compareT1);
UndGraph<char, int>* graph1 = new UndGraph<char, int>(compareT1);
int *array_1 = arr;
float *array_2 = arr2;
int *array_3 = arr3;
double  *array_4 = arr4;
complex *array_5 = arr5;


TEST(DynamicArray, Default)
{
    DynamicArray<int> array = DynamicArray<int>(0);
    ASSERT_EQ(0, array.GetSize());
}

TEST(DynamicArray, Getsize)
{
    DynamicArray<int> array = DynamicArray<int>(10);
    ASSERT_EQ(10, array.GetSize());
}

TEST(DynamicArray, Float)
{
    DynamicArray<float> array = DynamicArray<float>(array_2,5);
    ASSERT_EQ(5, array.GetSize());
    EXPECT_FLOAT_EQ(1.1, array.Get(0));
    EXPECT_FLOAT_EQ(5.5, array.Get(4));
}

TEST(DynamicArray, FromArray_Get)
{
    DynamicArray<int> array = DynamicArray<int>(array_1, 5);
    ASSERT_EQ(5, array.GetSize());
    ASSERT_EQ(1, array.Get(0));
    ASSERT_EQ(5, array.Get(4));
}

TEST(DynamicArray, Set)
{
    DynamicArray<int> array = DynamicArray<int>(3);
    array.Set(2,999);
    ASSERT_EQ(999, array.Get(2));
}

TEST(DynamicArray, Resize)
{
    DynamicArray<int> array = DynamicArray<int>(array_1, 5);
    array.Resize(3);
    ASSERT_EQ(3, array.Get(2));
}

TEST(LinkedList, InitDefault)
{
    LinkedList<int> arr = LinkedList<int>();
    ASSERT_EQ(0, arr.GetLength());
}

TEST(LinkedList, Creation_from_array)
{
    LinkedList<int> list = LinkedList<int>(array_1, 5);
    ASSERT_EQ(5,list.GetLength());
}

TEST(LinkedList, Get)
{
    LinkedList<int> list = LinkedList<int>(array_1, 5);
    ASSERT_EQ(1,list.Get(0));
    ASSERT_EQ(5,list.Get(4));
}

TEST(LinkedList, float)
{
    LinkedList<float> list = LinkedList<float>(array_2, 5);
    EXPECT_FLOAT_EQ(1.1,list.Get(0));
    EXPECT_FLOAT_EQ(5.5,list.Get(4));
}

TEST(LinkedList, GetLast_GetFirst)
{
    LinkedList<int> list = LinkedList<int>(array_1, 5);
    ASSERT_EQ(1,list.GetFirst());
    ASSERT_EQ(5,list.GetLast());
}

TEST(LinkedList, Getsublist)
{
    LinkedList<int> list = LinkedList<int>(array_1, 5);
    LinkedList<int>* list1 = new LinkedList<int>();
    list1 = list.GetSublist(1,3);
    ASSERT_EQ(2,list1->GetFirst());
    ASSERT_EQ(4,list1->GetLast());
}

TEST(LinkedList, Append)
{
    LinkedList<int> list = LinkedList<int>(array_1, 5);
    list.Append(22);
    ASSERT_EQ(22, list.Get(5));
}

TEST(LinkedList, Prepend)
{
    LinkedList<int> list = LinkedList<int>(array_1, 5);
    list.Prepend(22);
    ASSERT_EQ(22, list.Get(0));
}

TEST(LinkedList, Insert)
{
    LinkedList<int> list = LinkedList<int>(array_1, 5);
    list.InsertAt(11,2);
    ASSERT_EQ(11, list.Get(2));
}

TEST(LinkedList, Clear)
{
    LinkedList<int> list = LinkedList<int>(array_1, 5);
    list.Clear();
    ASSERT_EQ(0, list.GetLength());
}

TEST(ArraySequence, Get_First_Last)
{
    DynamicArray<int> array = DynamicArray<int>(array_1, 5);
    ArraySequence<int> seq = ArraySequence<int>(&array);
    ASSERT_EQ(1, seq.GetFirst());
    ASSERT_EQ(5, seq.GetLast());
}

TEST(ArraySequence, GetSubseq)
{
    DynamicArray<int> array = DynamicArray<int>(array_1, 5);
    ArraySequence<int> seq = ArraySequence<int>(&array);
    ArraySequence<int> *seq1 = new ArraySequence<int>();
    seq1 = seq.GetSubSequence(0, 1);
    ASSERT_EQ(1, seq1->GetFirst());
    ASSERT_EQ(1, seq1->GetLast());
}

TEST(ArraySequence, Set1)
{
    DynamicArray<int> array = DynamicArray<int>(array_1, 5);
    ArraySequence<int> seq = ArraySequence<int>(&array);
    seq.Set(0,11);
    ASSERT_EQ(11, seq.Get(0));
}

TEST(ListSequence, Get_First_Get_Last)
{
    LinkedList<int> list = LinkedList<int>(array_1, 5);
    ListSequence<int> seq = ListSequence<int>(&list);
    ASSERT_EQ(1, seq.GetFirst());
    ASSERT_EQ(5, seq.GetLast());
}

TEST(ListSequence, GetSize)
{
    LinkedList<int> list = LinkedList<int>(array_1, 5);
    ListSequence<int> seq = ListSequence<int>(&list);
    ASSERT_EQ(5, seq.GetSize());
}

TEST(ListSequence, Set)
{
    LinkedList<int> list = LinkedList<int>(array_1, 5);
    ListSequence<int> seq = ListSequence<int>(&list);
    seq.Set(1, 11);
    ASSERT_EQ(11, seq.Get(1));
}

TEST(DirectedGraph, Add_Edge_Vertex)
{
    graph->AddVertex('A');
    graph->AddVertex('B');
    graph->AddEdge('B', 'C', 1);
    ASSERT_EQ(0,graph->containsVertex('A'));
    ASSERT_EQ(1,graph->containsVertex('B'));
    ASSERT_EQ(2,graph->containsVertex('C'));
    ASSERT_EQ(3, graph->ReturnVertexNumber());
    ASSERT_EQ(1, graph->ReturnEdgeNumber());

}

TEST(DirectedGraph, Delete_Edge_Vertex)
{
    graph -> DeleteVertex('A');
    graph -> DeleteEdge('B', 'C');

    ASSERT_EQ(2, graph->ReturnVertexNumber());
    ASSERT_EQ(0, graph->ReturnEdgeNumber());
}

TEST(DirectedGraph, ADJMatrix)
{
    graph->DeleteVertex('B');
    graph->DeleteVertex('C');
    graph->AddEdge('A', 'B', 1);
    graph->AddEdge('A', 'C', 4);
    graph->AddEdge('B', 'C', 2);

    CommonMatrix<int>* matrix = graph->AdjMatrix();

    ASSERT_EQ(0, matrix->GetElement(0,0));
    ASSERT_EQ(0, matrix->GetElement(1,1));
    ASSERT_EQ(0, matrix->GetElement(2,2));
    ASSERT_EQ(1, matrix->GetElement(0,1));
    ASSERT_EQ(4, matrix->GetElement(0,2));
    ASSERT_EQ(10000, matrix->GetElement(1,0));
    ASSERT_EQ(2, matrix->GetElement(1,2));
    ASSERT_EQ(10000, matrix->GetElement(2,0));
    ASSERT_EQ(10000, matrix->GetElement(2,1));

}

TEST(DirectedGraph, Dijkstra)
{
    int weight = 0;
    int count = 0;
    graph->AddEdge('C', 'E', 1);
    graph->AddEdge('C', 'D', 5);
    graph->AddEdge('E', 'D', 3);
    graph->AddEdge('C', 'G', 10);
    graph->AddEdge('D', 'G', 10);
    graph->AddEdge('G', 'A', 1);
    ArraySequence<int>* Path = Dijkstra('A', 'G', graph, compareT1);
    for(int i = 0; i < Path->GetSize()-1; i += 1)
    {
        weight += graph->ReturnEdges()->Get(graph->containsEdge(graph->ReturnVertexes()->Get(Path->Get(i))->ReturnName(),
                                                                graph->ReturnVertexes()->Get(Path->Get(i + 1)) -> ReturnName())) -> ReturnWeight();

        count += 1;
    }
    ASSERT_EQ(3, count);
    ASSERT_EQ(13, weight);
}

TEST(DirectedGraph, TopologicalSort)
{
    graph->DeleteEdge('B', 'C');
    graph->TopologicalSort();

    ASSERT_EQ('A', graph->ReturnVertexes()->Get(0)->ReturnName());
    ASSERT_EQ('C', graph->ReturnVertexes()->Get(1)->ReturnName());
    ASSERT_EQ('E', graph->ReturnVertexes()->Get(2)->ReturnName());
    ASSERT_EQ('D', graph->ReturnVertexes()->Get(3)->ReturnName());
    ASSERT_EQ('G', graph->ReturnVertexes()->Get(4)->ReturnName());
    ASSERT_EQ('B', graph->ReturnVertexes()->Get(5)->ReturnName());

}


TEST(UndirectedGraph, Add_Edge_Vertex)
{

    graph1->AddVertex('A');
    graph1->AddVertex('B');
    graph1->AddEdge('B', 'C', 1);
    ASSERT_EQ(0,graph1->containsVertex('A'));
    ASSERT_EQ(1,graph1->containsVertex('B'));
    ASSERT_EQ(2,graph1->containsVertex('C'));
    ASSERT_EQ(3, graph1->ReturnVertexNumber());
    ASSERT_EQ(2, graph1->ReturnEdgeNumber());

}

TEST(UndirectedGraph, Delete_Edge_Vertex)
{
    graph1 -> DeleteVertex('A');
    graph1 -> DeleteEdge('B', 'C');

    ASSERT_EQ(-1,graph1->containsVertex('A'));
    ASSERT_EQ(0,graph1->containsVertex('B'));
    ASSERT_EQ(1,graph1->containsVertex('C'));
    ASSERT_EQ(2, graph1->ReturnVertexNumber());
    ASSERT_EQ(0, graph1->ReturnEdgeNumber());
}

TEST(UndirectedGraph, ADJMatrix)
{
    graph1->DeleteVertex('B');
    graph1->DeleteVertex('C');
    graph1->AddEdge('A', 'B', 1);
    graph1->AddEdge('A', 'C', 4);
    graph1->AddEdge('B', 'C', 2);

    CommonMatrix<int>* matrix1 = graph1->AdjMatrix();
    ASSERT_EQ(0, matrix1->GetElement(0,0));
    ASSERT_EQ(0, matrix1->GetElement(1,1));
    ASSERT_EQ(0, matrix1->GetElement(2,2));
    ASSERT_EQ(1, matrix1->GetElement(0,1));
    ASSERT_EQ(4, matrix1->GetElement(0,2));
    ASSERT_EQ(1, matrix1->GetElement(1,0));
    ASSERT_EQ(2, matrix1->GetElement(1,2));
    ASSERT_EQ(4, matrix1->GetElement(2,0));
    ASSERT_EQ(2, matrix1->GetElement(2,1));
}

TEST(UndirectedGraph, Dijkstra)
{
    int weight = 0;
    int count = 0;
    graph1->AddEdge('C', 'E', 1);
    graph1->AddEdge('C', 'D', 5);
    graph1->AddEdge('E', 'D', 3);
    graph1->AddEdge('C', 'G', 10);
    graph1->AddEdge('D', 'G', 10);
    graph1->AddEdge('G', 'A', 1);
    ArraySequence<int>* Path = Dijkstra('A', 'G', graph1, compareT1);
    for(int i = 0; i < Path->GetSize()-1; i += 1)
    {
        weight += graph->ReturnEdges()->Get(graph->containsEdge(graph->ReturnVertexes()->Get(Path->Get(i))->ReturnName(),
                                                                graph->ReturnVertexes()->Get(Path->Get(i + 1)) -> ReturnName())) -> ReturnWeight();

        count += 1;
    }
    ASSERT_EQ(1, count);
    ASSERT_EQ(1, weight);
}

TEST(UndirectedGraph, Coloring)
{
    ArraySequence<int> Colors = Coloring(graph1, compareT1);

    ASSERT_EQ(0,graph1->containsVertex('C'));
    ASSERT_EQ(1, graph1->containsVertex('A'));
    ASSERT_EQ(2, graph1->containsVertex('D'));
    ASSERT_EQ(3,graph1->containsVertex('G'));
    ASSERT_EQ(4, graph1->containsVertex('B'));
    ASSERT_EQ(5, graph1->containsVertex('E'));
    ASSERT_EQ(1, Colors.Get(0));
    ASSERT_EQ(2,Colors.Get(1));
    ASSERT_EQ(2,Colors.Get(2));
    ASSERT_EQ(3,Colors.Get(3));
    ASSERT_EQ(3,Colors.Get(4));
    ASSERT_EQ(3,Colors.Get(5));

}