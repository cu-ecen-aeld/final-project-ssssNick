// Description: Tests LCD driver module
//
// Author: Nick Brubaker
//
// References:
//    Checking for sucessful read - LSP textbook

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define DELAY_TIME 3
#define CLEAR_SCREEN "                                                                                "

int main(int argc, char *argv[])
{

  // Setup logging
  openlog("lcd_test.c", LOG_ODELAY, LOG_USER);

  char *writeFile = "/dev/lcd"; // device node
  char *writeStr; // String to write

  // Create file
  int fd = open(writeFile, O_WRONLY | O_CREAT | O_TRUNC, 0666);

  // Check if device node was opened sucessfully
  if(fd == -1)
  {
    syslog(LOG_ERR, "error: couldn't open device");
    close(fd);
    return -1;
  }

  //Test writing and seeking on LCD

  writeStr = CLEAR_SCREEN;
  write(fd, writeStr, strlen(writeStr));

  sleep(DELAY_TIME);

  writeStr = "Writing from beginning";
  write(fd, writeStr, strlen(writeStr));

  sleep(DELAY_TIME);

  lseek(fd, 20, SEEK_SET);
  writeStr = "SEEK_SET to line 2";
  write(fd, writeStr, strlen(writeStr));

  sleep(DELAY_TIME);

  lseek(fd, 2, SEEK_CUR);
  writeStr = "SEEK_CUR to line 3";
  write(fd, writeStr, strlen(writeStr));

  sleep(DELAY_TIME);

  writeStr = CLEAR_SCREEN;
  write(fd, writeStr, strlen(writeStr));

  sleep(DELAY_TIME);

  lseek(fd, 0, SEEK_END);
  writeStr = "SEEK_END wraps around";
  write(fd, writeStr, strlen(writeStr));

  close(fd);
  return 0;

}
