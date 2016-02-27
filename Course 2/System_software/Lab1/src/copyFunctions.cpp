#include "copyFunctions.h"

struct Grade {
    string student;
    int semester;
    string subject;
    double points;
};

void cppCopy(string inPath, string outPath) {
    vector <Grade> grades;
    int pointsSum = 0;
    int gradesCount = 0;

    ifstream inputStream(inPath, ios::in);
    while (!inputStream.eof()) {
        Grade Grade;

        inputStream >> Grade.student;
        inputStream >> Grade.semester;
        inputStream >> Grade.subject;
        inputStream >> Grade.points;

        gradesCount++;
        pointsSum += Grade.points;
        grades.push_back(Grade);
    }
    inputStream.close();

    cout << "Average points are: " << pointsSum / gradesCount << endl;

    ofstream outputStream(outPath, ios::out);
    for (vector<Grade>::iterator it = grades.begin(); it != grades.end(); it++) {
        outputStream << it->student << " ";
        outputStream << it->semester << " ";
        outputStream << it->subject << " ";
        outputStream << it->points << endl;
    }
    outputStream.close();
}