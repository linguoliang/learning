//
// Created by chaomai on 6/3/15.
//

#include "test2.h"

void test2ex1(void){
  typedef struct s_block *t_block;
  struct s_block {
    size_t size;
    t_block next;
    int free;
    int padding;
    char data[1];
  };

  struct s_block s;

  printf("%lu\n", sizeof(size_t));
  printf("%lu\n", sizeof(t_block));
  printf("%lu\n", sizeof(int));
  printf("%lu\n", sizeof(char));
  printf("%lu\n", sizeof(char*));
}

void test2ex2(void) {
  typedef struct s_block *t_block;
  struct s_block {
    size_t size;
    t_block next;
    int free;
    int padding;
    char data[1];
  };

  struct s_block s1;
  struct s_block s2;

  s1.size=10;
  s1.next=&s2;
}

void test2(void) {

}
