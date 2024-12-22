#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QPainter>
#include <QLabel>


class GraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    GraphWindow(QWidget *parent = nullptr);
    void setFunctionType(const QString &type);
    void setInterval(double xMin, double xMax);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onPlotButtonClicked();

private:
    QString functionType; // Type of function to plot (e.g., "sin" or "si")
    double xMin, xMax;    // Interval for x-axis
    QLineEdit *xMinInput;
    QLineEdit *xMaxInput;
    QPushButton *plotButton;
    QLabel *functionLabel; // Label to display the function type
};


#endif // GRAPHWINDOW_H
