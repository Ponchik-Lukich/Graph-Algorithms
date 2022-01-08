#ifndef LAB3_FUNCTION_H
#define LAB3_FUNCTION_H

template <class T>
int compareT1(T a, T b) {
    if (a < b)
    {
        return 0;
    }
    if (a > b)
    {
        return 1;
    }
    return 2;
}
#endif


//template <class Name, class Weight>
//        int BandwidthHelp(int start, int end, int weight, Graph<Name, Weight>* graph, bool *visited, CommonMatrix<Weight>* matrix, int (*cmp)(Name, Name))
//        {
//    for(int i = 0; i < graph->ReturnVertexNumber(); i++)
//    {
//        if (matrix->GetElement(start, i) == weight && start != i)
//        {
//            if (i == end)
//            {
//                return 1;
//            }
//            else
//            {
//                start = i;
//            }
//        }
//    }
//    return 0;
//        }
//
//        template <class Name, class Weight>
//                ArraySequence<int>* Bandwidth(Name first_one, int last_one, Graph<Name, Weight>* graph, int (*cmp)(Name, Name))
//                {
//    int start, end, result;
//    Weight temp;
//    start = graph->containsVertex(first_one);
//    end = graph->containsVertex(last_one);
//    ArraySequence<Weight>* weights = new ArraySequence<Weight>();
//    bool *visited = new bool[graph->ReturnVertexNumber()];
//    CommonMatrix<Weight>* matrix = graph->AdjMatrix();
//
//    for (int i = 0; i < graph->ReturnVertexNumber(); i++)
//    {
//        visited[i] = false;
//    }
//    for (int i = 0; i < graph->ReturnEdgeNumber(); i += 1)
//    {
//        weights->Append(graph->ReturnEdges()->Get(i)->ReturnWeight());
//    }
//    int size = weights->GetSize();
//    int d = size / 2;
//    while (d > 0)
//    {
//        for (int i = 0; i < size - d; i++)
//        {
//            int j = i;
//            while (j >= 0 && cmp(weights->Get(j) , weights->Get(j + d)) == 1)
//            {
//                temp = weights->Get(j);
//                weights->Set(j, weights->Get(j + d));
//                weights->Set(j + d, temp);
//                j--;
//            }
//        }
//        d = d / 2;
//    }
//    visited[start] = true;
//    for (int i = weights->GetSize()-1; i>=0; i--)
//    {
//        for (int j = 0; j < graph->ReturnVertexNumber(); j++)
//        {
//            if(cmp(matrix->GetElement(start, j), weights->Get(i)) == 2 && j != start)
//            {
//                result = BandwidthHelp(j, end, weights->Get(i), graph, visited, matrix, compareT1);
//            }
//        }
//    }
//
//    //        for (int i = weights->GetSize()-1; i >= 0; i--)
//    //        {
//    //            cout << weights->Get(i) << " ";
//    //        }
//    //        cout << endl;
//    return weights;
//
//                }