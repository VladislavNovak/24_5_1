#include <windows.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;
using std::vector;

std::string getTrimmedString(std::string str, std::string const &whiteSpaces = " \r\n\t\v\f") {
    auto start = str.find_first_not_of(whiteSpaces);
    str.erase(0, start);
    auto end = str.find_last_not_of(whiteSpaces);
    str.erase(end + 1);

    return str;
}

template<typename T>
void outputListToStream(std::ostream &out, std::vector<T> const &list, const std::string &delim = ",") {
    for (const auto &item : list) out << item << (item != list[list.size() - 1] ? delim : "\n");
}

std::string getUserLineString(const std::string &msg) {
    while (true) {
        std::string userLineString;
        printf("%s: ", msg.c_str());
        std::getline(std::cin, userLineString);

        userLineString = getTrimmedString(userLineString);
        if (userLineString.empty()) {
            std::cout << "Строка не может быть пустой. Попробуйте снова!" << std::endl;
            continue;
        }

        return userLineString;
    }
}

int selectFromList(std::vector<std::string> const &list) {
    bool isList = list.size() > 1;

    while (true) {
        cout << (isList ? "Выберите одну из опций: " : "Введите команду : ");
        outputListToStream(std::cout, list, (isList ? "|" : ""));

        auto userInput = getUserLineString("Наберите и нажмите enter");
        // return index from list, if word found
        for (int i = 0; i < list.size(); ++i) if (list[i] == userInput) return i;

        cout << "Неверно. Попробуйте снова!" << endl;
    }
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    // массив для хранения времени законченных задач

    vector<time_t> tasks;
    vector<string> commands = { "begin", "end", "status", "exit" };
    time_t current{0};

    // ---
    // меню с командами begin, end, status, exit

    while(true) {
        int index = selectFromList(commands);
        if (commands[index] == "begin") {
            // для первой инициализации или если ранее отработала команда end
            if (current == 0) {
                cout << "Отчет: Новая задача началась" << endl;
                current = std::time(nullptr);
            }
            else {
                cout << "Отчет: Прежняя задача остановлена. Новая задача началась" << endl;
                tasks.emplace_back(current);
                current = std::time(nullptr);
            }
        }
        else if (commands[index] == "end") {
            if (current == 0) {
                cout << "Отчет: Пока нет выполняющихся задач" << endl;
                continue;
            }
            else {
                cout << "Отчет: Задача окончена" << endl;
                tasks.emplace_back(current);
                current = 0;
            }
        }
        else if (commands[index] == "status") {
            if (current) {
                cout << "Отчет: Текущая задача:" << endl;
                std::tm* local = std::localtime(&current);
                // Здесь нужно будет получить текущее время и вычесть
                // типа std::difftime(local, std::time(nullptr))
                cout << asctime(local) << endl;
            }
            if (!tasks.empty()) {
                cout << "Отчет: Список задач:" << endl;
                for (int i = 0; i < tasks.size(); ++i) {
                    std::tm* local = std::localtime(&tasks[i]);
                    cout << asctime(local) << endl;
                }
            }
            else {
                cout << "Отчет: Задач пока не было" << endl;
            }
        }
        else if (commands[index] == "exit") break;
    }

    cout << "Программа закончила работу. До новых встреч" << endl;
}
