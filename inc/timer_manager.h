#pragma once

#include <forward_list>

class TimerCallback {
 public:
  TimerCallback(int frequency, bool one_off, void (*const callback)())
      : frequency_(frequency),
        frames_until_(frequency),
        one_off_(one_off),
        callback_(callback) {
    id_ = next_id_;
    ++next_id_;
  };

  int frames_until_;
  const int frequency_;
  const bool one_off_;
  void (*const callback_)();

  friend bool operator==(const TimerCallback& lhs, const TimerCallback& rhs);

 private:
  int id_;
  static int next_id_;
};

class TimerManager {
 public:
  static void RegisterTimerCallback(int frequency, bool one_off,
                                    void (*const callback)());

  static void ClearTimers();

  static void ProcessTimers();

 private:
  static std::forward_list<TimerCallback> timer_callbacks_;
};
