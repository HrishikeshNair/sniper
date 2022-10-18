/*#include<stdio.h>
#include<time.h>
void main()
{
double meow;
clock_t a1,a2;
a1=clock();
printf("hello\n");
a2=clock();
meow=(double)(a2-a1);
printf("cycles is =%f\n", meow);
}
*/

#include <stdio.h>

int main()
{
  int status;
  int pid = fork();
  int pid2 = fork();
  //int pid3 = fork();
  //int pid4 = fork();

  printf("Hello world from %s\n", pid ? "parent" : "child");

  while(waitpid(-1, &status, 0) > 0);
  return;
}
