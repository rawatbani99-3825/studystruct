@echo off
gcc -c task.c priority_queue.c merge_sort.c circular_queue.c stack.c auth.c storage.c
if errorlevel 1 goto fail
g++ main.cpp login.cpp analysis.cpp engine.cpp task.o priority_queue.o merge_sort.o circular_queue.o stack.o auth.o storage.o -o planner
if errorlevel 1 goto fail
echo.
echo Build OK. Now run: planner
goto end
:fail
echo.
echo Build FAILED. Read the error above.
:end
