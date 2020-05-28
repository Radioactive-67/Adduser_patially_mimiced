#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "server.h"

// encrypts password
void encrypt(char* str) {
  char temp;
  temp = str[0];
  int len = strlen(str);
  for(int i=0;i<len-1;i++) {
    str[i] = str[i+1];
    if(i==len-2) {
      str[i+1] = temp;
  }
  }
}

void shadow_details(const struct user_details *user, struct shadow *user_shadow) {
    strcpy (user_shadow->user_name, user->user_name);
    strcpy (user_shadow->encrypted_password, user->password);
    encrypt (user_shadow->encrypted_password);
    user_shadow->elapsed_days = 56;
    user_shadow->minimum = 9;
    user_shadow->maximum = 5000;
    user_shadow->w_days = 5;
    user_shadow->inactive = 5;
    user_shadow->expire = 1000;
}

// This function writes in passwd.txt
void write_in_passwd(FILE *file, const struct user_details user) {
  fseek (file, 0, SEEK_END);
  fprintf(file, "%s:x:%d:%d:%s:%s:%s\n",user.user_name,user.user_id,user.group_id,user.comments,user.directory,user.shell);
}

// This function writes in shadow.txt 
void write_in_shadow(FILE *file, const struct shadow user_shadow) {
  fseek (file, 0, SEEK_END);
  fprintf(file, "%s:%s:%d:%d:%d:%d:%d:%d\n", user_shadow.user_name, user_shadow.encrypted_password, user_shadow.elapsed_days, user_shadow.minimum, user_shadow.maximum, user_shadow.w_days, user_shadow.inactive, user_shadow.expire);
}

//to check userID
int check_userID (FILE *fp, int user_id) {
    char *temp; 
    char Line [100];
    int count = 0;
    int uid = 0;
    while (1) {
        if (fgets (Line, 99, fp) == NULL){
            return 2;
            }
        temp = strtok (Line, ":");
        temp = strtok (NULL, ":");
        temp = strtok (NULL, ":");
        uid = atoi (temp);
        if (uid == user_id)
        {   
            count = 1;
	          printf("UserID already exists!\n");
            return 0;
        }
    }
    return count;
}

//to check username
int check_username (FILE *fp, char* username) {
    char *temp; 
    char Line [100];
    int count = 0;
    char uname[30];

    while (1)
    {
        if (fgets (Line, 99, fp) == NULL)
            return 2;
        temp = strtok (Line, ":");
        strcpy (uname, temp);
        if (strcmp (uname, username) == 0)
        {   
            count = 1;
            printf("Username already exists!\n");
            return 0;
        }
    } 
    return count;
}



// checks the path of the direcory 
int check_directory(const char *path) {
    struct stat stats;

    stat(path, &stats);

    // Check for dir existence
    if (S_ISDIR(stats.st_mode))
        return 1;

    else{
      char* dirname = "etc";
      
      mkdir(dirname,0777);
      return 1; 
    };
}


// getenv gets the value of the environment variable
// generate_path returns the path of the file after using the information from the environment variable PFILE

void generate_path(char *path, char *filename) {
  if (getenv("PFILE") == NULL) {
    return;
  }
  else {
    strcpy(path, getenv("PFILE"));
    strcat(path, filename);
  }
}
