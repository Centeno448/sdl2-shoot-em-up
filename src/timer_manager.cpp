#include "timer_manager.h"

void TimerManager::RegisterTimerCallback(int frequency, bool one_off,
                                         void (*const callback)()) {
  timer_callbacks_.emplace_front(frequency, one_off, callback);
}

bool operator==(const TimerCallback& lhs, const TimerCallback& rhs) {
  return lhs.id_ == rhs.id_;
}

std::forward_list<TimerCallback> TimerManager::timer_callbacks_ = {};

int TimerCallback::next_id_ = 1;
