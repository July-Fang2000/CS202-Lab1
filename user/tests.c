#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
  printf("Active processes: %d\n", sysinfo(0));
  printf("Total syscalls: %d\n", sysinfo(1));
  printf("Free memory pages: %d\n", sysinfo(2));
  exit(0);
}
