/* Study Planner Engine: the main menu, calls the C modules and the Analysis class */
#include <iostream>
#include <string>
using namespace std;

#include "engine.h"
#include "task.h"
#include "priority_queue.h"
#include "merge_sort.h"
#include "circular_queue.h"
#include "stack.h"
#include "auth.h"
#include "storage.h"

bool StudyPlannerEngine::run() {
    int choice;
    bool loggedOut = false;
    do {
        cout << "\n--- Student Study Planner (" << currentUser << ") ---\n";
        cout << "1. Add task\n2. Edit task\n3. Delete task\n4. Show tasks (sorted by deadline)\n";
        cout << "5. Suggest next task\n6. Complete task\n7. Show completed tasks\n";
        cout << "8. Undo last completed\n9. Add revision topic\n10. Revise next topic\n";
        cout << "11. Overall performance\n12. Subject-wise performance\n13. Log out\n0. Exit\nChoice: ";
        cin >> choice;
        if (cin.eof())
            break;
        if (cin.fail()) {          // letters or symbols instead of a number
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
        }

        if (choice == 1) addTask();
        else if (choice == 2) editTask();
        else if (choice == 3) {
            int n = 0;
            showTasks();
            cout << "Task number to delete: ";
            cin >> n;
            if (n >= 1 && n <= taskCount) deleteTask(n - 1);
        }
        else if (choice == 4) {
            mergeSort(tasks, 0, taskCount - 1);
            showTasks();
        }
        else if (choice == 5) suggestNext();
        else if (choice == 6) completeTask();
        else if (choice == 7) showCompleted();
        else if (choice == 8) undoCompleted();
        else if (choice == 9) {
            string topic;
            cout << "Topic: ";
            getline(cin >> ws, topic);
            enqueueRevision(topic.c_str());
        }
        else if (choice == 10) reviseNext();
        else if (choice == 11) analysis.showOverall();
        else if (choice == 12) analysis.showSubjectWise();
        else if (choice == 13) {
            loggedOut = true;
            cout << "Logged out. Your progress is saved.\n";
        }
        else if (choice != 0)
            cout << "Invalid choice. Enter a number from 0 to 13.\n";

        saveData(currentUser);   // save progress to the file after every action
    } while (choice != 0 && !loggedOut);
    return loggedOut;
}
