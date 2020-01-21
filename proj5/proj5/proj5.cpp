// proj5.cpp 
// Author: Marc Maromonte


#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

int findCity(string x)
{
	if (x == "Erie")
	{
		return 0;
	}
	else if (x == "Shanghai")
	{
		return 1;
	}
	else if (x == "Tokyo")
	{
		return 2;
	}
	else if (x == "Beijing")
	{
		return 3;
	}
	else if (x == "Hongkong")
	{
		return 4;
	}
}

string findNum(int x)
{
	switch (x)
	{
	case 0:
		return "Erie";
	case 1:
		return "Shanghai";
	case 2:
		return "Tokyo";
	case 3:
		return "Beijing";
	case 4:
		return "Hongkong";
	}
}

int main()
{
	ifstream inFile;
	inFile.open("input.txt");

	// If unable to open file exit
	//
	if (!inFile)
	{
		cout << "Unable to open file";
		exit(1);
	}

	int paths = 0;

	string temp;
	while (getline(inFile, temp))
	{
		paths++;
	}

	inFile.clear();
	inFile.seekg(0, ios::beg);

	string** input = new string* [paths];
	
	for (int i = 0; i < paths; i++)
	{
		input[i] = new string[3];
	}

	for (int i = 0; i < paths; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			inFile >> temp;
			input[i][j] = temp;
		}
	}

	/*
	for (int i = 0; i < paths; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << input[i][j] << " ";
		}
		cout << endl;
	}*/

	vector<string> cities;

	for (int i = 0; i < paths; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			string city = input[i][j];
			if (find(cities.begin(), cities.end(), city) == cities.end())
			{
				cities.push_back(city);
			}
		}
	}

	float** graph = new float * [cities.size()];
	for (int i = 0; i < cities.size(); i++)
	{
		graph[i] = new float[cities.size()];
	}

	for (int i = 0; i < cities.size(); i++)
	{
		for (int j = 0; j < cities.size(); j++)
		{
			graph[i][j] = INFINITY;
		}
	}

	for (int i = 0; i < paths; i++)
	{
		graph[findCity(input[i][0])][findCity(input[i][1])] = stof(input[i][2]);
	}
	
	/*
	for (int i = 0; i < cities.size(); i++)
	{
		for (int j = 0; j < cities.size(); j++)
		{
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	*/

	float* dist = new float[cities.size()];
	vector<int> S;
	vector<int> Q;
	vector<int> prec;

	for (int i = 0; i < cities.size(); i++)
	{
		dist[i] = INFINITY;
		Q.push_back(i);
		prec.push_back(NULL);
	}
	
	dist[0] = 0;
	
	/*
	for (int i = 0; i < cities.size(); i++)
	{
		cout << dist[i] << " ";
	}
	cout << endl;*/

	while (!Q.empty())
	{
		float min = dist[Q[0]];
		int index = 0;

		for (int i = 0; i < Q.size(); i++)
		{
			if (dist[Q[i]] != INFINITY && dist[Q[i]] < min)
			{
				min = dist[i];
				index = i;
			}
		}

		int u = Q[index];
		S.push_back(u);
		Q.erase(Q.begin()+index);

		for (int i = 0; i < cities.size(); i++)
		{
			if (graph[u][i] != INFINITY)
			{
				if (dist[i] > dist[u] + graph[u][i])
				{
					dist[i] = dist[u] + graph[u][i];
					prec[i] = u;
				}
			}
		}
		
		/*
		for (int i = 0; i < cities.size(); i++)
		{
			cout << dist[i] << " ";
		}
		cout << endl;
		*/
	}
	
	int path = 1;
	stack<int> output;
	output.push(path);

	while(path != 0)
	{
		output.push(prec[path]);
		path = prec[path];
	}
	while (!output.empty())
	{
		cout << findNum(output.top()) << " ";
		output.pop();
	}

	cout << endl << "Total Cost: " << dist[1] << endl;
}

