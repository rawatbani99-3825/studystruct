#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <string>
#include "task.h"

const int NODES = 4 * MAX;   

class Analysis {
    std::string name[NODES];
    bool isSubject[NODES];
    int total[NODES];            // tasks in this topic
    int done[NODES];             // completed tasks in this topic
    bool adj[NODES][NODES];      // adj[subject][topic] = true
    int n;
    int subjectTotal, subjectDone;

    int newNode(std::string s, bool subject);
    int findSubject(std::string s);
    int findTopic(int s, std::string t);
    void addToGraph(struct Task t, bool completed);
    void build();
    void dfs(int cur, bool visited[]);

public:
    void showOverall();       // BFS
    void showSubjectWise();   // DFS
};

#endif
