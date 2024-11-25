#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

int rand(){
  int buff[1];
  int random = open("/dev/random", O_RDONLY, 0);
  read(random,buff,4);
  close(random);
  if(buff[0] < 0){
    buff[0] *= -1;
  }
  return *buff;
}

int main(){
  printf("%d about to create 2 child processes\n", getpid());
  pid_t fork1;
  fork1 = fork();
  if(fork1<0){
    perror("fork fail");//output to stderr instead of stdout
    exit(1);
  }
  if(fork1 == 0){
    int timer = rand()%5+1;
    printf("%d %dsec\n", getpid(), timer);
    sleep(timer);
    printf("%d finished after %dsec\n", getpid(), timer);
    return timer;
  }
  else{
    pid_t fork2;
    fork2 = fork();
    if(fork2<0){
      perror("fork fail");//output to stderr instead of stdout
      exit(1);
    }
    if(fork2 == 0){
      int timer = rand()%5+1;
      printf("%d %dsec\n", getpid(), timer);
      sleep(timer);
      printf("%d finished after %dsec\n", getpid(), timer);
      return timer;
    }
    else{
      int status;
      int child = wait(&status);
      int timer = WEXITSTATUS(status);
      printf("Main Process %d is done. Child %d slept for %dsec\n", getpid(), child, timer);
    }
  }
  return 0;
}
