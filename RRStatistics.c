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
  int rutime, retime, sltime;

  printf(1, "RRStatistics START\n");

  for(n=0; n<N; n++){
    pid = fork();
    if(pid < 0)
      break;
    if(pid == 0) {
      int i;
      volatile int s = 0;
      for (i = 0; i < 100000000; i ++)
        s++;
      exit();
    }
  }

  // if(n == N){
  //   printf(1, "fork claimed to work N times!\n", N);
  //   exit();
  // }

  for(; n > 0; n--){
    if(waitSch(&rutime, &retime, &sltime) < 0){
      printf(1, "wait stopped early\n");
      exit();
    }
    printf(1, "rutime = %d, retime = %d, sltime = %d\n", rutime, retime, sltime);
  }

  if(waitSch(&rutime, &retime, &sltime) != -1){
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
