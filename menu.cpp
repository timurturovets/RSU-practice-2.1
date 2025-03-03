#include "task1.cpp"
#include "task2.cpp"

class menu {
public:
    static void start() {
        const int TASKS_LEN = 2;
        itask* tasks[TASKS_LEN] = {new task1(), new task2()};

        int choice;
        do {
            std::cout << "Choose task (1-11): ";
            std::cin >> choice;
        } while (choice < 0 || choice > TASKS_LEN);

        try {
            tasks[choice - 1]->run();
        } catch (...){
            std::cerr << "An error occurred while running your task: see above";
            return;
        }
    }
};