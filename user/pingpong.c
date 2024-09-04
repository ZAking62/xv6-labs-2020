#include "kernel/types.h"
#include "user/user.h"

#define RD 0
#define WR 1

int
main(int argc, char *argv[])
{

  if(argc > 1){
    fprintf(2, "Usage: pingpong\n");
    exit(1);
  }

    int p2c[2];
    int c2p[2];
    pipe(p2c);
    pipe(c2p);
    printf("%d %d\n", p2c[0], p2c[1]);
    // char buf = '0';

    // if(fork()==0){
    //     read(p1[1], &buf, sizeof(char));
    //     printf("%d: received ping", getpid());
    //     write(p2[0], &buf, sizeof(char));
    // }
    // else{
    //     write(p1[0], &buf, sizeof(char));
    //     read(p2[1], &buf, sizeof(char));
    //     printf("%d: received ping", getpid());
    // }



  exit(0);
}
