#include "job_sequencing.h"

#include <algorithm>
#include <memory>
#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::copy_if;
using std::endl;
using std::vector;
using std::sort;
using std::string;

vector<Job> get_selection(vector<Job> jobs);

vector<Job> get_selection(vector<Job> jobs) {
  sort(jobs.begin(), jobs.end(),
       [](Job& l, Job& r) { return l.profit > r.profit; });

  vector<bool> slot(jobs.size(), true);
  vector<Job> ret;

  for (auto job : jobs) {
    for (auto i = job.deadline - 1; i >= 0; i--) {
      if (slot[i] == true) {
        slot[i] = false;
        ret.push_back(job);
        break;
      }
    }
  }

  return ret;
}

void job_sequencing() {
  vector<Job> jobs({{"a", 4, 20}, {"b", 1, 10}, {"c", 1, 50}, {"d", 1, 30}});

  auto res = get_selection(jobs);

  for (auto r : res) {
    cout << r.id << " " << r.deadline << " " << r.profit << endl;
  }
}
