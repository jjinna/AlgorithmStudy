#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv){
    int gpio;
    
    gpio = atoi(argv[1]);

    int fd;
    char buf[BUFSIZ];

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd == -1) {
        printf("open Failed! \n");
    }
    sprintf(buf, "%d", gpio);
    if (write(fd, buf, strlen(buf)) == -1) {
        printf("write Error\n");
    }
    close(fd);

    sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);
    fd = open(buf, O_WRONLY);
    if (fd == -1) {
        printf("open Failed! \n");
    }
    if (write(fd, "out", 4)) {
        printf("write Error\n");
    }
    
    close(fd);

    sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);
    fd = open(buf, O_WRONLY);
    if (fd == -1) {
        printf("open Failed! \n");
    }
    
    if (write(fd, "1", 2) == -1) {
        printf("write Error\n");
    }
    close(fd);

    getchar();

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd == -1) {
        printf("open Failed! \n");
    }
    sprintf(buf, "%d", gpio);
    if (write(fd, buf, strlen(buf))) {
        printf("Write Error\n");
    }
    close(fd);

    return 0;
}