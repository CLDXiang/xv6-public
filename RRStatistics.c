#include "types.h"
#include "stat.h"
#include "user.h"

#define N  1000

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
    if(pid == 0)
      exit();
    printf(1, "pid = %d\n", pid);
  }

  if(n == N){
    printf(1, "fork claimed to work N times!\n", N);
    exit();
  }

  for(; n > 0; n--){
    if(waitSch(&rutime, &retime, &sltime) < 0){
      printf(1, "wait stopped early\n");
      exit();
    }
    printf(1, "pid = %d\n", getpid());
    printf(1, "rutime = %d, retime = %d, sltime = %d\n", rutime, retime, sltime);
  }

  printf(1, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n");

  if(waitSch(&rutime, &retime, &sltime) != -1){
    printf(1, "wait got too many\n");
    printf(1, "pid = %d\n", getpid());
    printf(1, "rutime = %d, retime = %d, sltime = %d\n", rutime, retime, sltime);
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
