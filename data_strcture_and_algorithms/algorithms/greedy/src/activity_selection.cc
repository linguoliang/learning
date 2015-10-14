#include "activity_selection.h"

#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::sort;

void activity_selection() {
  vector<activity> activities = {{1, 2}, {3, 4}, {0, 6},
                                 {5, 7}, {8, 9}, {5, 9}};
  sort(activities.begin(), activities.end(), compare);

  vector<activity>::size_type i = 0;
  cout << activities[i].start_time << " " << activities[i].end_time << endl;

  for (vector<activity>::size_type j = 0; j != activities.size(); ++j) {
    if (activities[j].start_time >= activities[i].end_time) {
      cout << activities[j].start_time << " " << activities[j].end_time << endl;
      i = j;
    }
  }
}
