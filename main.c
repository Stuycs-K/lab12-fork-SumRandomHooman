#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int rand(){
  int buff[1];
  int random = open("/dev/random", O_RDONLY, 0);
  read(random,buff,4);
  close(random);
  return *buff;
}

int main
  printf("%d about to create 2 child processes", getpid());
  fork1 = fork();
  if(fork1<0){
    perror("fork fail");//output to stderr instead of stdout
    exit(1);
  }
  if(fork1 == 0){
    int timer = rand()%5+1;
    sleep(timer);
    printf("");
  }
  else{
    fork2 = fork();
    if(fork2<0){
      perror("fork fail");//output to stderr instead of stdout
      exit(1);
    }
    if(fork2 == 0){
      int timer = rand()%5+1;
      sleep(timer);
    }
    else{
      int* status;
      wait(status)
    }
  }
  return 0;
}
