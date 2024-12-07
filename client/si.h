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

    QString mcLoren()
    {
        QString result = "P(x) = x";
        for (unsigned i = 1; i < this->arrCoef->getSize(); ++i)
        {
            if (this->arrCoef->get(i) != 0)
            {
                // Получаем коэффициент и конвертируем его в QString
                QString coefStr;
                coefStr << this->arrCoef->get(i);
                QString sign = (coefStr[0] == '-' ? "-" : "+"); // Определяем знак

                result += " ";
                result += sign; // Добавляем знак перед коэффициентом
                result += " x";
                result += " ^";
                result += QString::number(i+1);
                result += "/";
                result += "(";
                result += QString::number(i+1);
                result += "*";
                result += QString::number(i+1);
                result += "!";
                result += ")";
            }
        }

        return result;
    }
};



#endif // SI_H
