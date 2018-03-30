// +build darwin
package device

// #cgo CFLAGS: -x objective-c
// #cgo LDFLAGS: -framework Foundation -framework AVFoundation -framework CoreMedia
// #include "device.h"
import "C"

// GetVideoDevices returns all connected devices
func GetVideoDevices() []Device {
	var devices []Device
	devicesList := C.get_video_devices()

	for _, device := range devicesList.devices {
		if C.GoString(device.name) != "" {
			var videoCapabilities []VideoCapabilities
			d := Device{Index: int(device.index), Name: C.GoString(device.name)}
			for _, vc := range device.caps {
				if C.GoString(vc.resolution) != "" && float32(vc.framerate) > 0 {
					pixelFormat := "uyuyv422" // hardcode pixelformat for now, since we'll not be deploying on darwin
					videoCapabilities = append(videoCapabilities, VideoCapabilities{Resolution: C.GoString(vc.resolution), Framerate: float32(vc.framerate), PixelFormat: pixelFormat})
				}
			}
			d.Caps = videoCapabilities

			devices = append(devices, d)
		}
	}

	return devices
}
