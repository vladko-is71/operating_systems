#pragma once
#include "Executor.h"

class Process
{
public:
	Process();
	Process(Executor&, int, int);
	int execute();
	int execute(Process);
	void push_to_queue_again(Executor);
	Executor executor;
	int priority;

private:
	int _duration;
};