// Test that fork fails gracefully.
// Tiny executable so that the limit can be filling the proc table.

#include "types.h"
#include "stat.h"
#include "user.h"

void
RRStatistics(void)
{
  printf(1, "RRStatistics start\n");
  int rutime = 0, retime = 0, sltime = 0;
  int res;
  res = waitSch(&rutime, &retime, &sltime);
  printf(1, "res = %d, rutime = %d, retime = %d, sltime = %d\n", res, rutime, retime, sltime);

  printf(1, "RRStatistics end\n");
}

int
main(void)
{
  RRStatistics();
  exit();
}
