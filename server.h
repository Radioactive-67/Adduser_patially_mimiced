struct user_details {
  char user_name[30];
  int user_id;
  int group_id;
  char comments[50];
  char password[15];
  char directory[36];
  char shell[10];
};

struct shadow {
  char user_name[30];
  char encrypted_password [30];
  int elapsed_days;
  int minimum;
  int maximum;
  int w_days;
  int inactive;
  int expire;
};
void encrypt(char* str);
void shadow_details(const struct user_details *user, struct shadow *user_shadow);
void write_in_passwd(FILE *file, const struct user_details user);
void write_in_shadow(FILE *file, const struct shadow user_shadow);
int check_userID (FILE *fp, int user_id);
int check_username (FILE *fp, char* username);
int check_directory(const char *path);
void generate_path(char *path, char *filename);


