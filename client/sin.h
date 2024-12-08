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

    friend QString& operator<<(QString& result, TFsin<number>& tfsin)
    {
        result += "P(x) = x";
        for (unsigned i = 1; i < tfsin.arrCoef->getSize(); ++i)
        {
            if (tfsin.arrCoef->get(i) != 0)
            {
                // Получаем коэффициент и конвертируем его в QString
                QString coefStr;
                coefStr << tfsin.arrCoef->get(i);
                coefStr.replace("(", "");
                coefStr.replace(")", "");
                QString sign = (coefStr[0] == '-' ? "-" : "+"); // Определяем знак

                result += " ";
                result += sign; // Добавляем знак перед коэффициентом
                result += " x";
                result += " ^";
                result += QString::number(i+1);
                result += "/";
                result += QString::number(i+1);
                result += "!";
            }
        }

        return result;
    }
};


#endif // SIN_H
