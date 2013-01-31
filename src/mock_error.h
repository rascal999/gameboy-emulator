typedef struct
{
   int code;
   char str[512];
} Error;

int exiterror(Error * error);
