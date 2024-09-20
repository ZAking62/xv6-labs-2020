#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

// char *
// fmtname(char *path)
// {
//     static char buf[DIRSIZ + 1];
//     char *p;

//     // Find first character after last slash.
//     for (p = path + strlen(path); p >= path && *p != '/'; p--)
//         ;
//     p++;

//     // Return blank-padded name.
//     if (strlen(p) >= DIRSIZ)
//         return p;
//     memmove(buf, p, strlen(p));
//     memset(buf + strlen(p), ' ', DIRSIZ - strlen(p));
//     return buf;
// }

// void ls(char *path)
// {
//     char buf[512], *p;
//     int fd;
//     struct dirent de;
//     struct stat st;

//     if ((fd = open(path, 0)) < 0)
//     {
//         fprintf(2, "ls: cannot open %s\n", path);
//         return;
//     }

//     if (fstat(fd, &st) < 0)
//     {
//         fprintf(2, "ls: cannot stat %s\n", path);
//         close(fd);
//         return;
//     }

//     switch (st.type)
//     {
//     case T_FILE:
//         printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);
//         break;

//     case T_DIR:
//         if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
//         {
//             printf("ls: path too long\n");
//             break;
//         }
//         strcpy(buf, path);
//         p = buf + strlen(buf);
//         *p++ = '/';
//         while (read(fd, &de, sizeof(de)) == sizeof(de))
//         {
//             if (de.inum == 0)
//                 continue;
//             memmove(p, de.name, DIRSIZ);
//             p[DIRSIZ] = 0;
//             if (stat(buf, &st) < 0)
//             {
//                 printf("ls: cannot stat %s\n", buf);
//                 continue;
//             }
//             printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
//         }
//         break;
//     }
//     close(fd);
// }

char *
fmtname(char *path)
{
    static char buf[DIRSIZ + 1];
    char *p;

    // Find first character after last slash.
    for (p = path + strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;

    // Return blank-padded name.
    if (strlen(p) >= DIRSIZ)
        return p;
    memmove(buf, p, strlen(p));
    memset(buf + strlen(p), ' ', DIRSIZ - strlen(p));
    return buf;
}

void find(char *path, char *file_name)
{

    char buf[512];
    int fd;
    // struct dirent de;
    struct stat st;
    // char *child_path;
    // int path_num;
    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    if (st.type != T_DIR)
    {
        printf("find: not a path\n");
        close(fd);
        return;
    }

    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
    {
        printf("find: path too long\n");
        close(fd);
        return;
    }


    // while (read(fd, &de, sizeof(de)) == sizeof(de))
    // {
    //     if (de.inum == 0)
    //         continue;
    //     memmove(p, de.namef, DIRSIZ);
    //     p[DIRSIZ] = 0;
    //     if (stat(buf, &st) < 0)
    //     {
    //         printf("ls: cannot stat %s\n", buf);
    //         continue;
    //     }
    //     printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
    // }
    // for (int i = 0; i < path_num; i++)
    // {
    //     ls(child_path[i], file_name);
    // }
    printf("find success\n");
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(2, "Usage: find path file\n");
        exit(1);
    }
    find(argv[1], argv[2]);
    exit(0);
}