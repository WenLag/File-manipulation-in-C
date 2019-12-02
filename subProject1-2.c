#include "header.h"

int main(int argc, char **argv) {
  char *buffer;
  size_t result;
  long lSize;
  char c;
  FILE* filePointer = fopen("ANNA_KARENINA.txt", "r");

  if (filePointer == NULL) {
    printf("can't open\find file!\n");
    return 1;
  }
  fseek(filePointer , 0 , SEEK_END);
  lSize = ftell(filePointer);
  rewind(filePointer);
  buffer = (char*) malloc (sizeof(char)*lSize);
  if (buffer == NULL) {
    fputs ("Memory error",stderr); exit (2);
  }
  //changing from letters from lower to upper/ upper to lower
  for (int i = 0; i < lSize; i++) {
    // reading from the file one char at a time
    result = fread(buffer,1,1,filePointer);
    c = buffer[0];

    if (isupper(c)) {
      c = tolower(c);

    } else if (islower(c)) {
      c = toupper(c);
    }
      buffer[i+1] = c;
  }
  printf("%s",buffer);
  filePointer = fopen("ANNA_KARENINA.txt","w");
  // rewriting to file changing file each execution.
  fwrite(buffer,sizeof(buffer[0]),lSize,filePointer);
  fclose(filePointer);

  return 0;
}
