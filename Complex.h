
#ifndef COMPLEX_H
#define COMPLEX_H

#endif
#include <math.h>
#include <iomanip>

class complex {
private:
    float realPart;
    float imagPart;

public:

    complex(float realPart = float(), float imagPart = float()): realPart(realPart), imagPart(imagPart) {}

    float real() const {
        return this->realPart;
    }

    float imag() const {
        return this->imagPart;
    }

    complex operator+(float val) const {
        return complex(this->realPart + val, this->imagPart);
    }

    complex operator-(float val) const {
        return complex(this->realPart - val, this->imagPart);
    }

    complex operator+(const complex& val) const {
        return complex(this->realPart + val.realPart, this->imagPart + val.imagPart);
    }

    complex operator-(const complex& val) const {
        return complex(this->realPart - val.realPart, this->imagPart - val.imagPart);
    }

    void operator+=(const complex& val) {
        this->realPart += val.real();
        this->imagPart += val.imag();
    }


    complex operator*(float val) const {
        return complex(this->realPart * val, this->imagPart * val);
    }

    //Multiplying on complex number
    complex operator*(complex val) const {
        return complex(this->real() * val.real() - this->imag() * val.imag(), this->real() * val.imag() + this->imag() * val.real());
    }

    bool operator==(const complex& val) const {
        return this->realPart == val.real() && this->imagPart == val.imag();
    }

    bool operator>(complex val) {
        return this->sqrt_complex() > val.sqrt_complex();
    }

    bool operator<(complex val) {
        return this->sqrt_complex() < val.sqrt_complex();
    }

    bool operator>=(complex val) {
        return this->sqrt_complex() >= val.sqrt_complex();
    }

    bool operator<=(complex val) {
        return this->sqrt_complex() <= val.sqrt_complex();
    }

    bool operator!=(const complex& val) const {
        return !this->operator==(val);
    }

    float sqrt_complex()
    {
        float re = this->realPart;
        float im = this->imagPart;
        float result = ((re+im)*sqrt(re*re+im*im))/(abs(re) + abs(im));
        return result;
    }

    void print() const {

        cout<< this->realPart<<"+i("<<this->imagPart<<")"<<setw(9);
    }

};

