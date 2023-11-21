/*
 * open-write.c
 *
 * Simple example of opening and writing to a file.
 *
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    /*
     * the attributes are:
     * - O_CREAT: create the file if it does not exist
     * - O_TRUNC: erase the contents of the file
     * - O_WRONLY: open the file for writing
     *
     * the permissions are applied if the file is created:
     * - S_IRUSR: reading, user
     * - S_IWUSR: writing, user
     */

    FILE *fd = fopen("test.txt", "w");
    if (fd < 0) {
        fprintf(stderr, "open error: %s\n", strerror(errno));
        return -1;
    }

    char buffer[] = "Hello World!\n";

    /* write a string to the file */
    int len = strlen(buffer);
    int done = 0;
    while (len > 0) {
        int bytes_written = fwrite(buffer + done, 1, len, fd);
        if (bytes_written < 0) {
            fprintf(stderr, "write error: %s\n", strerror(errno));
            return -1;
        }

        /* might not have managed to write all, len becomes what remains */
        len -= bytes_written;
        done += bytes_written;
    }

    /* close the file */
    fclose(fd);

    return 0;
}
