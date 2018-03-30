package main

import (
	"encoding/json"
	"net/http"

	"github.com/jkuri/golang-cam-repro/device"
)

// JSONResponse - data structure for common JSON response
type JSONResponse struct {
	Status int         `json:"status"`
	Data   interface{} `json:"data"`
}

func deviceListHandler(w http.ResponseWriter, r *http.Request) {
	devs := device.GetVideoDevices()
	resp := JSONResponse{Status: 200, Data: devs}

	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(http.StatusOK)
	json.NewEncoder(w).Encode(resp)
}

func main() {
	http.HandleFunc("/", deviceListHandler)
	if err := http.ListenAndServe(":7350", nil); err != nil {
		panic(err)
	}
}
