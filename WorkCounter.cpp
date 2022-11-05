#include "WorkCounter.h"

void WorkCounter::Incriment() {
	counter_.fetch_add(1);
}
void WorkCounter::Decriment() {
	counter_.fetch_sub(1);
}
int WorkCounter::GetValueUnderTheCounter() {
	return counter_.load();
}
