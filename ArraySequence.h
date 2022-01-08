#pragma once

#include "Sequence.h"
#include "DynamicArray.h"

template<typename T>
class ArraySequence : public Sequence<T>
{
private:
    DynamicArray<T>* dynamic_array;

public:

    ArraySequence()
    {
        this->dynamic_array = new DynamicArray<T>();
    };
    ArraySequence(int size)
    {
        this->dynamic_array = new DynamicArray<T>(size);
    };
    ArraySequence(T* data, int size)
    {
        this->dynamic_array =new DynamicArray<T>(data, size);
    };
    ArraySequence(DynamicArray<T>* arr)
    {
        this->dynamic_array =arr;
    };
    ArraySequence(const ArraySequence<T> & array)
    {
        this->dynamic_array = new DynamicArray<T>(*array.dynamic_array);
    };


    T GetFirst() const override
    {
        if (this->GetSize()==0)
        {
            throw out_of_range(INDEX_OUT_OF_RANGE);
        }
        return dynamic_array->Get(0);
    };

    T GetLast() const override
    {
        if (this->GetSize()==0)
        {
            throw out_of_range(INDEX_OUT_OF_RANGE);
        }
        return dynamic_array->Get(dynamic_array->GetSize()-1);
    };

    T Get(int index) const override
    {
        if (index<0 || index>=this->GetSize())
        {
            throw out_of_range(INDEX_OUT_OF_RANGE);
        }
        return dynamic_array->Get(index);
    };
    ArraySequence<T>* GetSubSequence(int start, int end) override
    {
        if (start<0 || start>=this->GetSize() + 1 || end<0 || end >=this->GetSize() + 1 || end<start)
        {
            throw out_of_range(INDEX_OUT_OF_RANGE);
        }
        int SubSIze = end - start;
        ArraySequence<T>* newArray = new ArraySequence<T>(SubSIze);
        for (int i=0; i < SubSIze; i++)
        {
            newArray->dynamic_array->Set(i, this->dynamic_array->Get(i + start));
        }
        return newArray;
    }

    int GetSize() const override
    {
        return dynamic_array->GetSize();
    };


    void Set(int index, T item) override
    {
        if (index<0 || index >=this->dynamic_array->GetSize())
        {
            throw out_of_range(INDEX_OUT_OF_RANGE);
        }
        return this->dynamic_array->Set(index, item);
    };

    void Append(T item) override
    {
        DynamicArray<T>* newarr = new DynamicArray<T>(this->GetSize()+1);
        newarr->Set(this->GetSize(), item);
        for (int i=0; i<this->GetSize(); i++)
        {
            newarr->Set(i, this->Get(i));
        }
        this->dynamic_array=newarr;
    };

    void Prepend(T item) override
    {
        DynamicArray<T>* newdynarr = new DynamicArray<T>(this->GetSize()+1);
        newdynarr->Set(0, item);
        for (int i=0; i<this->GetSize(); i++)
        {
            newdynarr->Set(i+1, this->Get(i));
        }
        this->dynamic_array=newdynarr;
    };

    void RemoveAt(int index) override
    {
        if (index < 0 || index >= this->GetSize())
        {
            throw out_of_range(INDEX_OUT_OF_RANGE);
        }
        DynamicArray<T>* temp;
        temp = new DynamicArray<T>(this->GetSize() - 1);
        for (int i = 0; i < index; i++)
        {
            temp->Set(i, this->dynamic_array->Get(i));
        }
        for (int i = index + 1; i < this->GetSize(); i++)
        {
            temp->Set(i, this->dynamic_array->Get(i));
        }
        delete this->dynamic_array;
        this->dynamic_array = temp;
        delete temp;
    };

    bool Contains(T item) override
    {
        for (int i = 0; i < this->GetSize(); i++)
        {
            if (this->Get(i) == item)
            {
                return true;
            }
        }
        return false;
    };


    void InsertAt(T item, int index) override
    {
        if (index<0)
        {
            throw out_of_range(INDEX_OUT_OF_RANGE);
        }
        if (index == this->GetSize() + 1)
        {
            this->Append(item);
            return;
        }
        int newSize = this->GetSize()+1;
        DynamicArray<T>* newdynarr = new DynamicArray<T>(newSize);
        int j=0;
        for (int i = 0; i<newSize; ++i)
        {
            if (i == index)
            {
                newdynarr->Set(i, item);
                continue;
            }
            newdynarr->Set(i, this->Get(j));
            j++;
        }
        dynamic_array = newdynarr;
    };

    ArraySequence<T>* Concat(Sequence<T> *arr) override
    {
        ArraySequence<T>* newSequence=new ArraySequence<T>;
        for (int i = 0; i<this->GetSize(); i++)
        {
            newSequence->Append(this->Get(i));
        }
        for (int i=0;i<arr->GetSize();i++)
        {
            newSequence->Append(arr->Get(i));
        }
        return newSequence;
    };


    ~ArraySequence() = default;

};