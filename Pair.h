#ifndef NEWLABA_PAIR_H
#define NEWLABA_PAIR_H

template<class TElement, class TElement1>
class PairKE
{
private:
    TElement element;
    TElement1 element1;
public:
    PairKE() = default;

    PairKE(TElement element, TElement1 element1)
    {
        this->element = element;
        this->element1 = element1;
    }

    ~PairKE() = default;

    TElement GetElem() const
    {
        return this->element;
    }

    TElement1 GetElem1() const
    {
        return this->element1;
    }

    void SetElem(TElement elem)
    {
        this->element = elem;
    }

    void SetElem1(TElement elem1)
    {
        this->element1 = elem1;
    }



};

template <class TKey, class TElement>
std::ostream& operator<< (std::ostream &out, const PairKE<TKey, TElement> pair)
{
    return out << "<" << pair.GetKey() << ", " << pair.GetElem() << ">";
}

#endif
