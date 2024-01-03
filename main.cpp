#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// loads file data to table of vectors
int fileLoad(fstream&, vector<int>[]);
// sums all values of given vector
int vecSum(vector<int>&);
// returns arithmetic average from values in vector
float avg(vector<int>&);
// shows are they new processes gained in current tact
bool newComeVisualise(vector<int>[], int&);
// visualises work of algorithm based on given vector {id : tacts : arrivingTact} and result [float]
void visualisation(vector<int>[], float);
// performs simulation of fcfs algorithm
void fcfs(vector<int>[]);
//bubble sort by tacts for vector table {id : tacts}
void sortVec(vector<int> []);
// performs simulation of sjf algorithm
void sjf(vector<int>[]);
// performs "waiting" by counting from INT_MIN/3 to 0
void wait();

int main() {
    fstream fInput("../input.txt",ios::in), fOutput("../output.txt",ios::out);
    //size of data array
    const size_t size=3;
    // array of processes details read from input file
    // {arriving : tacts : id}
    vector<int> dataArr[size];
    fileLoad(fInput, dataArr);

    cout<<"Choose an algorithm:\n\t1 — FCFS\n\t2 — SJF\n>> ";
    int userChoose=getchar();
    switch(userChoose)
    {
        case '1':
            fcfs(dataArr);
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
    // holds value of how many tasks there is written in file
    int taskCounter=firstLine.length()==0?0:1;

    for(auto i: firstLine)
    {
        if(i==' '||i==10 /*eol ASCII number*/)
            ++taskCounter;
    }
    //cout<<(int)taskCounter; //uncomment to check is taskCounter counted properly

    // temporary variable to hold value read from file
    int temp;
    fInput.seekg(0); //revert to beginning when we know how many processes we have to handle with
    for(size_t ipre=0; ipre<2; ++ipre) //as we have only *size* lines which interests us, i handle only them
        for(int i=0; i<taskCounter; ++i)
        {
            if(ipre<1)
                tab[2].push_back(i);
            fInput>>temp;
            tab[ipre].push_back(temp);
        }
    return 0;
}

int vecSum(vector<int> &tab)
{
    int sum=0;
    for(auto &i: tab)
        sum+=i;
    return sum;
}

float avg(vector<int> &tab)
{
    return static_cast<float>(vecSum(tab))/static_cast<float>(tab.size());
}

bool newComeVisualise(vector<int> tab[], int &tact)
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

void visualisation(vector<int> tab[], float avg)
{
    cout<<"average waiting time: "<<avg<<"\n\n";
    cout<<"visualisation of algorithm:\n";
    // tab : {so-called number of process : tacts : tactOfBeginning}
    cout<<"tact\tid\tremaining tacts to end\n--------------------------------------";
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


void fcfs(vector<int> tab[])
{
    int time=0;
    // {waitingTime}
    vector<int> timeTab;
    // {id : tacts : arriving}
    vector<int> toDraw[3];
    for(size_t i=0; i<tab[0].size(); ++i)
    {
        timeTab.push_back(time-tab[0][i]);
        time+=tab[1][i];
    }
    toDraw[0]=tab[2];
    toDraw[1]=tab[1];
    toDraw[2]=tab[0];
    visualisation(toDraw,avg(timeTab));
}

//int minValVec(vector<int> tab[])
//{
//    int minVal=INT_MAX;
//    for(auto i: tab[1])
//    {
//        minVal=i<minVal?i:minVal;
//    }
//    return minVal;
//}

void sortVec(vector<int> tab[])
{
    for(size_t i=1; i<tab[0].size(); ++i)
    {
        int temp[2];
        if(tab[1][i-1]>tab[1][i])
        {
            temp[0]=tab[0][i-1];
            temp[1]=tab[1][i-1];
            tab[0][i-1]=tab[0][i];
            tab[1][i-1]=tab[1][i];
            tab[0][i]=temp[0];
            tab[1][i]=temp[1];
        }
    }
}

void sjf(vector<int> tab[])
{
    // array of processes currently available to put on processor.
    // **use only when sorted!**
    // {id : tacts : arriving}
    vector<int> currentlyAvailable[3];
    // {waitingTime}
    vector<int> timeTab;
    // array for "drawing" - visualisation function
    // {id : tacts : arriving}
    vector<int> toDraw[3];

    // tacts needed to complete all processes
    int tacts=vecSum(tab[1]);

    // processor busy status
    bool busy=false;
    // tacts lasts to end current process
    int toEndCurrent=0;

    // for every tact, check what's going on in there
    for(int i=0; i<tacts; ++i)
    {
        for(size_t ii=0; ii<tab[0].size(); ++ii)
        {
            // loading processes gained in current tact
            if(i==tab[0][ii])
            {
                currentlyAvailable[0].push_back(tab[2][ii]);
                currentlyAvailable[1].push_back(tab[1][ii]);
                currentlyAvailable[2].push_back(tab[0][ii]);

            }
            // sorting available processes by tacts
            sortVec(currentlyAvailable);
        }

        //loading process on processor
        if(!busy)
        {
            busy=true;
            toDraw[0].push_back(currentlyAvailable[0][0]);
            toDraw[1].push_back(currentlyAvailable[1][0]);
            toDraw[2].push_back(currentlyAvailable[2][0]);
            timeTab.push_back(i-currentlyAvailable[2][0]);
            toEndCurrent=currentlyAvailable[1][0]-1;
            currentlyAvailable[0].erase(currentlyAvailable[0].begin());
            currentlyAvailable[1].erase(currentlyAvailable[1].begin());
            currentlyAvailable[2].erase(currentlyAvailable[2].begin());
        }

        else
        {
            if(toEndCurrent==0)
            {
                busy=false;
            }
            --toEndCurrent;
        }
    }

    visualisation(toDraw,avg(timeTab));

//    for(size_t i=0; i<toDraw[0].size(); ++i)
//    {
//        cout<<'{'<<toDraw[0][i]<<'|'<<toDraw[1][i]<<'|'<<toDraw[2][i]<<"}\n";
//    }
//    cout<<"...................\n";
}

void wait()
{
    for(int i=INT_MIN/3;i<0; ++i);
}