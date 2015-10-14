#ifndef ACTIVITY_SELECTION_H_
#define ACTIVITY_SELECTION_H_

struct activity {
  int start_time;
  int end_time;
};

inline bool compare(activity &a1, activity &a2) {
  return a1.end_time < a2.end_time;
}

void activity_selection();

#endif
