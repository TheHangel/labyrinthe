#include "file.h"

char* get_project_root_path(const char *filename) {
    static char path[256];
    strcpy(path, __FILE__);
    dirname(path);
    strcat(path, "/");
    strcat(path, filename);
    return path;
}
