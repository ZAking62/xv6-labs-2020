#include "kernel/types.h"
#include "user/user.h"


#define RD 0
#define WR 1

int main(int argc, char *argv[])
{

  if (argc > 1)
  {
    fprintf(2, "Usage: primes\n");
    exit(1);
  }

  int p[2];
  pipe(p);


  exit(0);
}