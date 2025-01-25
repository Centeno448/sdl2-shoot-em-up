#include "timer_manager.h"

bool operator==(const TimerCallback& lhs, const TimerCallback& rhs) {
  return lhs.id_ == rhs.id_;
}

int TimerCallback::next_id_ = 1;

void TimerManager::RegisterTimerCallback(int frequency, bool one_off,
                                         void (*const callback)()) {
  timer_callbacks_.emplace_front(frequency, one_off, callback);
}

std::forward_list<TimerCallback> TimerManager::timer_callbacks_ = {};

void TimerManager::ClearTimers() { timer_callbacks_.clear(); }
