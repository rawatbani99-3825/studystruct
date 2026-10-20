#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;
class Analysis {
    vector<int>* graph;
    vector<string>* names;
    vector<int>* subjectNodes;
public:
    Analysis(vector<int> g[], vector<string>& n, vector<int>& s) {
        graph = g;
        names = &n;
        subjectNodes = &s;
    }
    void showOverall(int totalNodes) {
        cout << "\n OVERALL ANALYSIS     \n";
        vector<bool> visited(totalNodes, false);
        queue<int> q;
        for (int start = 0; start < totalNodes; start++) {
            if (visited[start])
                continue;
            q.push(start);
            visited[start] = true;
            while (!q.empty()) {
                int current = q.front();
                q.pop();
                cout << (*names)[current] << " ";
                for (int next : graph[current]) {
                    if (!visited[next]) {
                        visited[next] = true;
                        q.push(next);
                    }
                }
            }
        }
        cout << endl;
    }
    void showSubjectWise() {
        cout << "\n SUBJECT-WISE ANALYSIS     \n";
        for (int subject : *subjectNodes) {
            vector<bool> visited(names->size(), false);
            vector<int> stack;
            cout << "\nSubject: " << (*names)[subject] << endl;
            stack.push_back(subject);
            visited[subject] = true;
            while (!stack.empty()) {
                int current = stack.back();
                stack.pop_back();
                cout << (*names)[current] << " ";
                for (int i = graph[current].size() - 1; i >= 0; i--) {
                    int next = graph[current][i];
                    if (!visited[next]) {
                        visited[next] = true;
                        stack.push_back(next);
                    }
                }
            }
            cout << endl;
        }
    }
    void subjectWiseGrowth() {
        cout << "\n SUBJECT-WISE STUDENT GROWTH\n";
        int n;
        cout << "Enter number of subjects: ";
        cin >> n;
        if (n <= 0) {
            cout << "Invalid number of subjects.\n";
            return;
        }
        vector<string> subject(n);
        vector<int> total(n), completed(n);
        for (int i = 0; i < n; i++) {
            cout << "\nEnter subject " << i + 1 << ": ";
            cin >> subject[i];
            cout << "Enter total tasks for " << subject[i] << ": ";
            cin >> total[i];
            cout << "Enter completed tasks for " << subject[i] << ": ";
            cin >> completed[i];
            if (total[i] < 0)
                total[i] = 0;
            if (completed[i] < 0)
                completed[i] = 0;
            if (completed[i] > total[i])
                completed[i] = total[i];
        }
        ofstream data("subject_growth.dat");
        cout << "\n SUBJECT PERFORMANCE \n";
        for (int i = 0; i < n; i++) {
            double performance = 0;
            if (total[i] != 0)
                performance = (double)completed[i] / total[i] * 100;
            cout << subject[i] << " : "<< performance << "%\n";
            data << i + 1 << " " << performance << endl;
        }
        data.close();
        ofstream plot("subject_growth.gp");
        plot << "set terminal qt persist\n";
        plot << "set title 'Subject-wise Student Performance'\n";
        plot << "set xlabel 'Subjects'\n";
        plot << "set ylabel 'Performance (%)'\n";
        plot << "set yrange [0:100]\n";
        plot << "set grid\n";
        plot << "set xtics (";
        for (int i = 0; i < n; i++) {
            plot << "'" << subject[i] << "' " << i + 1;
            if (i != n - 1)
                plot << ", ";
        }
        plot << ")\n";
        plot << "plot 'subject_growth.dat' using 1:2 "<< "with linespoints lw 2 pt 7 "<< "title 'Student Performance'\n";
        plot << "set terminal qt persist\n";
        plot.close();
        string command = "start \"\" \"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persist \"subject_growth.gp\"";
system(command.c_str());
        cout << "\nSubject-wise growth graph generated.\n";
    }
    void overallGrowth() {
        cout << "\n OVERALL STUDENT GROWTH \n";
        int n;
        cout << "Enter number of subjects: ";
        cin >> n;
        if (n <= 0) {
            cout << "Invalid number of subjects.\n";
            return;
        }
        int totalTasks = 0;
        int completedTasks = 0;
        for (int i = 0; i < n; i++) {
            string subject;
            int total, completed;
            cout << "\nEnter subject " << i + 1 << ": ";
            cin >> subject;
            cout << "Enter total tasks for " << subject << ": ";
            cin >> total;
            cout << "Enter completed tasks for " << subject << ": ";
            cin >> completed;
            if (total < 0)
                total = 0;
            if (completed < 0)
                completed = 0;
            if (completed > total)
                completed = total;
            totalTasks += total;
            completedTasks += completed;
        }
        double performance = 0;
        if (totalTasks > 0)
            performance = (double)completedTasks / totalTasks * 100;
        cout << "\n OVERALL PERFORMANCE \n";
        cout << "Total Tasks     : " << totalTasks << endl;
        cout << "Completed Tasks : " << completedTasks << endl;
        cout << "Overall Growth  : " << performance << "%\n";
        ofstream data("overall_growth.dat");
        data << "0 0\n";
        for (int i = 1; i <= completedTasks; i++) {
            double growth = (double)i / totalTasks * 100;
            data << i << " " << growth << endl;
        }
        data.close();
        ofstream plot("overall_growth.gp");
        plot << "set terminal qt persist\n";
        plot << "set title 'Overall Student Growth'\n";
        plot << "set xlabel 'Completed Tasks'\n";
        plot << "set ylabel 'Performance (%)'\n";
        plot << "set yrange [0:100]\n";
        plot << "set grid\n";
        plot << "plot 'overall_growth.dat' using 1:2 "<< "with linespoints lw 2 pt 7 "<< "title 'Overall Student Growth'\n";
        plot << "set terminal qt persist\n";
        plot.close();
        string command = "start \"\" \"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persist \"overall_growth.gp\"";
system(command.c_str());
        cout << "\nOverall growth graph generated.\n";
    }
    void growthAnalysis() {
        int choice;
        cout << "\n STUDENT GROWTH \n";
        cout << "1. Subject-wise Student Growth\n";
        cout << "2. Overall Student Growth\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1)
            subjectWiseGrowth();
        else if (choice == 2)
            overallGrowth();
        else if (choice == 3)
            cout << "Exiting growth analysis.\n";
        else
            cout << "Invalid choice.\n";
    }
};
int main() {
    int numberOfSubjects;
    cout << "Enter number of subjects: ";
    cin >> numberOfSubjects;
    vector<string> names;
    vector<int> subjectNodes;
    vector<pair<int, int>> connections;
    for (int i = 0; i < numberOfSubjects; i++) {
        string subject;
        cout << "\nEnter subject " << i + 1 << ": ";
        cin >> subject;
        int subjectNode = names.size();
        subjectNodes.push_back(subjectNode);
        names.push_back(subject);
        int numberOfTopics;
        cout << "Enter number of topics: ";
        cin >> numberOfTopics;
        for (int j = 0; j < numberOfTopics; j++) {
            string topic;
            cout << "Enter topic " << j + 1 << ": ";
            cin >> topic;
            int topicNode = names.size();
            names.push_back(topic);
            connections.push_back({subjectNode, topicNode});
        }
    }
    int totalNodes = names.size();
    vector<int>* graph = new vector<int>[totalNodes];
    for (auto connection : connections)
        graph[connection.first].push_back(connection.second);
    Analysis analysis(graph, names, subjectNodes);
    analysis.showOverall(totalNodes);
    analysis.showSubjectWise();
    analysis.growthAnalysis();
    delete[] graph;
    return 0;
}
