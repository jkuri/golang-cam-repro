package device

// VideoCapabilities is a struct representing capabilities of device
type VideoCapabilities struct {
	Resolution  string  `json:"resolution"`
	Framerate   float32 `json:"framerate"`
	PixelFormat string  `json:"pixel_format"`
}

// Device is a struct representing video capture device
type Device struct {
	Index int                 `json:"index"`
	Name  string              `json:"name"`
	Caps  []VideoCapabilities `json:"video_capabilities"`
}
