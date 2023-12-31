#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

float avg(vector<int>&); //returns arithmetic average from values in vector
int fileLoad(fstream&, vector<int>[]); //loads file data to table of vectors
int vecSum(vector<int>&);
bool newComeVisualise(vector<int>[], int);
void visualisation(vector<int>[]);
float fcfs(vector<int>[]); //performs simulation of fcfs algorithm
int sjf(vector<int>[]); //performs simulation of sjf algorithm
void wait();

int main() {
    fstream fInput("../input.txt",ios::in), fOutput("../output.txt",ios::out);
    const size_t size=2;
    vector<int> dataArr[size];
    fileLoad(fInput, dataArr);
    cout<<"Choose an algorithm:\n\t1 — FCFS\n\t2 — SJF\n>> ";
    int userChoose;
    userChoose=getchar();
    switch(userChoose)
    {
        case '1':
            fcfs(dataArr);
//            cout<<"|"<<fcfs(dataArr)<<"|";
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

int fileLoad(fstream &fInput, vector<int> tab[])
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
        for(int i=0; i<taskCounter; ++i)
        {
            fInput>>temp;
            tab[ipre].push_back(temp);
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

int vecSum(vector<int> &tab)
{
    int sum=0;
    for(auto &i: tab)
        sum+=i;
    return sum;
}

bool newComeVisualise(vector<int> tab[], int tact)
{
    string processes;
    bool gained_=false;
    for(int i=0; i<tab[0].size(); ++i)
    {
        if(tab[2][i]==tact)
        {
            gained_=true;
            processes+=to_string(i)+"  ";
        }
    }
    if(gained_)
    {
        cout<<"\n"<<tact<<"\tgained new processes: "<<processes;
    }
    return gained_;
}

void visualisation(vector<int> tab[])
{
    //tab {so-called number of process' : tacts : tactOfBeginning}
    cout<<"tact\tpr. no\tremaining tacts\n--------------------------------------";
    int tact=0;
    for(int i=0; i</*sum*/tab[0].size(); ++i)
    {
        bool showed_=false;
        for(int ii=0; ii<tab[1][i]; ++ii)
        {
            string tactvisual=newComeVisualise(tab,tact)?"":to_string(tact);
            if(!showed_)
            {
                cout<<"\n"<<tactvisual<<"\t'"<<tab[0][i]<<"'\t"<<tab[1][i]-ii-1;
                showed_=true;
                wait();
            }
            tact++;
        }
    }
}


float fcfs(vector<int> tab[])
{
    int time=0;
    vector<int> timeTab;
    vector<int> toDraw[3];
    for(size_t i=0; i<tab[0].size(); ++i)
    {
        timeTab.push_back(time-tab[0][i]);
        time+=tab[1][i];
        toDraw[0].push_back(i);
    }
    toDraw[1]=tab[1];
    toDraw[2]=tab[0];
    visualisation(toDraw);
    return avg(timeTab);
}

int sjf(vector<int> tab[])
{

    return 0;
}

void wait()
{
    for(int i=INT_MIN/3;i<0; i++);
}