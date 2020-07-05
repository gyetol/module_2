#ifndef MODULE_2_COMMANDFUNC_H
#define MODULE_2_COMMANDFUNC_H

int doRemove(char **srcPath, int len, char **msg);
int doMkdir(char *newPath, char **msg);
int doMove(char **srcPath, int len, char *destPath, char **msg);
int doCopy(char **srcPath, int len, char *destPath, char **msg);
int doRename(char **srcPath, int len, char *destPath, char **msg);
int putSrcPath(char **srcPath, char **msg);
void myflush();

#endif //MODULE_2_COMMANDFUNC_H
