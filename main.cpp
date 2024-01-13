#include <iostream>
#include <fstream>
#include <vector>

#include "fileLoad.h"
#include "fcfs.h"
#include "sjf.h"
#include "priority.h"

using namespace std;

int main() {
    fstream fInput("../input.txt",ios::in), fOutput("../output.txt",ios::out);
    if(!fInput.good())
    {
        cout<<"no input file!";
        return 1;
    }
    //size of data array
    const size_t size=6;
    // array of processes details read from input file
    // {arriving : tacts : id : priority : time quantum for priority sjf : time quantum for round-robin}
    vector<int> dataArr[size];
    char fStatus=fileLoad(fInput, dataArr);
    switch(fStatus)
    {
        case 0:
            break;
        case 1:
            cout<<"not enough processes placed in file";
            return 1;
        case 2:
            cout<<"not corresponding number of arriving tacts and duration of processes";
            return 1;
        case 3 ... 5:
            break;
        default:
            cout<<"file data error";
            return 1;
    }

    cout<<"Choose an algorithm:\n\t1 — FCFS\n\t2 — SJF\n\t3 — Priority SJF\n>> ";
    char userChoose=static_cast<char>(getchar());

    switch(userChoose)
    {
        case '1':
            fcfs(dataArr);
            break;
        case '2':
            sjf(dataArr);
            break;
        case '3':
            switch(fStatus)
            {
                case 3:
                    cout<<"lack of priorities in file.";
                    return 1;
                case 4:
                    cout<<"lack of time quantum for priority algorithm in file.";
                    return 1;
                case 5:
                    cout<<"not corresponding number of priorities and processes in file.";
                    return 1;
                default:
                    break;
            }
			priority(dataArr);
            break;
        default:
            cout<<"bad input.";
            return 1;
    }
    return 0;
}