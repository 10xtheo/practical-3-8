#include "graphWindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <cmath>
#include "si.h"
#include "sin.h"
#include "complex.h"


GraphWindow::GraphWindow(QWidget *parent) : QMainWindow(parent), xMin(0), xMax(1)
{
    // layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // label
    functionLabel = new QLabel("Function: ", this);
    layout->addWidget(functionLabel);

    // interval
    xMinInput = new QLineEdit(this);
    xMaxInput = new QLineEdit(this);
    xMinInput->setPlaceholderText("Enter minimum x value");
    xMaxInput->setPlaceholderText("Enter maximum x value");

    // button to plot
    plotButton = new QPushButton("Plot Function", this);
    connect(plotButton, &QPushButton::clicked, this, &GraphWindow::onPlotButtonClicked);

    // button to reset
    resetPlotButton = new QPushButton("Reset plot", this);
    connect(resetPlotButton, &QPushButton::clicked, this, &GraphWindow::onResetPlotButtonClicked);

    layout->addWidget(xMinInput);
    layout->addWidget(xMaxInput);
    layout->addWidget(plotButton);
    layout->addWidget(resetPlotButton);

    setCentralWidget(centralWidget);
    setWindowTitle("Graph Plotter");
    resize(800, 600);
}

void GraphWindow::setFunctionType(const QString &type)
{
    functionType = type;
    functionLabel->setText("Function: " + functionType + "\nPrecision: " + QString::number(precision));
}

void GraphWindow::setInterval(double min, double max)
{
    xMin = min;
    xMax = max;
    update();
}

void GraphWindow::setPrecision(int p) {
    this->precision = p;
}

void GraphWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // axes
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(50, height() / 2, width() - 50, height() / 2); // X-axis
    painter.drawLine(width() / 2, 50, width() / 2, height() - 50); // Y-axis

    // function
    painter.setPen(QPen(Qt::blue, 2));
    const int numPoints = 100;
    QVector<QPointF> points(numPoints);

    if (functionType == "sin")
    {
        TFsin<TComplex> localSin(precision);

        for (int i = 0; i < numPoints; ++i)
        {
            double x = xMin + (xMax - xMin) * i / (numPoints - 1);
            TComplex localX(x);
            double y = 0;


            double mappedX = (x - xMin) / (xMax - xMin) * (width() - 100) + 50;
            TComplex rawY = TComplex(height()) / TComplex(2) - (localSin.value(localX) * TComplex(50));
            double mappedY = rawY.getReal();
            points[i] = QPointF(mappedX, mappedY);
        }

    }
    else if (functionType == "si")
    {
        TFsi<TComplex> localSi(precision);

        for (int i = 0; i < numPoints; ++i)
        {
            double x = xMin + (xMax - xMin) * i / (numPoints - 1);
            TComplex localX(x);
            double y = 0;


            double mappedX = (x - xMin) / (xMax - xMin) * (width() - 100) + 50;
            TComplex rawY = TComplex(height()) / TComplex(2) - (localSi.value(localX) * TComplex(50));
            double mappedY = rawY.getReal();
            points[i] = QPointF(mappedX, mappedY);
        }
    }

    painter.drawPolyline(points.data(), points.size());
}

void GraphWindow::onPlotButtonClicked()
{
    bool okMin, okMax;
    double minX = xMinInput->text().toDouble(&okMin);
    double maxX = xMaxInput->text().toDouble(&okMax);

    if (!okMin || !okMax || minX >= maxX)
    {
        QMessageBox::warning(this, "Input Error", "Please enter valid x values.");
        return;
    }

    setInterval(minX, maxX);
    // setFunctionType("sin");
    update();
}

void GraphWindow::onResetPlotButtonClicked()
{
    double minX = -10;
    double maxX = 10;

    setInterval(minX, maxX);
    // setFunctionType("sin");
    update();
}
