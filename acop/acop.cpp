// acop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Ant.h"
#include "Node.h"
#include "Edge.h"
#include "Graph.h"
#include "Path.h"
#include "Nest.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	CGraph graph("inp865.txt");

	graph.PrintInfo();

	CNest::Inst();

	int from = 0;
	int to = 0;

	do
	{
		cout << "start=";
		int from = 0;
		cin >> from;
		cout << "finish=";
		int to = 0;
		cin >> to;

		graph.FindPath(from, to);

	} while (true);
	
	graph.Save("graph.txt");
	system("pause");
	return 0;
}

