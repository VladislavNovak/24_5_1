#include <windows.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;
using std::vector;

int selectMenuItem(std::vector<std::string> const &list) {
    while (true) {
        cout << (list.size() > 1 ? "Выберите одну из опций: " : "Введите команду : ");
        for (const auto &item : list) cout << item << (item != list[list.size() - 1] ? "|" : "\n");

        while (true) {
            std::string userInput;
            std::cout << "Наберите и нажмите enter: ";
            std::getline(std::cin, userInput);

            for (int i = 0; i < list.size(); ++i)
                if (list[i] == userInput) return i;

            cout << "Неверно. Попробуйте снова!" << endl;
        }
    }
}

time_t getNow(size_t taskNumber, const string &msg) {
    printf("Задача №%zu %s в: ", (taskNumber + 1), msg.c_str());
    std::time_t rightNow = time(nullptr);
    std::tm* local = localtime(&rightNow);
    cout << std::put_time(local, "%H:%M:%S") << endl;

    return rightNow;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    vector<double> tasks;
    vector<string> commands = { "begin", "end", "status", "exit" };
    time_t current{0};

    while(true) {
        int index = selectMenuItem(commands);
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
