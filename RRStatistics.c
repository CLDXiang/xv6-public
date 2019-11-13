#include "types.h"
#include "stat.h"
#include "user.h"

#define N  50

// int factorial(int n) {
//   if (n == 1 || n == 0) return 1;
//   return n * factorial(n - 1);
// }


void
RRStatistics(void)
{
  int n, pid;

  printf(1, "RRStatistics START\n");

  for(n=0; n<N; n++){
    pid = fork();
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

  int ctime, rutime, retime, sltime;
  int num_pid = 0;
  int total = 0;


  for(; n > 0; n--){
    pid = waitSch(&ctime, &rutime, &retime, &sltime);
    if(pid < 0){
      printf(1, "wait stopped early\n");
      exit();
    }
    printf(1, "pid: %d -- ctime = %d, rutime = %d, retime = %d, sltime = %d\n", pid, ctime, rutime, retime, sltime);
    num_pid ++;
    total += rutime + retime + sltime;
  }

  printf(1, "Average time(RR): %d\n", total / num_pid); // unnecessary to be float

  if(waitSch(&ctime, &rutime, &retime, &sltime) != -1){
    printf(1, "wait got too many\n");
    exit();
  }

  printf(1, "RRStatistics END\n");
}

int
main(void)
{
  RRStatistics();
  exit();
}
