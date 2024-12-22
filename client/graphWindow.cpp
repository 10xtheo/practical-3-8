#include "graphWindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <cmath>

GraphWindow::GraphWindow(QWidget *parent) : QMainWindow(parent), xMin(0), xMax(1)
{
    // Create central widget and layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Create a label for the function type
    functionLabel = new QLabel("Function: ", this);
    layout->addWidget(functionLabel);

    // Create input fields for interval
    xMinInput = new QLineEdit(this);
    xMaxInput = new QLineEdit(this);
    xMinInput->setPlaceholderText("Enter minimum x value");
    xMaxInput->setPlaceholderText("Enter maximum x value");

    // Create a button to plot the function
    plotButton = new QPushButton("Plot Function", this);
    connect(plotButton, &QPushButton::clicked, this, &GraphWindow::onPlotButtonClicked);

    // Add widgets to the layout
    layout->addWidget(xMinInput);
    layout->addWidget(xMaxInput);
    layout->addWidget(plotButton);

    setCentralWidget(centralWidget);
    setWindowTitle("Graph Plotter");
    resize(800, 600); // Set a reasonable default size
}

void GraphWindow::setFunctionType(const QString &type)
{
    functionType = type; // Store the function type
    functionLabel->setText("Function: " + functionType); // Update the label
}

void GraphWindow::setInterval(double min, double max)
{
    xMin = min;
    xMax = max;
    update(); // Trigger a repaint
}

void GraphWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw axes
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(50, height() / 2, width() - 50, height() / 2); // X-axis
    painter.drawLine(width() / 2, 50, width() / 2, height() - 50); // Y-axis

    // Draw the function
    painter.setPen(QPen(Qt::blue, 2));
    const int numPoints = 100;
    QVector<QPointF> points(numPoints);

    for (int i = 0; i < numPoints; ++i)
    {
        double x = xMin + (xMax - xMin) * i / (numPoints - 1);
        double y = 0;

        if (functionType == "sin")
        {
            y = sin(x);
        }
        else if (functionType == "si")
        {
            // Implement the Si function here
            // y = /* Your Si function implementation */;
        }

        // Map the function value to the widget's coordinate system
        double mappedX = (x - xMin) / (xMax - xMin) * (width() - 100) + 50;
        double mappedY = height() / 2 - (y * 50); // Scale the y value
        points[i] = QPointF(mappedX, mappedY);
    }

    // Draw the function line
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

    // Set the interval for the graph
    setInterval(minX, maxX);
    setFunctionType("sin"); // Example: setting the function type to "sin"
    update(); // Trigger a repaint to show the updated graph
}
