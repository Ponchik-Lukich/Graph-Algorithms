#pragma once

#include "Sequence.h"
#include "ArraySequence.h"
#include <ctime>

using namespace std;

#ifndef LAB1_SORTS_H
#define LAB1_SORTS_H

#endif
namespace Sorts_algorithms
{
    const string INCORRECT_INDEX = "Impossible to make this operation: Incorrect number";


    template<class T>
    Sequence<T> *SelectionSort(Sequence<T> *seq, int (*cmp)(T, T))
    {
        int size = seq->GetSize();
        if (seq->GetSize() <= 1) {
            throw out_of_range(INCORRECT_INDEX);
        }
        T temp;
        int j;

        for (int i = 0; i < size ; i++)
        {
            j = i;
            for(int k = i; k < size; k++)
            {
                if(cmp(seq->Get(j) , seq->Get(k)) == 1)
                {
                    j = k;
                }
            }
            temp = seq->Get(i);
            seq->Set(i, seq->Get(j));
            seq->Set(j, temp);
        }
        return seq;
    }

    template<class T>
    void QuickSort_Support(Sequence<T> *seq, int left, int right, int (*cmp)(T, T))
    {
        int i = left;
        int j = right;
        T pivot_help = seq->Get(((left + right) / 2));
        T temp;


        while (i <= j) {
            while (cmp(seq->Get(i) , (pivot_help)) == 0) {
                i++;
            }
            while (cmp(seq->Get(j) , T (pivot_help)) == 1) {
                j--;
            }
            if (i <= j) {
                temp = seq->Get(i);
                seq->Set(i, seq->Get(j));
                seq->Set(j, temp);
                i++;
                j--;
            }

        }
        if (j > left) {
            QuickSort_Support(seq, left, j, cmp);
        }
        if (i < right) {
            QuickSort_Support(seq, i, right, cmp);
        }
    }

    template<class T>
    Sequence<T> *QuickSort(Sequence<T> *seq, int (*cmp)(T, T))
    {
        if (seq->GetSize() <= 1)
        {
            throw out_of_range(INCORRECT_INDEX);
        }
        int size = seq->GetSize();
        QuickSort_Support(seq, 0, size - 1, cmp);
        return seq;
    }

    template<class T>
    Sequence<T> *ShellSort(Sequence<T> *seq, int (*cmp)(T, T))
    {
        int size = seq->GetSize();
        int d = size / 2;
        T temp;
        while (d > 0) {
            for (int i = 0; i < size - d; i++) {
                int j = i;
                while (j >= 0 && cmp(seq->Get(j) , seq->Get(j + d)) == 1) {
                    temp = seq->Get(j);
                    seq->Set(j, seq->Get(j + d));
                    seq->Set(j + d, temp);
                    j--;
                }
            }
            d = d / 2;
        }
        return seq;
    }

}

template <class T>
bool IsCorrect(Sequence<T>* seq, int (*cmp)(T, T))
{
    int size = seq->GetSize();
    int i = 1;
    while ( i <= size - 1)
    {
        if (cmp(seq->Get(i) , seq->Get(i - 1)) == 1 || cmp(seq->Get(i) , seq->Get(i - 1)) == 2)
        {
            i++;
        }
        else
        {
            return false;
        }
    }
    return true;
}


template<class T>
        double Time(Sequence<T> *seq, Sequence<T> *(*sort)(Sequence<T> *seq, int (*cmp)(T, T)), int (*cmp)(T, T))
{
    clock_t startTime = clock();
    seq = sort(seq, cmp);
    clock_t endTime = clock();
    double time = (double) (endTime - startTime) / CLOCKS_PER_SEC;
    return time;
}
