#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QWidget>
#include "interface.h" // Подключаем интерфейс

class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int &argc, char **argv);
    ~Application();

private:
    TInterface *mainInterface; // Указатель на основной интерфейс
};

#endif // APPLICATION_H
