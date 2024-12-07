#include "application.h"

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
{
    mainInterface = new TInterface(); // Создаем экземпляр интерфейса
    mainInterface->show(); // Показываем интерфейс
}

Application::~Application()
{
    delete mainInterface; // Освобождаем память
}
