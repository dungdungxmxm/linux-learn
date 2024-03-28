#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define MAX_PID 1000000
uid_t userIdFromName(const char *name)
{
    struct passwd *pw;

    if (name == NULL || *name == '\0')
        return -1;

    pw = getpwnam(name);
    if (pw == NULL)
    {
        return -1;
    }

    return pw->pw_uid;
}

char *userNameFromId(uid_t uid)
{
    struct passwd *pw;

    if (uid < 0)
        return NULL;

    pw = getpwuid(uid);
    if (pw == NULL)
    {
        return NULL;
    }

    return pw->pw_name;
}

void printProcessInfo(uid_t uid)
{
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir("/proc/")) == NULL)
    {
        perror("opendir error");
        exit(EXIT_FAILURE);
    }
    else
    {
        while ((entry = readdir(dir)) != NULL)
            if (entry->d_name[0] >= '1' && entry->d_name[0] <= '9')
            {
                char path[1000];
                memset(path, 0, sizeof(path));
                snprintf(path, sizeof(path), "/proc/%s/status", entry->d_name);
                FILE *fd = fopen(path, "r");
                if (fd == NULL)
                {
                    perror("open error");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    char line[1000];
                    char process_name[1000];
                    int pid;
                    while (fgets(line, sizeof(line), fd) != NULL)
                    {
                        if (strncmp(line, "Name:", 5) == 0)
                        {
                            char *p = line + 5;
                            while (isspace(*p))
                                p++;
                            strncpy(process_name, p, sizeof(process_name));
                        }
                        if (strncmp(line, "Pid:", 4) == 0)
                        {
                            char *p = line + 4;
                            while (isspace(*p))
                                p++;
                            pid = atoi(p);
                        }
                        if (strncmp(line, "Uid:", 4) == 0)
                        {
                            char *p = line + 4;
                            while (isspace(*p))
                                p++;
                            uid_t pid_uid = atoi(p);
                            if (pid_uid == uid)
                            {
                                printf("Command name: %s", process_name);
                                printf("PID: %d\n", pid);
                            }
                        }
                    }
                    fclose(fd);
                }
            }

        closedir(dir);
    }
}

int main(int argc, char *argv[])
{
    uid_t uid;
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    uid = userIdFromName(argv[1]);
    if (uid == -1)
    {
        fprintf(stderr, "No such user (%s)\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // printf("User ID: %d\n", uid);
    printProcessInfo(uid);

    exit(EXIT_SUCCESS);
}
