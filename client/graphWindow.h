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
    void setPrecision(int p);
protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onPlotButtonClicked();
    void onResetPlotButtonClicked();

private:
    QString functionType;
    double xMin, xMax; // Интервал для x
    int precision; // Точность
    QLineEdit *xMinInput;
    QLineEdit *xMaxInput;
    QPushButton *plotButton;
    QPushButton *resetPlotButton;
    QLabel *functionLabel;
};


#endif // GRAPHWINDOW_H
