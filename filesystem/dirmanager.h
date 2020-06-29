//
// Created by linux on 6/30/20.
//

#ifndef MODULE_2_DIRMANAGER_H
#define MODULE_2_DIRMANAGER_H

int cmd_mkdir(char * newPath, char ** errorMsg);
int cmd_rmdir(char * wannaRemove, char ** errorMsg);
int cmd_rmdirs(const char *path, int force);
int cmd_mvDir(char * srcDir, char * destDir, char ** errorMsg);
int cmd_cpDir(char * srcDir, char * destDir, char ** errorMsg);
#endif //MODULE_2_DIRMANAGER_H
