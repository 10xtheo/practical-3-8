#ifndef FUNCTION_H
#define FUNCTION_H

#include "polynom.h"
#include "array.h"

template <class number>
class TFunction : public TPolynom<number> {
private:
    int factorial(int n);
public:
    TFunction(int degree, const TArray<number>& derivatives);
    ~TFunction();
};

template <class number>
TFunction<number>::TFunction(int degree, const TArray<number>& derivatives) {
    this->arrCoef->flushMemory();

    for (int i = 0; i <= degree; ++i) {
        this->addCoef(derivatives[i] / factorial(i)); // f^(i)(0) / i!
    }
}

template <class number>
int TFunction<number>::factorial(number n) { // TODO: мб вынести отсюда
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

#endif // FUNCTION_H
