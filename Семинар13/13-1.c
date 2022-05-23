#include <unistd.h>
#include <stdio.h>
 
int main(int argc, char **argv) {
  FILE *file_path;
  char pathname[] = "temp/a";
  if ((file_path = fopen(pathname, "a")) == NULL) {
    printf("ERROR\n");
    return 0;
  }
  char pathname_2[] = "temp/b";
  symlink(pathname, pathname_2);
  
  FILE *current_path;
  int count = 0;
  
  while ((current_path = fopen(pathname_2, "r")) != NULL) {
    ++count;
    strcpy(pathname, pathname_2);
    
    pathname_2[5] = 'a' + 1 + count;
    symlink(pathname, pathname_2);
    fclose(current_path);
  }
  
  printf("%d", count);
  fclose(file_path);
  return 0;
}
