#ifndef FUNCTION_H
#define FUNCTION_H

#include "polynom.h"
#include "array.h"

template <class number>
class TFunction : public TPolynom<number> {
private:
    number factorial(number n);
public:
    TFunction(int degree, TArray<number>& derivatives);
    TFunction(int degree, TArray<number>* derivatives);
    number value(number val);
};

template <class number>
TFunction<number>::TFunction(int degree, TArray<number>& derivatives) {
    this->arrCoef = new TArray<number>();
    this->arrRoot = new TArray<number>();

    for (int i = 0; i < degree; i++) {
        this->arrRoot->appendElement(number(0));
    }
    this->canonicCoef = number(1);

    for (int i = 1; i <= degree; ++i) {
        number coef = derivatives.get(i-1) / factorial(number(i));

        this->addCoef(coef); // f^(i)(0) / i!
    }
}

template <class number>
TFunction<number>::TFunction(int degree, TArray<number>* derivatives) {
    this->arrCoef = new TArray<number>();
    this->arrRoot = new TArray<number>();

    for (int i = 0; i < degree; i++) {
        this->arrRoot->appendElement(number(0));
    }
    this->canonicCoef = number(1);


    for (int i = 1; i <= degree; ++i) {
        number coef = derivatives->get(i-1) / factorial(number(i));

        this->addCoef(coef); // f^(i)(0) / i!
    }
}


template <class number>
number TFunction<number>::factorial(number n) { // TODO: мб вынести отсюда
    number result = number(1);
    for (number i = number(2); i <= n; ++i) {
        result = result * i;
    }
    return result;
}

template <class number>
number TFunction<number>::value (number val) {
    number result = 0;

    for (unsigned i = 1; i <= this->arrCoef->getSize(); i++) {
        result += this->arrCoef->get(i-1) * pow(val, i);
    }

    return result;
}


#endif // FUNCTION_H
