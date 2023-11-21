/*
 * open-read.c
 *
 * Simple example of opening and reading to a file.
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
     *
     * the attributes are:
     * - O_RDONLY: open the file for reading
     *
     */
    // FILE *fopen(const char *pathname, const char *mode);
    FILE *fd = fopen("test.txt", "r");
    if (fd < 0) {
        fprintf(stderr, "open error: %s\n", strerror(errno));
        return -1;
    }

    char buffer[128];
    memset(buffer, 0, sizeof(buffer));

    /* read the contents of the file */
    while (!feof(fd)) {
        int bytes_read = fread(buffer, 1, sizeof(buffer) - 1, fd);
        if (bytes_read == 0 && ferror(fd)) {
            fprintf(stderr, "read error: %s\n", strerror(errno));
            return -1;
        }
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }

    /* close the file */
    fclose(fd);

    return 0;
}
