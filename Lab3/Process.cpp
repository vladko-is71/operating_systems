#include <chrono>
#include <thread>
#include <ctime>
#include <Windows.h>
#include "Process.h"
#include "Executor.h"
using namespace std;

Process::Process() {
	executor = Executor();
	_duration = 1;
	priority = 20;
}

// Initialising the process with parametres
Process::Process(Executor& original_executor, int original_duration, int original_priority) {
	executor = original_executor;
	original_executor.execution_queue.push_back(*this);
	_duration = original_duration;
	priority = original_priority;
}

// Executing the process (this function is called there's no next element in the queue)
int Process::execute() {
	chrono::milliseconds ideal_timespan(_duration);
	if (_duration < executor.clock_time) {
		chrono::milliseconds emergency_timespan(executor.clock_time);
		this_thread::sleep_for(emergency_timespan);
		return 1;
	}
	else {
		this_thread::sleep_for(ideal_timespan);
		return 0;
	}
}

// Executing the process (this function is called there are next elements in the queue)
int Process::execute(Process nextInQueue) {
	chrono::milliseconds ideal_timespan(_duration);

	int miliseconds_before_comparison = rand() % 5;
	chrono::milliseconds comparison_time(executor.clock_time);
	this_thread::sleep_for(comparison_time);

	if (nextInQueue.priority < priority) {
		chrono::milliseconds next_in_queue_time(nextInQueue._duration);
		
		if (_duration < executor.clock_time) {
			chrono::milliseconds emergency_timespan(executor.clock_time);
			this_thread::sleep_for(emergency_timespan);
			return 3;
		}
		else {
			this_thread::sleep_for(next_in_queue_time);
			return 2;
		}
	}
	
	if (_duration < executor.clock_time) {
		chrono::milliseconds emergency_timespan(executor.clock_time);
		this_thread::sleep_for(emergency_timespan);
		return 1;
	}
	else {
		this_thread::sleep_for(ideal_timespan);
		return 0;
	}
}

// Pushing the process into the queue of other executor, in case if execution failed
void Process::push_to_queue_again(Executor new_executor) {
	executor = new_executor;
	new_executor.execution_queue.push_back(*this);
}