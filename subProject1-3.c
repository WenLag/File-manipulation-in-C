#include "header.h"

int main(int argc, char **argv) {
  int filedesc;
  char c;
  filedesc = open("ANNA_KARENINA.txt",O_RDWR, (mode_t)0600);
  if (filedesc == -1)
  {
      perror("Error opening file for writing");
      exit(EXIT_FAILURE);
  }
  struct stat fileInfo = {0};
  if (fstat(filedesc, &fileInfo) == -1)
   {
       perror("Error getting the file size");
       exit(EXIT_FAILURE);
   }
   if (fileInfo.st_size == 0)
  {
      fprintf(stderr, "Error: File is empty, nothing to do\n");
      exit(EXIT_FAILURE);
  }
  printf("size is %ji\n", (__intmax_t)fileInfo.st_size);
  if (lseek(filedesc, (__intmax_t)fileInfo.st_size, SEEK_SET) == -1)
    {
        close(filedesc);
        perror("Error calling lseek() to 'stretch' the file");
        exit(EXIT_FAILURE);
    }
  char *map = (mmap(0, fileInfo.st_size, PROT_READ | PROT_WRITE , MAP_SHARED, filedesc, 0));
  if (map == MAP_FAILED)
    {
        close(filedesc);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }

    for (off_t i = 0; i < fileInfo.st_size; i++)
      {

        if(isupper(map[i])) {
        map[i] = tolower(map[i]);
      } else if (islower(map[i])) {
          map[i] = toupper(map[i]);
        }

      }
      printf("%s",map);
      filedesc = open("ANNA_KARENINA.txt", O_WRONLY);
      write(filedesc,map,fileInfo.st_size);
      if (msync(map, fileInfo.st_size, MS_SYNC) == -1)
    {
        perror("Could not sync the file to disk");
    }


      if (munmap(map, fileInfo.st_size) == -1)
    {
        close(filedesc);
        perror("Error un-mmapping the file");
        exit(EXIT_FAILURE);
    }

    // Un-mmaping doesn't close the file, so we still need to do that.
    close(filedesc);


  return 0;
}
