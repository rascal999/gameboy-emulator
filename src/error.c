#include <stdio.h>
#include <stdlib.h>

#include "error.h"

int exiterror(Error * error)
{
   switch(error->code)
   {
      case 2:
         printf("Error 1: Cannot open file\n");
         exit(2);
      break;

      case 3:
         printf("Error 3: Error reading from file\n");
         exit(3);
      break;

      case 4:
         printf("Specify rom file\n");
         printf("Error 4: Incorrect number of arguments\n");
         exit(4);
      break;

      case 20:
         printf("Error 20: Missing opcode\n");
         exit(20);
      break;

      case 30:
         printf("Error 30: Unaddressable location\n");
         exit(30);
      break;
   }

   return 1;
}
