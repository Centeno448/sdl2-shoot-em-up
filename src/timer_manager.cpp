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

void TimerManager::ProcessTimers() {
  auto current_timer = timer_callbacks_.begin();
  while (current_timer != timer_callbacks_.end()) {
    if (current_timer->frames_until_ == 0) {
      current_timer->callback_();

      if (current_timer->one_off_) {
        auto to_delete = (*current_timer);
        ++current_timer;
        timer_callbacks_.remove(to_delete);
      } else {
        current_timer->frames_until_ = current_timer->frequency_;
        ++current_timer;
      }

    } else {
      --current_timer->frames_until_;
      ++current_timer;
    }
  }
}
