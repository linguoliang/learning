//
// Created by chaomai on 6/3/15.
//

#include "test1.h"

//void *malloc(size_t size) {
//  void *p;
//  p = sbrk(0);
//  if (sbrk(size) == (void *) (-1)) {
//    return NULL;
//  } else {
//    return p;
//  }
//}

void test1(void) {
  struct rlimit *limit = (struct rlimit *) malloc(sizeof(struct rlimit));
  getrlimit(RLIMIT_AS, limit);
  printf("soft limit: %lu, hard limit: %lu\n", limit->rlim_cur,
         limit->rlim_max);
}
