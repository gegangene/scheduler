//
// Created by Bartłomiej Pruszczyk on 13/01/2024.
//

#include <fstream>
#include <vector>
#include "fileLoad.h"

char fileLoad(std::fstream &fInput, std::vector<int> tab[])
{
	//line from file
	std::string line;
	if(!getline(fInput, line))
		return 99;

	fInput.seekg(0);
	// number of lines in file
	char lineCounter=0;
	while(!fInput.eof()&&lineCounter<5)
	{
		getline(fInput,line);
		std::string temp;
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


//    cout<<tab[0].dataArrSize()<<"\t"<<tab[1].dataArrSize()<<endl;

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
