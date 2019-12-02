#include "header.h"
#include <sys/stat.h>
off_t fsize(const char *filename);

int main (int argc, char **argv) {

    int filedesc = open("ANNA_KARENINA.txt",  O_RDONLY);
    //printf("%lu",fsize("ANNA_KARENINA.txt"));
    unsigned char buffer[fsize("ANNA_KARENINA.txt")];
    if (filedesc == -1)
    {
       printf("\nFile Open Unsuccessful\n");
       exit (0);;
    }

    int bytes_read;
    unsigned long k=0;
    char c;
      while ((bytes_read = read(filedesc, buffer, 1)) != 0) {
        //printf("working till now:%lu \n" ,k);
        c = buffer[0];
        if (islower(c)) {
          c = toupper(c);
        } else if (isupper(c)) {
          c = tolower(c);
        }
        if(bytes_read <= 0 || buffer[0] == '\n' && buffer[0] == '\0') {
          close(filedesc);
        }
        if (bytes_read == -1) {
          printf("failed");
        }

        buffer[(k++)+1] = c;
        
    }
    printf("%s",buffer);
    filedesc = open("ANNA_KARENINA.txt", O_WRONLY);
    write(filedesc, buffer, k);
    close(filedesc);
    return 0;
}


off_t fsize(const char *filename) {
    struct stat st;

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1;
}
