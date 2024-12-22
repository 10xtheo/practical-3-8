#include "interface.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QRadioButton>
#include <QApplication>
#include <QtDebug>
#include "function.h"
#include "complex.h"
#include "sin.h"
#include "si.h"


TInterface::TInterface(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void TInterface::setupUI()
{
    setWindowTitle("Вычисление функций");
    setMaximumSize(600, 300);
    setMinimumSize(300, 200);

    mainLayout = new QVBoxLayout(this);

    // Горизонтальный макет для поля ввода x
    QHBoxLayout *xLayout = new QHBoxLayout();
    QLabel *xLabel = new QLabel("x =", this);
    inputField = new QLineEdit(this);
    inputField->setPlaceholderText("Введите x");

    xLayout->addWidget(xLabel);
    xLayout->addWidget(inputField);
    mainLayout->addLayout(xLayout);

    // Горизонтальный макет для поля ввода точности
    QHBoxLayout *precisionLayout = new QHBoxLayout();
    QLabel *precisionLabel = new QLabel("Точность:", this);
    precisionField = new QLineEdit(this);
    precisionField->setPlaceholderText("Введите точность (от 1 до 100)");

    // Небольшой валидатор для поля точности
    connect(precisionField, &QLineEdit::textChanged, this, [this](const QString& text) {
        if (text.isEmpty()) return;

        bool ok;
        int value = text.toInt(&ok);

        if (!ok || value < 0 || value > 100) {
            precisionField->clear();
            return;
        }
    });

    precisionLayout->addWidget(precisionLabel);
    precisionLayout->addWidget(precisionField);
    mainLayout->addLayout(precisionLayout);

    // Create radio buttons for number type selection
    QHBoxLayout *radioLayout = new QHBoxLayout();
    complexRadioButton = new QRadioButton("Компл", this);
    realRadioButton = new QRadioButton("Вещ", this);
    realRadioButton->setChecked(true); // Set real as default
    radioLayout->addWidget(complexRadioButton);
    radioLayout->addWidget(realRadioButton);
    mainLayout->addLayout(radioLayout);

    // Кнопка "Вычислить sin(x)"
    calculateSinButton = new QPushButton("Вычислить sin(x)", this);
    connect(calculateSinButton, &QPushButton::clicked, this, &TInterface::calculateSin);
    mainLayout->addWidget(calculateSinButton);

    // Кнопка "Вычислить Si(x)"
    calculateSiButton = new QPushButton("Вычислить Si(x)", this);
    connect(calculateSiButton, &QPushButton::clicked, this, &TInterface::calculateSi);
    mainLayout->addWidget(calculateSiButton);

    // Поле вывода результата
    outputField = new QLineEdit(this);
    outputField->setReadOnly(true);
    outputField->setPlaceholderText("Результат будет здесь...");
    mainLayout->addWidget(outputField);

    // Поле для ряда Маклорена
    maclaurinSeriesField = new QLineEdit(this); // Создаем новое поле
    maclaurinSeriesField->setReadOnly(true); // Устанавливаем readonly
    maclaurinSeriesField->setPlaceholderText("Ряд Маклорена"); // Устанавливаем плейсхолдер
    mainLayout->addWidget(maclaurinSeriesField); // Добавляем в layout

    // Кнопка "Очистить"
    clearButton = new QPushButton("Очистить", this);
    connect(clearButton, &QPushButton::clicked, this, &TInterface::clearOutput);
    mainLayout->addWidget(clearButton);

    // Кнопка "Выход"
    exitButton = new QPushButton("Выход", this);
    connect(exitButton, &QPushButton::clicked, this, &TInterface::exitApplication);
    mainLayout->addWidget(exitButton);

    setLayout(mainLayout);
}

TInterface::~TInterface()
{
    delete outputField; // Поле вывода результата
    delete xLabel; // Метка x
    delete inputField; // Поле ввода x
    delete xLayout; // Макет ввода x
    delete precisionLabel; // Метка точности
    delete precisionField; // Поле ввода точности
    delete precisionLayout; // Макет ввода точности
    delete clearButton; // Кнопка очистки
    delete calculateSinButton; // Кнопка вычисления sin(x)
    delete calculateSiButton; // Кнопка вычисления Si(x)
    delete exitButton; // Кнопка выхода
    delete mainLayout; // Основной макет

}

void TInterface::calculateSin()
{
    bool okPrecision;
    TComplex x;

    if (complexRadioButton->isChecked())
    {
        QString cnum = inputField->text();
        cnum >> x;
    }
    else
    {
        double realX = inputField->text().toDouble(&okPrecision);
        if (okPrecision)
        {
            x = TComplex(realX, 0);
        }
        else
        {
            outputField->setText("Ошибка ввода!");
            maclaurinSeriesField->setText("Ошибка ввода!");
            return;
        }
    }

    const int precision = precisionField->text().toInt(&okPrecision);

    if (okPrecision && precision >= 1)
    {
        TFsin<TComplex> func(precision);
        TComplex result = func.value(x);
        QString resStr;

        if (complexRadioButton->isChecked()) resStr << result;
        else resStr.setNum(result.modulus());

        func.setPrintMode(EPrintModeCanonical);

        QString strX;
        if (complexRadioButton->isChecked()) strX << x;
        else strX = QString::number(x.modulus());

        outputField->setText("sin(" + strX + ") = " + resStr);

        QString mclaurianOutput;
        mclaurianOutput << func;
        maclaurinSeriesField->setText(mclaurianOutput);

        GraphWindow *graphWindow = new GraphWindow(this);
        graphWindow->setPrecision(precision);
        graphWindow->setFunctionType("sin");
        graphWindow->setInterval(-10, 10);
        graphWindow->show();
        return;
    }

    outputField->setText("Ошибка ввода!");
    maclaurinSeriesField->setText("Ошибка ввода!");

}

void TInterface::calculateSi()
{
    bool okPrecision;
    TComplex x;

    if (complexRadioButton->isChecked())
    {
        QString cnum = inputField->text();
        cnum >> x;

    }
    else
    {
        double realX = inputField->text().toDouble(&okPrecision);
        if (okPrecision)
        {
            x = TComplex(realX, 0);
        }
        else
        {
            outputField->setText("Ошибка ввода!");
            maclaurinSeriesField->setText("Ошибка ввода!");
            return;
        }
    }

    const int precision = precisionField->text().toInt(&okPrecision);
    if (okPrecision && precision >= 1)
    {
        TFsi<TComplex> func(precision);
        TComplex result = func.value(x);
        QString resStr;

        if (complexRadioButton->isChecked()) resStr << result;
        else resStr.setNum(result.modulus());

        func.setPrintMode(EPrintModeCanonical);

        QString strX;
        if (complexRadioButton->isChecked()) strX << x;
        else strX = QString::number(x.modulus());

        outputField->setText("Si(" + strX + ") = " + resStr);

        QString mclaurianOutput;
        mclaurianOutput << func;
        maclaurinSeriesField->setText(mclaurianOutput);


        GraphWindow *graphWindow = new GraphWindow(this);
        graphWindow->setPrecision(precision);
        graphWindow->setFunctionType("si");
        graphWindow->setInterval(-10, 10);
        graphWindow->show();
        return;
    }
    outputField->setText("Ошибка ввода!");
    maclaurinSeriesField->setText("Ошибка ввода!");
}

void TInterface::clearOutput()
{
    outputField->clear(); // Очистка поля вывода
    maclaurinSeriesField->clear();
}

void TInterface::exitApplication()
{
    QApplication::quit(); // Завершение приложения
}

