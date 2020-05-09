#include <iostream>
#include <ctime>
#include "Process.h"
#include "Executor.h"
using namespace std;

int main() {
	// Receiving the parametres
	int queues, priorities;
	cout << "Number of executing queues: ";
	cin >> queues;
	cout << "Number of priorities: ";
	cin >> priorities;

	// Creating the executors (the ones that have queues)
	Executor* executors = new Executor[queues];
	for (int i = 0; i < queues; i++) {
		executors[i] = Executor();
	}

	// Creating the processes
	Process* processes = new Process[50];
	srand(time(NULL));
	for (int i = 0; i < 50; i++) {
		int rand_time = rand() % 15;
		int priority = (rand() % priorities) + 1;
		processes[i] = Process(executors[i % queues], rand_time, priority);
		cout << "The process " << i << " is allocated to executor " << i % queues << endl;
	}

	// Executing the processes
	while (true) {
		for (int i = 0; i < queues; i++) {
			if (executors[i].execution_queue.empty())
				continue;
			Process current_process = *executors[i].execution_queue.begin();
			executors[i].execution_queue.erase(executors[i].execution_queue.begin());
			Process next_in_queue;
			bool next_in_queue_exists = false;
			if (!executors[i].execution_queue.empty()) {
				next_in_queue = *executors[i].execution_queue.begin();
				next_in_queue_exists = true;
			}
			int execution_code;
			if (!next_in_queue_exists)
				execution_code = current_process.execute();
			else
				execution_code = current_process.execute(next_in_queue);

			switch (execution_code) {
			case 0:
				cout << "The process was finished successfully" << endl;
				break;
			case 1:
				current_process.push_to_queue_again(current_process.executor);
				cout << "The process was terminated" << endl;
				break;
			case 2:
				current_process.push_to_queue_again(current_process.executor);
				executors[i].execution_queue.erase(executors[i].execution_queue.begin());
				cout << "The other process from the queue was finished successfully" << endl;
				cout << "The original process was terminated" << endl;
				break;
			case 3:
				current_process.push_to_queue_again(current_process.executor);
				next_in_queue.push_to_queue_again(current_process.executor);
				executors[i].execution_queue.erase(executors[i].execution_queue.begin());
				cout << "Both the original process and other process from the queue were terminated" << endl;
				break;
			}
		}

		bool time_to_stop_execution = true;
		for (int i = 0; i < queues; i++)
			if (!executors[i].execution_queue.empty())
				time_to_stop_execution = false;

		if (time_to_stop_execution)
			break;
	}
}