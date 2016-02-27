#include <unistd.h>
#include <sys/sendfile.h>
#include "copyFunctions.h"
#include <vector>
#include <fstream>
#include <fcntl.h>

struct Grade {
    string student;
    int semester;
    string subject;
    double points;
};
void customCopy(string inPath, string outPath) {
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

void posixCopy(string inPath, string outPath) {
    char* buffer = new char[2056]; // 256 byte for a null-terminator
    ssize_t readAmount = 0;
    size_t head = 0; // point to the current char to read
    size_t step = 2056;

    int inFiledes = open(inPath.c_str(), O_RDONLY);
    int outFiledes = open(outPath.c_str(), O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (inFiledes == -1 || outFiledes == -1) {
        cout << "Cannot open in/out-file, check permissions";
        return;
    }

    do {
        readAmount = pread(inFiledes, buffer, step, head);
        buffer[readAmount] = 0; // pread doesn't append string null-terminator, so, let's do it manually
        write(outFiledes, buffer, readAmount);
        cout << buffer;

        head += step;
    } while(readAmount == step);

    close(inFiledes);
    close(outFiledes);
}

void sendfileCopy(string inPath, string outPath) {
    int inFiledes = open(inPath.c_str(), O_RDONLY);
    int outFiledes = open(outPath.c_str(), O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (inFiledes == -1 || outFiledes == -1) {
        cout << "Cannot open in/out-file, check permissions";
        return;
    }

    sendfile(outFiledes, inFiledes, 0, 100500);

    close(inFiledes);
    close(outFiledes);
}
