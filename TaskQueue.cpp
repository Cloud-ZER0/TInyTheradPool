#include "TaskQueue.h"

void TaskQueue::Put(Task&& task) {
	std::lock_guard lock (mutex_);
	if (closed.load() && !canceled.load()) {
		return;
	}
	else if ((!closed.load() && canceled.load()) || (closed.load() && canceled.load())) {
		if (!buffer_.empty()) {
			clearTheBuffer();
		}
		return;
	}
	else {
		buffer_.push(std::move(task));
		is_empty.notify_one();
	}
}

std::optional<Task> TaskQueue::Take() {
	std::unique_lock lock_(mutex_);

	if (closed.load() && buffer_.empty()) {
		return nullptr;
	}
	while (buffer_.empty()) {
		is_empty.wait(lock_);
	}
	auto task = std::move(buffer_.top());
	buffer_.pop();
	return task;
}

void TaskQueue::Close() {
	closed.store(true);
}
void TaskQueue::Cancel() {
	canceled.store(true);
}
void TaskQueue::clearTheBuffer() {
	std::stack<Task> cleared;
	buffer_ = cleared;
}