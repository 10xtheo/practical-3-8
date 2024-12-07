#ifndef SI_H
#define SI_H

#include "function.h"
#include "array.h"

template <class number>
class TFsi: public TFunction<number>
{
    TArray<number>* d;
    TArray<number>* c(unsigned int n)
    {
        d = new TArray<number>;
        d->flushMemory();
        for (int i=0;i<(int)n+1;i++) {
            switch (i % 4)
            {
            case 0:
            {
                number el = number(1)/(number(i)+number(1));
                d->appendElement(el);
                break;
            }
            case 2:
            {
                number el = number(-1)/(number(i)+number(1));
                d->appendElement(el);
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
    TFsi(unsigned int n) : TFunction<number>(n, c(n)) {}
    ~TFsi() {
        d->flushMemory();
        delete d;
    }
};


#endif // SI_H
