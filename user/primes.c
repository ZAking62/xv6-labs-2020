#include "kernel/types.h"
#include "user/user.h"

#define RD 0
#define WR 1

// 每个读之前把写关掉，read读到最后就会返回0
// 如果有fork，需要把所有写都关掉才行
int lpipe_first_data(int lpipe[2], int *dst)
{
  if (read(lpipe[RD], dst, sizeof(int)) == sizeof(int))
  {
    printf("prime %d\n", *dst);
    return 0;
  }
  return -1;
}

void transmit_data(int lpipe[2], int rpipe[2], int first)
{
  int data;
  // 从左管道读取数据
  while (read(lpipe[RD], &data, sizeof(int)) == sizeof(int))
  {
    // 将无法整除的数据传递入右管道
    if (data % first)
      write(rpipe[WR], &data, sizeof(int));
  }
  close(lpipe[RD]);
  close(rpipe[WR]);
}

void primes(int lpipe[2])
{
  int first;
  close(lpipe[WR]);
  if (lpipe_first_data(lpipe, &first) == 0)
  {
    int p[2];
    pipe(p);
    // 将无法整除的数据写入右管道
    transmit_data(lpipe, p, first);

    if (fork() == 0)
    {
      primes(p);
    }
    else
    {
      close(p[WR]);
      wait(0);
      close(p[RD]);
    }
  }
  exit(0);
}

int main(int argc, char const *argv[])
{
  int p[2];
  pipe(p);

  for (int i = 2; i <= 35; ++i)
  {
    write(p[WR], &i, sizeof(int));
  }
  if (fork() == 0)
  {
    primes(p);
  }
  else
  {
    // 主动关闭，防止子进程读阻塞
    close(p[WR]);
    wait(0);
    close(p[RD]);
  }

  exit(0);
}