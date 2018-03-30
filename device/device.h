#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#ifdef _WIN32

#elif __APPLE__
#import <AVFoundation/AVFoundation.h>
#elif __linux__
#include <linux/videodev2.h>
#endif

typedef struct video_capabilities_t
{
  const char *resolution;
  const char *pixel_format;
  float framerate;
} video_capabilities_t;

typedef struct device_t
{
  int index;
  const char *device;
  const char *name;
  video_capabilities_t caps[500];
  int num_caps;
} device_t;

typedef struct devices_t
{
  device_t devices[50];
  int num_devices;
} devices_t;

static const char *get_device_family();
devices_t get_video_devices();
