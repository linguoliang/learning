#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/* 定义一个给 clone 用的栈，栈大小1M */
#define STACK_SIZE (1024 * 1024)
static char container_stack[STACK_SIZE];

char* const container_args[] = {"/bin/bash", NULL};

int container_main(void* arg) {
  /* 查看子进程的PID，我们可以看到其输出子进程的 pid 为 1 */
  printf("Container [%5d] - inside the container!\n", getpid());

  sethostname("container", 10); /* 设置hostname */
  /* 重新mount proc文件系统到 /proc下 */
  /* system("mount -t proc proc /proc"); */
  /* 功能与下面的if mount一样 */
  /* if (mount("proc", "/proc", "proc", 0, NULL) != 0) { */
  /*   perror("proc"); */
  /* } */

  /* chroot 隔离目录 */
  /* if (chdir("./rootfs") != 0 || chroot("./") != 0) { */
  /*   perror("chdir/chroot"); */
  /* } */

  /* 直接执行一个shell，以便我们观察这个进程空间里的资源是否被隔离了 */
  execv(container_args[0], container_args);
  /* perror("exec"); */
  printf("Something's wrong!\n");
  return 1;
}

int main() {
  printf("Parent - start a container!\n");
  /* 调用clone函数，其中传出一个函数，还有一个栈空间的（为什么传尾指针，因为栈是反着的）
   */
  int container_pid = clone(
      container_main, container_stack + STACK_SIZE,
      CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | CLONE_NEWNS | SIGCHLD, NULL);
  /* 等待子进程结束 */
  waitpid(container_pid, NULL, 0);
  printf("Parent [%5d] - container stopped!\n", getpid());
  return 0;
}
