#pragma once

#include <vector>
#include <thread>
#include <functional>
#include <iostream>
#include <cassert>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include "TaskQueue.h"
#include "WorkCounter.h"

namespace tp {
	class ThreadPool
	{
	public:
		using Task = std::function<void()>;
		friend ThreadPool* Current();
	public:
		ThreadPool() = delete;

		~ThreadPool();

		explicit ThreadPool(const std::size_t& psz);

		ThreadPool(const ThreadPool& other) = delete;

		ThreadPool& operator = (const ThreadPool& other) = delete;

		void Submit(Task&& task);

		void Stop();

		void Wait();

	private:
		void workerRoutin();
		void startWorkerThreads(std::size_t workersSize);
		static ThreadPool* getCurrent();
	private:
		std::size_t poolSize{ 0 };
		std::vector<std::thread> workers_;
		TaskQueue BlockingQueue;
		WorkCounter BlockingCounterOfTasks;
		std::mutex mutex_; // TO SLEEP IN FUTEX WHILE WAITING FOR TASKS TO END
		std::condition_variable empty_queue;
		//static thread_local ThreadPool* self;
	};

	static ThreadPool* Current() {
		// NOT IMPLIMENTED YET
		std::abort();
		//return ThreadPool::getCurrent();
	}
}

