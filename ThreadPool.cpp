#include "ThreadPool.h"
#include <chrono>

using namespace std::chrono_literals;

using namespace tp;

ThreadPool::ThreadPool(const std::size_t& psz) {
	startWorkerThreads(psz);
}

ThreadPool::~ThreadPool() {
	assert(workers_.empty());
}

void::ThreadPool::workerRoutin() {
	while (true) {
		auto taskWrapper = BlockingQueue.Take();
		if (taskWrapper.has_value()) {
			auto task = taskWrapper.value();
			task();
			BlockingCounterOfTasks.Decriment();
			/*if (BlockingCounterOfTasks.GetValueUnderTheCounter() == 0) {
				empty_queue.notify_one();*/
				//std::cout << BlockingCounterOfTasks.GetValueUnderTheCounter() << '\n';
			/*if (BlockingCounterOfTasks.GetValueUnderTheCounter() > 0) {
				BlockingCounterOfTasks.Decriment();
				if (BlockingCounterOfTasks.GetValueUnderTheCounter() == 0) {
					empty_queue.notify_all();
					std::cout << BlockingCounterOfTasks.GetValueUnderTheCounter() << '\n';
				}
			}*/
		}
		//else if(!taskWrapper.has_value()) {
		//	//empty_queue.notify_all();
		//	std::cout << "No more Tasks left\n";
		//	return;
		//}
	}
}

void ThreadPool::Submit(Task&& task) {
	BlockingQueue.Put(std::move(task));
	BlockingCounterOfTasks.Incriment();
	return;
}

void ThreadPool::Wait() {
	/*while (!BlockingQueue.empty()) {
		std::cout << std::this_thread::get_id() << ' ' << "is_waiting\n";
	}*/
	assert(!workers_.empty());
	BlockingQueue.Close();
	//std::unique_lock locked(mutex_);
	while (BlockingCounterOfTasks.GetValueUnderTheCounter() != 0) {
		//empty_queue.wait(locked);
		//std::cout << "Waiting " << BlockingCounterOfTasks.GetValueUnderTheCounter() << '\n';
	}
}
void ThreadPool::Stop() {
	BlockingQueue.Cancel();
	workers_.clear();
}

void ThreadPool::startWorkerThreads(std::size_t workersSize) {
	workers_.reserve(workersSize);
	for (auto i = 0; i < workersSize; ++i) {
		workers_.emplace_back([this]() {
			workerRoutin();
		});
		workers_[i].detach();
	}
}

ThreadPool* ThreadPool::getCurrent() {
	// NOT IMPLIMENTED YET 
	std::abort();
}

