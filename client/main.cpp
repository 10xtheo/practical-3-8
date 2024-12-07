#include "application.h"

int main(int argc, char *argv[])
{
    Application app(argc, argv); // Создаем объект приложения
    return app.exec(); // Запускаем основной цикл событий
}
