#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char* argv[])
{
  char* filepath = argv[1];
  int returnval;

  // from command line input
  if (argc != 2)
      printf ("Usage: program <filename> \n");

  // checks whether the calling process can access the file
  returnval = access (filepath, F_OK);

  if (returnval == 0)
      printf ("\n %s exists \n", filepath);
  else {
      if (errno == ENOENT)
          printf ("\n %s does not exist\n", filepath);
      else if (errno == EACCES)
          printf ("\n cannot access file %s \n", filepath);
      return 0;
  }

//   ...

int returnvalExtended;

returnvalExtended = access (filepath, R_OK);
if (returnvalExtended == 0) {
    printf("\nCan read from %s\n", filepath);
} else {
    printf("\nCan't read from %s. Sorry!\n", filepath);
}

int returnvalExtended1;

returnvalExtended1 = access (filepath, W_OK);
if (returnvalExtended1 == 0) {
    printf("\nCan write to %s!", filepath);
} else {
    printf("\nCan't write to %s. Darn!", filepath);
}

  return 0;
}
// separated the added bits for readability