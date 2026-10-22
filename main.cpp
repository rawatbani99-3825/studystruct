/* StudyStruct - the only file with main().
   C part: task.c, priority_queue.c, merge_sort.c, circular_queue.c, stack.c, auth.c, storage.c
   C++ part: login.cpp, analysis.cpp, engine.cpp
   Note: we mix cin and scanf, so do not call ios::sync_with_stdio(false). */
#include "login.h"
#include "engine.h"
#include "auth.h"
#include "storage.h"

int main() {
    loadUsers();                          // read users.dat
    Login login;
    StudyPlannerEngine planner;
    while (login.run()) {                 // login screen (0 = close the program)
        loadData(currentUser);            // read this user's own saved progress
        if (!planner.run())               // inside the menu, 0 = Exit the program
            break;
    }                                     // 13 = Log out: back to the login screen
    return 0;
}
