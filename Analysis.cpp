/* Analysis: graph (subject -> topics), BFS, DFS and gnuplot graphs */
#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <cstdlib>
using namespace std;

#include "analysis.h"
#include "stack.h"

int percent(int done, int total) {
    if (total == 0)
        return 0;
    return done * 100 / total;
}

void showBar(int pct) {
    cout << "[";
    for (int i = 0; i < 10; i++) {
        if (i < pct / 10)
            cout << "#";
        else
            cout << ".";
    }
    cout << "] " << pct << "%";
}

/* Runs gnuplot on a .gp file */
void runGnuplot(string fileName) {
#ifdef _WIN32
    string command = "start \"\" gnuplot -persist " + fileName + ".gp";
#else
    string command = "gnuplot -persist " + fileName + ".gp";
#endif
    if (system(command.c_str()) != 0)
        cout << "gnuplot not found. Install gnuplot and add it to PATH.\n";
    else
        cout << "Graph opened (" << fileName << ".gp saved)\n";
}

/* OVERALL graph: pie chart of completed vs pending tasks */
void drawPie(string fileName, int done, int total) {
    int pending = total - done;
    int angle = done * 360 / total;

    ofstream plot((fileName + ".gp").c_str());
    plot << "set title 'Overall Progress: " << done << " of " << total
         << " tasks done (" << percent(done, total) << "%)'\n";
    plot << "set size square\n";
    plot << "set xrange [-1.3:1.3]\n";
    plot << "set yrange [-1.3:1.3]\n";
    plot << "unset border\n";
    plot << "unset tics\n";
    plot << "unset key\n";
    if (done > 0)
        plot << "set object 1 circle at 0,0 size 1 arc [0:" << angle << "] fc rgb 'green' fs solid\n";
    if (pending > 0)
        plot << "set object 2 circle at 0,0 size 1 arc [" << angle << ":360] fc rgb 'red' fs solid\n";
    plot << "set label 1 'Completed: " << done << "' at -1.2,-1.2 tc rgb 'dark-green'\n";
    plot << "set label 2 'Pending: " << pending << "' at 0.3,-1.2 tc rgb 'red'\n";
    plot << "plot NaN notitle\n";
    plot.close();
    runGnuplot(fileName);
}

/* SUBJECT-WISE graph: bar chart, one bar per subject */
void drawBars(string title, string fileName, string labels[], int values[], int points) {
    ofstream data((fileName + ".dat").c_str());
    for (int i = 0; i < points; i++)
        data << i + 1 << " " << values[i] << endl;
    data.close();

    ofstream plot((fileName + ".gp").c_str());
    plot << "set title '" << title << "'\n";
    plot << "set ylabel 'Performance (%)'\n";
    plot << "set yrange [0:115]\n";
    plot << "set ytics 0,20,100\n";
    plot << "set xrange [0:" << points + 1 << "]\n";
    plot << "set boxwidth 0.6\n";
    plot << "set style fill solid\n";
    plot << "set grid y\n";
    plot << "set xtics rotate by -30 (";
    for (int i = 0; i < points; i++) {
        plot << "\"" << labels[i] << "\" " << i + 1;
        if (i != points - 1)
            plot << ", ";
    }
    plot << ")\n";
    plot << "plot '" << fileName << ".dat' using 1:2 with boxes notitle, "
         << "'' using 1:($2+4):(sprintf(\"%d%%\", $2)) with labels notitle\n";
    plot.close();
    runGnuplot(fileName);
}

/* ---------- building the graph ---------- */
int Analysis::newNode(string s, bool subject) {
    name[n] = s;
    isSubject[n] = subject;
    total[n] = 0;
    done[n] = 0;
    n++;
    return n - 1;
}

int Analysis::findSubject(string s) {
    for (int i = 0; i < n; i++)
        if (isSubject[i] && name[i] == s)
            return i;
    return newNode(s, true);
}

int Analysis::findTopic(int s, string t) {
    for (int i = 0; i < n; i++)
        if (!isSubject[i] && adj[s][i] && name[i] == t)
            return i;
    int p = newNode(t, false);
    adj[s][p] = true;
    return p;
}

void Analysis::addToGraph(struct Task t, bool completed) {
    int s = findSubject(t.subject);
    int p = findTopic(s, t.topic);
    total[p]++;
    if (completed)
        done[p]++;
}

// builds the graph from the real task data (pending + completed)
void Analysis::build() {
    n = 0;
    for (int i = 0; i < NODES; i++)
        for (int j = 0; j < NODES; j++)
            adj[i][j] = false;
    for (int i = 0; i < taskCount; i++)
        addToGraph(tasks[i], false);
    for (int i = 0; i <= completedTop; i++)
        addToGraph(completedStack[i], true);
}

/* ---------- DFS (used for subject-wise) ---------- */
void Analysis::dfs(int cur, bool visited[]) {
    visited[cur] = true;
    if (!isSubject[cur]) {
        int pct = percent(done[cur], total[cur]);
        cout << "  " << name[cur] << " (" << done[cur] << "/" << total[cur] << ") ";
        showBar(pct);
        if (pct < 50)
            cout << "  <- needs work";
        cout << endl;
        subjectTotal += total[cur];
        subjectDone += done[cur];
    }
    for (int next = 0; next < n; next++)
        if (adj[cur][next] && !visited[next])
            dfs(next, visited);
}

/* ---------- BFS (overall performance) ---------- */
void Analysis::showOverall() {
    build();
    cout << "\n--- OVERALL PERFORMANCE (BFS) ---\n";
    if (n == 0) {
        cout << "No tasks yet\n";
        return;
    }
    bool visited[NODES] = {false};
    queue<int> q;
    int allTotal = 0, allDone = 0;
    for (int start = 0; start < n; start++) {
        if (visited[start] || !isSubject[start])
            continue;
        q.push(start);
        visited[start] = true;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            if (!isSubject[cur]) {
                allTotal += total[cur];
                allDone += done[cur];
            }
            for (int next = 0; next < n; next++) {
                if (adj[cur][next] && !visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
    }
    cout << "Completed " << allDone << " of " << allTotal << " tasks\n";
    showBar(percent(allDone, allTotal));
    cout << endl;
    drawPie("overall_progress", allDone, allTotal);
}

void Analysis::showSubjectWise() {
    build();
    cout << "\n--- SUBJECT-WISE PERFORMANCE (DFS) ---\n";
    if (n == 0) {
        cout << "No tasks yet\n";
        return;
    }
    bool visited[NODES] = {false};
    string labels[NODES];
    int values[NODES];
    int points = 0;
    for (int s = 0; s < n; s++) {
        if (!isSubject[s])
            continue;
        subjectTotal = 0;
        subjectDone = 0;
        cout << "\nSubject: " << name[s] << endl;
        dfs(s, visited);
        cout << "  Subject total: ";
        showBar(percent(subjectDone, subjectTotal));
        cout << endl;
        labels[points] = name[s];
        values[points] = percent(subjectDone, subjectTotal);
        points++;
    }
    drawBars("Subject-wise Performance", "subject_growth", labels, values, points);
}
