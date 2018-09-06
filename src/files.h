
typedef struct file_read
{
  char *buf;
  int size;
} file_read;

file_read read_file(char *filename);