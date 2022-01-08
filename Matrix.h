#ifndef MATRIX_H
#define MATRIX_H

#endif

#include <strings.h>
#include <stdexcept>
#include <cmath>
#include "ArraySequence.h"
#include "DynamicArray.h"

const string INVALID_ARGUMENT = "Invalid argument";
const string DIFFERENT_DIMS = "Impossible to make this operation: Matrices have different dimensions";

template <typename T>
class CommonMatrix {
protected:
    Sequence<T>** rows;
    int dimension;
public:

    CommonMatrix() :dimension(0)
    {
        rows=0;
    }

    CommonMatrix(int size) :dimension(size)
    {
        rows =(Sequence<T>**) new ArraySequence<T>*[size];
        for (int i =0; i<size; i++) {
            rows[i] = new ArraySequence<T>(size);
        }
        for (int i = 0; i<size; i++) {
            for (int j=0; j<size; j++) {
                this->SetElement(i,j,0);
            }
        }
    }

    CommonMatrix(const CommonMatrix<T>& matrix)
    {
        this->dimension=matrix.dimension;
        this->rows=matrix.rows;
    }

    CommonMatrix(ArraySequence<T> sequence, int size, string str) : CommonMatrix(size)
    {
        if (str == "common")
        {
            int count = 0;
            for (int i = 0; i<size; i++)
            {
                for (int j=0; j<size; j++)
                {
                    this->SetElement(i,j, sequence[count]);
                    count++;
                }
            }
        }
        this->dimension=size;
    }

    int GetDim()
    {
        return this->dimension;
    }

    Sequence<T>* GetRow(int index)
    {
        if (index<0 || index>=this->dimension)
        {
            throw out_of_range(INDEX_OUT_OF_RANGE);
        }
        return rows[index];
    }



    T GetElement(int row, int col)
    {
        if (row<0 || col<0 || col>=dimension || row>=dimension) {throw out_of_range(INDEX_OUT_OF_RANGE);}
        return this->GetRow(row)->Get(col);
    }


    void SetElement(int row, int col, T item)
    {
        if (row<0 || col<0 || col>=dimension || row>=dimension) {throw out_of_range(INDEX_OUT_OF_RANGE);}
        Sequence<T>* temp = this->GetRow(row);
        temp->Set(col, item);
        rows[row] = temp;

    }

    void Sw_row(int first, int second, int size)
    {
        if (first<0 || second<0 || first==second) {throw out_of_range(INDEX_OUT_OF_RANGE);}
        for (int i = 0; i < size; i++)
        {
            T item1 = this->GetElement(first, i);
            T item2 = this->GetElement(second, i);
            this->SetElement(first, i, item2);
            this->SetElement(second, i, item1);
        }
    }

    void Sw_col(int first, int second, int size)
    {
        if (first<0 || second<0 || first==second) {throw out_of_range(INDEX_OUT_OF_RANGE);}
        for (int i = 0; i < size; i++)
        {
            T item1 = this->GetElement(i, first);
            T item2 = this->GetElement(i, second);
            this->SetElement(i, first, item2);
            this->SetElement(i, second, item1);
        }
    }

    void Multiply_row(T scalar, int row, int size)
    {
        if (row<0) {throw out_of_range(INDEX_OUT_OF_RANGE);}
        for (int i = 0; i < size; i++)
        {
            T item = this->GetElement(row, i) * scalar;
            this->SetElement(row, i, item);
        }
    }

    void Multiply_col(T factor, int col, int size) {
        if (col<0) {throw out_of_range(INDEX_OUT_OF_RANGE);}
        for (int i = 0; i < size; i++) {
            T item = this->GetElement(i, col) * factor;
            this->SetElement(i, col, item);
        }
    }

    void Sum_row(int row1, int row2, int size)
    {
        if (row1<0 || row2<0 || row1==row2) {throw out_of_range(INDEX_OUT_OF_RANGE);}
        for (int i = 0; i < size; i++)
        {
            T item1 = this->GetElement(row1, i);
            T item2 = this->GetElement(row2, i);
            this->SetElement(row1, i, item1 + item2);
        }
    }

    void Sum_col(int col1, int col2, int size)
    {
        if (col1<0 || col2<0 || col1==col2) {throw out_of_range(INDEX_OUT_OF_RANGE);}
        for (int i = 0; i < size; i++)
        {
            T item1 = this->GetElement(i, col1);
            T item2 = this->GetElement(i, col2);
            this->SetElement(i, col1, item1 + item2);
        }
    }

    //matrixR = matrixA + matrixB
    CommonMatrix<T> operator+(CommonMatrix<T>& matrix)
    {
        if (this->dimension != matrix.dimension)
        {
            throw logic_error(DIFFERENT_DIMS);
        }
        CommonMatrix<T> matrixR = CommonMatrix<T>(matrix.dimension);

        for(int i = 0; i<matrix.dimension; i++)
        {
            for(int j = 0; j<matrix.dimension; j++)
            {
                T item = this->GetElement(i, j)+matrix.GetElement(i, j);
                matrixR.SetElement(i, j, item);
            }
        }
        return matrixR;
    }

    //matrixR = matrixA - matrixB
    CommonMatrix<T> operator-(CommonMatrix<T>& matrix)
    {
        if (this->dimension != matrix.dimension)
        {
            throw logic_error(DIFFERENT_DIMS);
        }
        CommonMatrix<T> matrixR = CommonMatrix<T>(matrix.dimension);

        for(int i = 0; i<matrix.dimension; i++)
        {
            for(int j = 0; j<matrix.dimension; j++)
            {
                T item = this->GetElement(i, j) - matrix.GetElement(i, j);
                matrixR.SetElement(i, j, item);
            }
        }
        return matrixR;
    }

    bool operator==(CommonMatrix<T>& matrix)
    {
        if (this->dimension != matrix.dimension)
        {
            throw logic_error(DIFFERENT_DIMS);
        }
        for(int i = 0;i < matrix.dimension;i++)
        {
            for(int j = 0;j < matrix.dimension;j++)
            {
                if(this->GetElement(i, j) != matrix.GetElement(i, j))
                {
                    return false;
                }
            }
        }
        return true;
    }

    // matrixC = maatrixA * factor
    template<typename U>
    CommonMatrix<T> operator*(U factor)
    {
        CommonMatrix<T> matrixR = CommonMatrix<T>(this->dimension);
        for(int i = 0; i<this->dimension; i++)
        {
            for(int j = 0; j<this->dimension; j++)
            {
                T item =((this->GetElement(i, j))*factor);
                matrixR.SetElement(i, j, item);
            }
        }
        return (matrixR);
    }


    //Matrix norm

    template<typename U>
    U MatrixNorm()
    {
        U Sum =U();
        for(int i = 0; i<this->dimension; i++)
        {
            for(int j = 0; j<this->dimension; j++)
            {
                Sum = Sum + ((this->GetElement(i, j)) * (this->GetElement(i, j)));
            }
        }
        return (U)(sqrt(Sum));
    }

    Sequence<T>* operator[](const int index)
    {
       return this->GetRow(index);
    }

    ~CommonMatrix(){};


};
