#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX_PROC 10
struct pinfo {
  int ppid;
  int syscall_count;
  int page_usage;
};
void print_sysinfo(void) {
  int n_active_proc, n_syscalls, n_free_pages;
  n_active_proc = sysinfo(0);
  n_syscalls = sysinfo(1);
  n_free_pages = sysinfo(2);
  printf("[sysinfo] active proc: %d, syscalls: %d, free pages: %d\n",
         n_active_proc, n_syscalls, n_free_pages);
}
int main(int argc, char *argv[]) {
  int mem, n_proc, ret, proc_pid[MAX_PROC];
  if (argc < 3) {
    printf("Usage: %s [MEM] [N_PROC]\n", argv[0]);
    exit(-1);
  }
  mem = atoi(argv[1]);
  n_proc = atoi(argv[2]);
  if (n_proc > MAX_PROC) {
    printf("Cannot test with more than %d processes \n", MAX_PROC);
    exit(-1);
  }
  print_sysinfo();
  for (int i = 0; i < n_proc; i++) {
    sleep(1);
    ret = fork();
    if (ret == 0) {
      struct pinfo param;
      malloc(mem);
      for (int j = 0; j < 10; j++)
        procinfo(&param);
      printf("[procinfo %d] ppid: %d, syscalls: %d, page usage: %d\n", getpid(),
             param.ppid, param.syscall_count, param.page_usage);
      while (1)
        ;
    } else {
      proc_pid[i] = ret;
      continue;
    }
  }
  sleep(1);
  print_sysinfo();
  for (int i = 0; i < n_proc; i++)
    kill(proc_pid[i]);
  exit(0);
}
