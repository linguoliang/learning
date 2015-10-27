#ifndef JOB_SEQUENCING_H_
#define JOB_SEQUENCING_H_

#include <string>

struct Job {
  std::string id;
  int deadline;
  int profit;
};

void job_sequencing();

#endif
