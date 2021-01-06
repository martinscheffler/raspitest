#include "setuptouchscreen.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
#include <dirent.h>
#include <qdebug.h>

#define DEVICE_NAME "ADS7846 Touchscreen"
#define INPUT_PATH "/dev/input"

// got these values from file https://github.com/goodtft/LCD-show/blob/master/usr/99-calibration.conf-5-0
#define X_MIN 140
#define X_MAX 3951
#define Y_MIN 261
#define Y_MAX 3998

int setupTouchScreen() {


    DIR* directory = opendir(INPUT_PATH);
    if (!directory) {
        qDebug("setupTouchScreen:: Failed to open %s.", INPUT_PATH);
        return -1;
    }

    bool found = false;
    struct dirent *entry = NULL;
    while (!found && (entry = readdir(directory))) {

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char pathname[NAME_MAX + 1];   /* should always be big enough */
        sprintf( pathname, "%s/%s", INPUT_PATH, entry->d_name );
        qDebug("setupTouchScreen:: Path name: %s",  entry->d_name);
        int fd = open(pathname, O_RDONLY);

        if (fd == NULL) {
            puts ("setupTouchScreen:: Could not open device file - are you running as root");
        }
        else
        {

            char name[256] = "Unknown";
            ioctl (fd, EVIOCGNAME(sizeof(name)), name);
            qDebug("setupTouchScreen:: Input device name: %s", name);
            if(strcmp(name, DEVICE_NAME ) != 0 ) {
                qDebug("setupTouchScreen:: This is not the event file of the touchscreen: %s. Value is: %s", DEVICE_NAME, name);

            } else {
                qDebug("setupTouchScreen:: Found input file!");
                found = true;

                struct input_absinfo absval;

                // Read the ioctl and display the current values
                qDebug("setupTouchScreen:: Writing event struct ABS_X");
                ioctl(fd, EVIOCGABS(ABS_X), &absval);

                // check if a write is wanted - and do it

                absval.minimum = X_MIN;
                absval.maximum = X_MAX;

                ioctl(fd, EVIOCSABS(ABS_X), &absval);

                /////////////////
                qDebug("setupTouchScreen:: Writing event struct ABS_Y");
                ioctl(fd, EVIOCGABS(ABS_Y), &absval);

                absval.minimum = Y_MIN;
                absval.maximum = Y_MAX;

                ioctl(fd, EVIOCSABS(ABS_Y), &absval);

            }
        }
        close(fd);

    }
    closedir(directory);
    if(!found)
    {
        qDebug("setupTouchScreen:: Could not find device file for device %s", DEVICE_NAME);
        return -1;
    }
    qDebug("setupTouchScreen:: Success!");
    return 0;
}
