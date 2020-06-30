//
// Created by linux on 6/30/20.
//

#ifndef MODULE_2_DIRMANAGER_H
#define MODULE_2_DIRMANAGER_H

void cmd_cd(int ac, char *av[]);
int cmd_mkdir(char * newPath, char * errorMsg);
int cmd_rmdir(char * wannaRemove, char ** errorMsg);
void cmd_cp(int ac, char *av[]);

#endif //MODULE_2_DIRMANAGER_H
