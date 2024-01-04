#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// loads file data to table of vectors
char fileLoad(fstream&, vector<int>[]);
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
    if(!fInput.good())
    {
        cout<<"no input file!";
        return 1;
    }
    //size of data array
    const size_t size=6;
    // array of processes details read from input file
    // {arriving : tacts : id}
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

    cout<<"Choose an algorithm:\n\t1 — FCFS\n\t2 — SJF\n\t3 — Priority-based\n>> ";
    int userChoose=getchar();
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
            break;
        default:
            cout<<"bad input.";
            return 1;
    }
    return 0;
}

char fileLoad(fstream &fInput, vector<int> tab[])
{
    //line from file
    string line;
    if(!getline(fInput, line))
        return 99;

    fInput.seekg(0);
    char lineCounter=0;
    while(!fInput.eof()&&lineCounter<5)
    {
        getline(fInput,line);
        string temp;
		int processCounter=0;
        for(auto &i: line)
        {
            if(i==' '||&i==&line[line.size()-1])
            {
                if(&i==&line[line.size()-1])
                    temp+=i;

				int lineTemp=lineCounter>1?lineCounter+1:lineCounter;
                tab[lineTemp].push_back(stoi(temp));

                if(lineCounter==0)
                {
					tab[2].push_back(processCounter);
//					cout<<"|"<<temp<<"|"<<tab[2][processCounter]<<"|"<<lineTemp<<"|\n";
					processCounter++;
                }

				if(lineCounter>2)
				{
					break;
				}
                temp="";
            }
            else
            {
                temp+=i;
            }
        }
        ++lineCounter;
    }


//    cout<<tab[0].size()<<"\t"<<tab[1].size()<<endl;

    // checking is there corresponding number of arrivings and tacts
    if(tab[0].size()!=tab[1].size())
    {
        return 2;
    }
    // checking is there necessary number of processes
    if(tab[0].size()<15||tab[1].size()<15)
    {
        return 1;
    }
    // checking is there a priorities at all
    if(lineCounter<3)
    {
        return 3;
    }
    // checking is there corresponding number of arrivings and priorities
    if(tab[0].size()!=tab[2].size())
    {
        return 5;
    }
    //checking is time quantum exist
    else if(lineCounter<4)
    {
        return 4;
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
            processes+=to_string(tab[0][i])+"  ";
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
    cout<<"tact\tid\twaited for ... tacts\n--------------------------------------";
    int tact=0;
    for(int i=0; i</*sum*/tab[0].size(); ++i)
    {
        bool showed_=false;
        for(int ii=0; ii<tab[1][i]; ++ii)
        {
            string tactVisual=newComeVisualise(tab,tact)?"":to_string(tact);
            if(!showed_)
            {
                cout<<"\n"<<tactVisual<<"\t'"<<tab[0][i]<<"'\t"<<tact-tab[2][i];
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

void sortVec(vector<int> tab[])
{
    for(size_t i=1; i<tab[0].size(); ++i)
    {
        int temp[3];
        if(tab[1][i-1]>tab[1][i])
        {
            temp[0]=tab[0][i-1];
            temp[1]=tab[1][i-1];
            temp[2]=tab[2][i-1];
            tab[0][i-1]=tab[0][i];
            tab[1][i-1]=tab[1][i];
            tab[2][i-1]=tab[2][i];
            tab[0][i]=temp[0];
            tab[1][i]=temp[1];
            tab[2][i]=temp[2];
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

    // processor busy status indicator
    bool busy_=false;
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
        if(!busy_)
        {
            busy_=true;
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
                busy_=false;
            }
            --toEndCurrent;
        }
    }

    visualisation(toDraw,avg(timeTab));
}

void wait()
{
    for(int i=INT_MIN/3;i<0; ++i);
}