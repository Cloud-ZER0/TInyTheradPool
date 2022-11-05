#pragma once

#include <stack>
#include <functional>
#include <condition_variable>
#include <mutex>

using Task = std::function<void()>;

class TaskQueue
{
public:
	// DEFAULT CONCSTRUCTORS
	TaskQueue() = default;
	~TaskQueue() = default;

	// NON COPPYABLE
	TaskQueue(const TaskQueue& another) = delete;
	TaskQueue& operator = (const TaskQueue& another) = delete;

	void Put(Task&& task);
	std::optional<Task> Take();
	void Close();
	void Cancel();
private:
	void clearTheBuffer();
private:
	std::stack<Task> buffer_; // FIFO (GUARDED BY mutex_)
	std::mutex mutex_;
	std::condition_variable is_empty;
	std::atomic_bool closed{ false };
	std::atomic_bool canceled{ false };
};

