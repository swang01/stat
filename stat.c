#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void readable_form(long size){
  int i = 1;
  while (size >= 1024){
    size /= 1024;
    ++i;
  }
  if (i == 1){
    printf("File size in readable form: %dB\n",size);
  }
  else if (i == 2){
    printf("File size in readable form: %dKB\n" ,size);
  }
  else if (i == 3){
    printf("File size in readable form: %dMB\n",size);
  }
  else{
    printf("File size in readable form: %dGB\n", size);
  }
}

void print_perms(mode_t mode, char * buff){
  char perms[10] = "rwxrwxrwx";
  int i;
  for (i = 0; i < 9; i++){
    if (!((1 << (8 - i)) & mode)){
      perms[i] = '-';
    }
  }
  strcpy(buff, perms);
  printf("ls -l Permissions: %s\n", buff);
}

int main(){
  struct stat info;
  stat("stat.c", &info);
  int x = info.st_size;
  printf("File size: %d \n", x);
  printf("File permissions: %o \n", info.st_mode);
  printf("Last accessed: %s", ctime(&info.st_atime));
  readable_form(x);
  char perms[10];
  print_perms(info.st_mode, perms);
  return 0;
}
