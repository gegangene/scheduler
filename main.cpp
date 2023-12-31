#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

float avg(vector<int>&);
char fileLoad(fstream&, vector<char>[]);
float fcfs(vector<char>[]);
int sjf(vector<char>[]);

int main() {
    fstream fInput("../input.txt",ios::in), fOutput("../output.txt",ios::out);
    const size_t size=2;
    vector<char> dataArr[size];
    fileLoad(fInput, dataArr);
    cout<<"Choose an algorithm:\n\t1 — FCFS\n\t2 — SJF\n>> ";
    char userChoose;
    userChoose=getchar();
    switch(userChoose)
    {
        case '1':
            cout<<"|"<<fcfs(dataArr)<<"|";
            break;
        case '2':
            sjf(dataArr);
            break;
        default:
            cout<<"bad input.";
            return 1;
    }
    return 0;
}

char fileLoad(fstream &fInput, vector<char> tab[])
{
    string firstLine;
    getline(fInput, firstLine);
    char taskCounter=firstLine.length()==0?0:1;
    for(auto i: firstLine)
    {
        if(i==' '||i==10 /*eol ASCII number*/)
            taskCounter++;
    }
    //cout<<(int)taskCounter; //uncomment to check is taskCounter counted properly
    int temp;
    fInput.seekg(0); //revert to beginning when we know how many processes we have to handle with
    for(size_t ipre=0; ipre<2; ++ipre) //as we have only *size* lines which interests us, i handle only them
        for(char i=0; i<taskCounter; ++i)
        {
            fInput>>temp;
            tab[ipre].push_back(static_cast<char>(temp));
        }
    return 0;
}

float avg(vector<int> &tab)
{
    int sum=0;
    for(auto &i: tab)
    {
        sum+=i;
    }
    return static_cast<float>(sum)/static_cast<float>(tab.size());
}

float fcfs(vector<char> tab[])
{
    int time=0;
    vector<int> timeTab;
    for(size_t i=0; i<tab[0].size(); ++i)
    {
        timeTab.push_back(time-tab[0][i]);
        time+=tab[1][i];
    }
    return avg(timeTab);
}

int sjf(vector<char> tab[])
{

    return 0;
}