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

time_t getNow(size_t taskNumber, const string &msg) {
    printf("Задача №%zu %s в: ", (taskNumber + 1), msg.c_str());
    std::time_t rightNow = time(nullptr);
    std::tm* local = localtime(&rightNow);
    cout << std::put_time(local, "%M:%S") << endl;

    return rightNow;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    vector<double> tasks;
    vector<string> commands = { "begin", "end", "status", "exit" };
    time_t current{0};

    while(true) {
        int index = selectFromList(commands);
        if (commands[index] == "begin") {
            if (current != 0) {
                double diff = std::difftime(getNow(tasks.size(), " остановлена"), current);
                tasks.emplace_back(diff);
            }

            current = getNow(tasks.size(), " началась");
        }
        else if (commands[index] == "end") {
            if (current == 0) {
                cout << "ОТЧЁТ: пока нет выполняющихся задач." << endl;
                continue;
            }
            else {
                std::time_t rightNow = getNow(tasks.size(), " остановлена");

                double diff = std::difftime(rightNow, current);
                tasks.emplace_back(diff);

                current = 0;
            }
        }
        else if (commands[index] == "status") {
            std::time_t rightNow = time(nullptr);
            if (current) {
                cout << "ОТЧЁТ: одна задача не закончена!" << endl;
                double diff = std::difftime(rightNow, current);
                cout << "Данная задача длится уже: " << diff << " сек. " << endl;
            }
            if (!tasks.empty()) {
                cout << "ОТЧЁТ: по списку ранее завершенных задач: " << endl;
                for (int i = 0; i < tasks.size(); ++i) {
                    cout << (i + 1) << " задача длилась: " << tasks[i] << " сек. " << endl;
                }
            }
            else {
                cout << "ОТЧЁТ: завершенных задач пока не было." << endl;
            }
        }
        else if (commands[index] == "exit") break;
    }

    cout << "Программа закончила работу. До новых встреч" << endl;
}
