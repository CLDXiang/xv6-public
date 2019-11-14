#include "types.h"
#include "stat.h"
#include "user.h"

#define N  12

void
PBStatistics(void)
{
  int n, pid;

  printf(1, "PBStatistics START\n");

  for(n=0; n<N*4; n++){
    pid = fork();
    if(pid > 0) {
      setPriority(pid, pid % 4 + 1);
    }
    if(pid < 0)
      break;
    if(pid == 0) {
      int i;
      volatile int s = 0;
      for (i = 0; i < 100000000; i++)
        s++;
      exit();
    }
  }

  int ctime, rutime, retime, sltime, priority;
  int num_pid[4] = {0, 0, 0, 0};
  int total[4] = {0, 0, 0, 0};

  for(; n > 0; n--){
    pid = waitSch(&ctime, &rutime, &retime, &sltime, &priority);
    if(pid < 0){
      printf(1, "wait stopped early\n");
      exit();
    }
    printf(1, "pid: %d -- ctime = %d, rutime = %d, retime = %d, sltime = %d, priority = %d\n", pid, ctime, rutime, retime, sltime, priority);
    num_pid[pid % 4] ++;
    total[pid % 4] += rutime + retime + sltime;
  }

  int pi;
  for (pi = 0; pi < 4; pi++)
    printf(1, "Average time(PB) with priority %d: %d\n", pi+1, total[pi] / num_pid[pi]); // unnecessary to be float
  
  printf(1, "Average time(PB): %d\n", (total[0] + total[1] + total[2] + total[3]) / (num_pid[0] + num_pid[1] + num_pid[2] + num_pid[3])); // unnecessary to be float

  if(waitSch(&ctime, &rutime, &retime, &sltime, &priority) != -1){
    printf(1, "wait got too many\n");
    exit();
  }

  printf(1, "PBStatistics END\n");
}

int
main(void)
{
  PBStatistics();
  exit();
}
