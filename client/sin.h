#ifndef SIN_H
#define SIN_H

#include "function.h"
#include "array.h"

template <class number>
class TFsin: public TFunction<number>
{
    TArray<number>* d;
    TArray<number>* c(unsigned int n)
    {
        d = new TArray<number>;
        d->flushMemory();
        for (unsigned i=0;i<n+1;i++) {
            switch (i % 4)
            {
            case 0:
            {
                d->appendElement(number(1));
                break;
            }
            case 2:
            {
                d->appendElement(number(-1));
                break;
            }
            default:
            {
                d->appendElement(number(0));
                break;
            }
            }
        }

        return d;
    }

public:
    TFsin(unsigned int n) : TFunction<number>(n, c(n)) {}
    ~TFsin() {
        d->flushMemory();
        delete d;
    }
};


#endif // SIN_H
