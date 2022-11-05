#pragma once

#include <atomic>
class WorkCounter
{
public:
	WorkCounter() = default;
	~WorkCounter() = default;
	WorkCounter(const WorkCounter& another) = delete;
	WorkCounter& operator = (const WorkCounter& another) = delete;
	void Incriment();
	void Decriment();
	int  GetValueUnderTheCounter();
private:
	std::atomic<int> counter_{ 0 };
};

