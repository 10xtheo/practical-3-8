#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>

class TInterface : public QWidget
{
    Q_OBJECT

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

public slots:
    void clearOutput(); // Очистить поле вывода
    void calculateSin(); // Вычислить sin(x)
    void calculateSi(); // Вычислить Si(x)
    void exitApplication(); // Выйти

private:
    QLineEdit *outputField; // Поле вывода результата
    QLineEdit *inputField; // Поле ввода x
    QLineEdit *precisionField; // Поле ввода точности
    QPushButton *clearButton; // Кнопка очистки
    QPushButton *calculateSinButton; // Кнопка вычисления sin(x)
    QPushButton *calculateSiButton; // Кнопка вычисления Si(x)
    QPushButton *exitButton; // Кнопка выхода
    QVBoxLayout *mainLayout; // Основной макет

    void setupUI(); // Настройка пользовательского интерфейса
};

#endif // INTERFACE_H
