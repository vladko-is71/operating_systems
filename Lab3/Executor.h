#pragma once
#include <vector>
using namespace std;

class Process;

class Executor
{
public:
	Executor();
	// Executor(int);
	vector<Process> execution_queue;
	int clock_time;
};