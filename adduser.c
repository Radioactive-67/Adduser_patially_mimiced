#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "server.h"

/*

using a to load file 
“a+” – Searches file. If the file is opened successfully fopen( ) loads it into memory and sets up a pointer that points to the last character in it. If the file doesn’t exist, a new file is created. Returns NULL, if unable to open file.
The getenv function obtains the current value of the environment variable, name.
The setenv function inserts or resets the environment variable name in the current environment list. If the variable name does not exist in the list, it is inserted with the given value. If the variable does exist, the argument overwrite is tested; if overwrite is zero, the variable is not reset, otherwise it is reset to the given value

*/

int main(int argc, char **argv) {
  if (argc < 9) {
    printf("Insufficient number of arguments\n");
    printf ("Usage: adduser <-u> <UID> <-g> <GID> <-c> <Comments> <Name>\n");
    exit(1);
  }
  if (strcmp(argv[1], "adduser") != 0) {
    printf("Invalid command\n");
    exit(1);
  }
  setenv("PFILE", "./etc/", 1);
  check_directory(getenv("PFILE"));
  struct user_details user;
  struct shadow user_shadow;
  strcpy(user.password, "PES1UG19CS094");//password is hardcoded as it is not taken as input in the project
  
  strcpy(user.directory, "/user/home");
  strcpy(user.shell,"/bin/bash"); 
  char passwd_path[1000];
  char shadow_path[1000];
  
  generate_path(passwd_path, "passwd.txt");
  generate_path(shadow_path, "shadow.txt");
  
  FILE *passwd = fopen(passwd_path, "a+");
  FILE *shadow = fopen(shadow_path, "a+");
  
  if (check_username(passwd, argv[8]) == 0) {
    exit(1);
  }
 fseek(passwd, 0, SEEK_SET);
 fseek(shadow, 0, SEEK_SET);
  if (check_userID(passwd, atoi(argv[3])) == 0) {
    exit(1);
  }
  user.user_id = atoi(argv[3]);
  user.group_id = atoi(argv[5]);
  strcpy(user.comments, argv[7]);
  strcpy(user.user_name, argv[8]);
  //initialising shadow
  shadow_details(&user, &user_shadow);
  
  write_in_passwd(passwd, user);
  write_in_shadow(shadow, user_shadow);
  
  fclose(passwd);
  fclose(shadow);
  
}
