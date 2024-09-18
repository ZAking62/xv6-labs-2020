#include "kernel/types.h"
#include "user/user.h"

#define RD 0
#define WR 1

int main(int argc, char *argv[])
{

  if (argc > 1)
  {
    fprintf(2, "Usage: pingpong\n");
    exit(1);
  }

  int p2c[2];
  int c2p[2];
  pipe(p2c);
  pipe(c2p);

  char buf = '0';

  if (fork() == 0)
  {
    close(p2c[WR]);
    close(c2p[RD]);
    read(p2c[RD], &buf, sizeof(char));
    printf("%d: received ping\n", getpid());
    write(c2p[WR], &buf, sizeof(char));
    close(p2c[RD]);
    close(c2p[WR]);
  }
  else
  {
    close(p2c[RD]);
    close(c2p[WR]);
    write(p2c[WR], &buf, sizeof(char));
    read(c2p[RD], &buf, sizeof(char));
    printf("%d: received pong\n", getpid());
    close(p2c[WR]);
     close(c2p[RD]);
  }
  exit(0);
}
