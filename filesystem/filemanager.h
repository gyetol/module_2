//
// Created by linux on 6/30/20.
//

#ifndef MODULE_2_FILEMANAGER_H
#define MODULE_2_FILEMANAGER_H

int cmd_fileCp(char * srcStr, char * destStr, char **msg);
int cmd_fileRm(char *srcStr, char **msg);
int cmd_fileMv(char *srcStr, char *destStr, char **msg);
#endif //MODULE_2_FILEMANAGER_H
