# Время

## <font color="tomato">Реализация программы учёта времени</font>

Используя функцию получения текущего времени `std::time`, реализуйте простейший менеджер учёта времени.

Пользователь взаимодействует с программой с помощью команд:

* Команда begin начинает отслеживание новой задачи. 
После ввода этой команды пользователь должен ввести название задачи, над которой он планирует сейчас работать. 
Если уже была начата какая-то другая задача, предыдущая должна быть автоматически завершена и начата новая.
* Команда end заканчивает отслеживание текущей задачи. Если текущей начатой задачи нет, то команда ничего не делает.
* Команда status выводит на экран информацию о всех законченных задачах и времени, которое было на них потрачено. 
Также выводится название текущей выполняемой задачи, если таковая имеется.
* Команда exit выходит из программы.

### <font color="tomato">Советы и рекомендации</font>

Тип std::time_t принимайте за секунды и с помощью него рассчитывайте время в часах, которое было затрачено.

## <font color="tomato">Примеры из лекций:</font>

```c++
#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
using std::cout;
using std::endl;
using std::vector;

void first_part() {
    // получить текущее время
    std::time_t result = std::time(nullptr);
    // преобразовать в структуру tm
    std::tm* local = std::localtime(&result);
    // обычный вывод
    cout << asctime(local) << endl;
    // возможно вывести время на дисплей по заданному формату
    cout << std::put_time(local, "%Y/%m/%d %H/%M/%S") << endl;
    std::tm* custom = std::localtime(&result);
    // можно в соответствии с переданным форматом ввести время в структуру
    std::cin >> std::get_time(custom, "%Y");
    cout << asctime(custom) << endl;
}

void second_part() {
    std::time_t a = std::time(nullptr);
    std::tm* localA = std::localtime(&a);
    cout << asctime(localA);
    int foo;
    std::cin >> foo;
    std::time_t b = std::time(nullptr);
    std::tm* localB = std::localtime(&b);
    cout << asctime(localB) << endl;

    auto diff = std::difftime(a, b);
    std::time_t c = b - (std::time_t)diff;
    std::time_t d = b + (std::time_t)diff;
    std::tm* localC = std::localtime(&c);
    std::tm* localD = std::localtime(&d);
    cout << asctime(localC) << endl;
    cout << asctime(localD) << endl;
}
```