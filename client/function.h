#ifndef FUNCTION_H
#define FUNCTION_H

#include "polynom.h"
#include "array.h"
#include "QDebug"

template <class number>
class TFunction : public TPolynom<number> {
private:
    number factorial(number n);
    number value(number val);
public:
    TFunction(int degree, TArray<number>& derivatives);
    TFunction(int degree, TArray<number>* derivatives);
    number getValue(number val);
    // ~TFunction();
};

template <class number>
number TFunction<number>::getValue(number val)
{
    return value(val);
}

template <class number>
TFunction<number>::TFunction(int degree, TArray<number>& derivatives) {
    this->arrCoef = new TArray<number>();
    this->arrRoot = new TArray<number>();

    for (int i = 0; i < degree; i++) {
        this->arrRoot->appendElement(number(0));
    }
    this->canonicCoef = number(1);

    QString bebra;

    qDebug() << derivatives.getSize() << " " << this->arrRoot->getSize() << " sizes\n";
    for (int i = 1; i <= degree; ++i) {
        number cefteme = derivatives.get(i-1) / factorial(number(i));

        bebra << cefteme;
        bebra += " ";
        this->addCoef(cefteme); // f^(i)(0) / i!
    }

    bebra << value(number(4));
    qDebug() << bebra << " resut\n";
}

template <class number>
TFunction<number>::TFunction(int degree, TArray<number>* derivatives) {
    this->arrCoef = new TArray<number>();
    this->arrRoot = new TArray<number>();

    for (int i = 0; i < degree; i++) {
        this->arrRoot->appendElement(number(0));
    }
    this->canonicCoef = number(1);

    QString bebra;

    qDebug() << derivatives->getSize() << " " << this->arrRoot->getSize() << " sizes\n";
    for (int i = 1; i <= degree; ++i) {
        number cefteme = derivatives->get(i-1) / factorial(number(i));

        bebra << cefteme;
        bebra += " ";
        this->addCoef(cefteme); // f^(i)(0) / i!
    }

    bebra << value(number(4));
    qDebug() << bebra << " resut\n";
}


// template <class number>
// TFunction<number>::~TFunction() {
//     qDebug() << "destr\n";
//     flushMemory();
// }

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
    QString bebra1;
    for (unsigned i = 0; i < this->arrCoef->getSize(); i++) {
        bebra1 << this->arrCoef->get(i);
        bebra1 += " ";
    }
    qDebug() << "arrCoef: " << bebra1;
    bebra1 = "";
    for (unsigned i = 0; i < this->arrRoot->getSize(); i++) {
        bebra1 << this->arrRoot->get(i);
        bebra1 += " ";
    }
    qDebug() << "arrRoot: " << bebra1;

    for (unsigned i = 1; i <= this->arrCoef->getSize(); i++) {
        QString b1;
        QString b2;
        b1 << this->arrCoef->get(i-1);
        b2 << pow(val, i);
        qDebug() << b1 << "*" << b2;
        result += this->arrCoef->get(i-1) * pow(val, i);
    }

    return result;
}

#endif // FUNCTION_H
