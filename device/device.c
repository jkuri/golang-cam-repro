#include "device.h"

const char *get_device_family()
{
#ifdef _WIN32
  const char *device_family = "dshow";
#elif __APPLE__
  const char *device_family = "avfoundation";
#elif __linux__
  const char *device_family = "v4l2";
#endif

  return device_family;
}

#ifdef _WIN32

#elif __APPLE__
devices_t get_video_devices()
{
  devices_t devs;
  devs.num_devices = 0;
  NSArray *devices = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];

  int index = 0;
  for (AVCaptureDevice *device in devices)
  {
    devs.num_devices++;

    const char *name = [[device localizedName] UTF8String];
    index = [devices indexOfObject:device];

    devs.devices[devs.num_devices - 1].index = index;
    devs.devices[devs.num_devices - 1].name = malloc(30);
    devs.devices[devs.num_devices - 1].num_caps = 0;
    devs.devices[devs.num_devices - 1].name = strdup(name);

    for (AVCaptureDeviceFormat *format in [device formats])
    {
      CMVideoDimensions dimensions = CMVideoFormatDescriptionGetDimensions((CMVideoFormatDescriptionRef)[format formatDescription]);

      for (AVFrameRateRange *range in format.videoSupportedFrameRateRanges)
      {
        devs.devices[devs.num_devices - 1].num_caps++;
        devs.devices[devs.num_devices - 1].caps[devs.devices[devs.num_devices - 1].num_caps - 1].resolution = malloc(30);

        char res[15];
        sprintf(res, "%dx%d", dimensions.width, dimensions.height);
        devs.devices[devs.num_devices - 1].caps[devs.devices[devs.num_devices - 1].num_caps - 1].resolution = strdup(res);
        devs.devices[devs.num_devices - 1].caps[devs.devices[devs.num_devices - 1].num_caps - 1].framerate = range.minFrameRate;
      }
    }
    index++;
  }

  return devs;
}
#elif __linux__
int is_v4l2_device(const char *name)
{
  return !strncmp(name, "video", 5) ||
         !strncmp(name, "radio", 5) ||
         !strncmp(name, "vbi", 3) ||
         !strncmp(name, "v4l-subdev", 10);
}

devices_t get_video_devices()
{
  int fd;
  DIR *dir;
  struct dirent *entry;

  struct v4l2_capability cap;
  struct v4l2_fmtdesc fmt;
  struct v4l2_frmsizeenum frmsize;
  struct v4l2_frmivalenum frmival;

  devices_t *devs;
  devs.num_devices = 0;

  dir = opendir("/dev");
  if (!dir)
  {
    fprintf(stderr, "Could not open /dev directory!\n");
    return devs;
  }

  while ((entry = readdir(dir)))
  {
    char device_name[261];

    if (!is_v4l2_device(entry->d_name)) {
      continue;
    }

    snprintf(device_name, sizeof(device_name), "/dev/%s", entry->d_name);

    if ((fd = open(device_name, O_RDONLY)) == -1)
    {
      continue;
    }

    if (ioctl(fd, VIDIOC_QUERYCAP, &cap) == -1)
    {
      continue;
    }

    devs.num_devices++;
    devs.devices[devs.num_devices - 1].index = devs.num_devices - 1;
    devs.devices[devs.num_devices - 1].device = strdup(device_name);
    devs.devices[devs.num_devices - 1].name = strdup(cap.card);

    fmt.index = 0;
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    while (ioctl(fd, VIDIOC_ENUM_FMT, &fmt) >= 0)
    {
      frmsize.pixel_format = fmt.pixelformat;
      frmsize.index = 0;

      int index = 0;

      while (ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &frmsize) >= 0)
      {
        if (frmsize.type == V4L2_FRMSIZE_TYPE_DISCRETE)
        {
          frmival.index = 0;
          frmival.pixel_format = fmt.pixelformat;
          frmival.width = frmsize.discrete.width;
          frmival.height = frmsize.discrete.height;
          while (ioctl(fd, VIDIOC_ENUM_FRAMEINTERVALS, &frmival) >= 0)
          {
            if (frmival.type == V4L2_FRMIVAL_TYPE_DISCRETE)
            {
              char sec[100], fps[100], res[15], pix_fmt[32];
              sprintf(sec, "%.3f", (1.0 * frmival.discrete.numerator) / frmival.discrete.denominator);
              sprintf(fps, "%.3f", (1.0 * frmival.discrete.denominator) / frmival.discrete.numerator);
              sprintf(res, "%dx%d", frmival.width, frmival.height);
              sprintf(pix_fmt, "%s", fmt.description);

              devs.devices[devs.num_devices - 1].caps[index].resolution = strdup(res);
              devs.devices[devs.num_devices - 1].caps[index].pixel_format = strdup(pix_fmt);
              devs.devices[devs.num_devices - 1].caps[index].framerate = atoi(fps);
              index++;
            }
            frmival.index++;
          }
        }
        frmsize.index++;
      }

      fmt.index++;
    }
  }

  return devs;
}
#endif
