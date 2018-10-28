#ifndef SD_FUN_h
#define SD_FUN_h


char SD_init(void);
void SD_command(char command,long int arguman);
char SD_response(void);
char SD_response(void);
char SD_datatoken(void);
char SD_readsector(long int SD_add, char *buf);
char SD_writesector(long int lba, char *buf);
void SD_release(void);





#endif