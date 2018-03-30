## golang-cam-repro

This repository presents bug that is introduced with running `C` code or Objective-C on Darwin but works on Linux with similar request.

## Install

```
go install -i github.com/jkuri/golang-cam-repro
```

Stack trace:

```
fatal: morestack on g0
SIGTRAP: trace trap
PC=0x40542a2 m=4 sigcode=1

goroutine 0 [idle]:
runtime.morestack()
        /usr/local/Cellar/go/1.10/libexec/src/runtime/asm_amd64.s:451 +0x22

goroutine 5 [syscall]:
runtime.cgocall(0x4220280, 0xc42036c420, 0x0)
        /usr/local/Cellar/go/1.10/libexec/src/runtime/cgocall.go:128 +0x64 fp=0xc42036c3f0 sp=0xc42036c3b8 pc=0x40040c4
github.com/jkuri/golang-cam-repro/device._Cfunc_get_video_devices(0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, ...)
        _cgo_gotypes.go:89 +0x59 fp=0xc42036c420 sp=0xc42036c3f0 pc=0x421f1c9
github.com/jkuri/golang-cam-repro/device.GetVideoDevices(0xc420110080, 0x1, 0x9)
        /Users/jan/go/src/github.com/jkuri/golang-cam-repro/device/device_darwin.go:12 +0x4d fp=0xc42052dc28 sp=0xc42036c420 pc=0x421f22d
main.deviceListHandler(0x4312720, 0xc420128000, 0xc420124000)
        /Users/jan/go/src/github.com/jkuri/golang-cam-repro/main.go:17 +0x34 fp=0xc42052dcf0 sp=0xc42052dc28 pc=0x421fed4
net/http.HandlerFunc.ServeHTTP(0x42ca610, 0x4312720, 0xc420128000, 0xc420124000)
        /usr/local/Cellar/go/1.10/libexec/src/net/http/server.go:1947 +0x44 fp=0xc42052dd18 sp=0xc42052dcf0 pc=0x41fa1c4
net/http.(*ServeMux).ServeHTTP(0x4455880, 0x4312720, 0xc420128000, 0xc420124000)
        /usr/local/Cellar/go/1.10/libexec/src/net/http/server.go:2337 +0x130 fp=0xc42052dd58 sp=0xc42052dd18 pc=0x41fbe30
net/http.serverHandler.ServeHTTP(0xc42009b110, 0x4312720, 0xc420128000, 0xc420124000)
        /usr/local/Cellar/go/1.10/libexec/src/net/http/server.go:2694 +0xbc fp=0xc42052dd88 sp=0xc42052dd58 pc=0x41fc93c
net/http.(*conn).serve(0xc4200a4780, 0x4312920, 0xc42011a040)
        /usr/local/Cellar/go/1.10/libexec/src/net/http/server.go:1830 +0x651 fp=0xc42052dfc8 sp=0xc42052dd88 pc=0x41f93d1
runtime.goexit()
        /usr/local/Cellar/go/1.10/libexec/src/runtime/asm_amd64.s:2361 +0x1 fp=0xc42052dfd0 sp=0xc42052dfc8 pc=0x4056d11
created by net/http.(*Server).Serve
        /usr/local/Cellar/go/1.10/libexec/src/net/http/server.go:2795 +0x27b

goroutine 1 [IO wait]:
internal/poll.runtime_pollWait(0x5064f00, 0x72, 0x0)
        /usr/local/Cellar/go/1.10/libexec/src/runtime/netpoll.go:173 +0x57
internal/poll.(*pollDesc).wait(0xc420110018, 0x72, 0x0, 0x0, 0x0)
        /usr/local/Cellar/go/1.10/libexec/src/internal/poll/fd_poll_runtime.go:85 +0x9b
internal/poll.(*pollDesc).waitRead(0xc420110018, 0xffffffffffffff00, 0x0, 0x0)
        /usr/local/Cellar/go/1.10/libexec/src/internal/poll/fd_poll_runtime.go:90 +0x3d
internal/poll.(*FD).Accept(0xc420110000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0)
        /usr/local/Cellar/go/1.10/libexec/src/internal/poll/fd_unix.go:372 +0x1a8
net.(*netFD).accept(0xc420110000, 0xc4200a48a0, 0xc420065da8, 0x4003f98)
        /usr/local/Cellar/go/1.10/libexec/src/net/fd_unix.go:238 +0x42
net.(*TCPListener).accept(0xc42000e030, 0xc420065dd8, 0x4002ef7, 0xc4200a48a0)
        /usr/local/Cellar/go/1.10/libexec/src/net/tcpsock_posix.go:136 +0x2e
net.(*TCPListener).AcceptTCP(0xc42000e030, 0xc420065e20, 0xc420065e28, 0x18)
        /usr/local/Cellar/go/1.10/libexec/src/net/tcpsock.go:246 +0x49
net/http.tcpKeepAliveListener.Accept(0xc42000e030, 0x42ca7a8, 0xc4200a4820, 0x43129e0, 0xc420094db0)
        /usr/local/Cellar/go/1.10/libexec/src/net/http/server.go:3216 +0x2f
net/http.(*Server).Serve(0xc42009b110, 0x4312860, 0xc42000e030, 0x0, 0x0)
        /usr/local/Cellar/go/1.10/libexec/src/net/http/server.go:2770 +0x1a5
net/http.(*Server).ListenAndServe(0xc42009b110, 0xc42009b110, 0x42ca610)
        /usr/local/Cellar/go/1.10/libexec/src/net/http/server.go:2711 +0xa9
net/http.ListenAndServe(0x42b74f4, 0x5, 0x0, 0x0, 0xc420065f78, 0xc42008a058)
        /usr/local/Cellar/go/1.10/libexec/src/net/http/server.go:2969 +0x7a
main.main()
        /Users/jan/go/src/github.com/jkuri/golang-cam-repro/main.go:27 +0x67

goroutine 6 [IO wait]:
internal/poll.runtime_pollWait(0x5064d60, 0x72, 0xc420055868)
        /usr/local/Cellar/go/1.10/libexec/src/runtime/netpoll.go:173 +0x57
internal/poll.(*pollDesc).wait(0xc420110118, 0x72, 0xffffffffffffff00, 0x4310860, 0x441f528)
        /usr/local/Cellar/go/1.10/libexec/src/internal/poll/fd_poll_runtime.go:85 +0x9b
internal/poll.(*pollDesc).waitRead(0xc420110118, 0xc420118000, 0x1000, 0x1000)
        /usr/local/Cellar/go/1.10/libexec/src/internal/poll/fd_poll_runtime.go:90 +0x3d
internal/poll.(*FD).Read(0xc420110100, 0xc420118000, 0x1000, 0x1000, 0x0, 0x0, 0x0)
        /usr/local/Cellar/go/1.10/libexec/src/internal/poll/fd_unix.go:157 +0x1dc
net.(*netFD).Read(0xc420110100, 0xc420118000, 0x1000, 0x1000, 0xc420055978, 0x41f3c5b, 0x428e3e0)
        /usr/local/Cellar/go/1.10/libexec/src/net/fd_unix.go:202 +0x4f
net.(*conn).Read(0xc42000e048, 0xc420118000, 0x1000, 0x1000, 0x0, 0x0, 0x0)
        /usr/local/Cellar/go/1.10/libexec/src/net/net.go:176 +0x6a
net/http.(*connReader).Read(0xc420094f30, 0xc420118000, 0x1000, 0x1000, 0x0, 0x5000000, 0x3)
        /usr/local/Cellar/go/1.10/libexec/src/net/http/server.go:764 +0xf8
bufio.(*Reader).fill(0xc42007e120)
        /usr/local/Cellar/go/1.10/libexec/src/bufio/bufio.go:100 +0x11e
bufio.(*Reader).ReadSlice(0xc42007e120, 0xc420055a0a, 0xc420055ad8, 0x4012216, 0x5007608, 0x0, 0xc420055ab8)
        /usr/local/Cellar/go/1.10/libexec/src/bufio/bufio.go:341 +0x2c
bufio.(*Reader).ReadLine(0xc42007e120, 0xc420126000, 0x100, 0xf8, 0x42ad160, 0x1, 0x1000004456620)
        /usr/local/Cellar/go/1.10/libexec/src/bufio/bufio.go:370 +0x34
net/textproto.(*Reader).readLineSlice(0xc420094f60, 0xc420047c01, 0xc420055ba8, 0x4012ef8, 0x100, 0x42ad160)
        /usr/local/Cellar/go/1.10/libexec/src/net/textproto/reader.go:55 +0x70
net/textproto.(*Reader).ReadLine(0xc420094f60, 0xc420126000, 0x0, 0x0, 0x72)
        /usr/local/Cellar/go/1.10/libexec/src/net/textproto/reader.go:36 +0x2b
net/http.readRequest(0xc42007e120, 0x0, 0xc420126000, 0x0, 0x0)
        /usr/local/Cellar/go/1.10/libexec/src/net/http/request.go:929 +0x8c
net/http.(*conn).readRequest(0xc4200a4820, 0x4312920, 0xc420020280, 0x0, 0x0, 0x0)
        /usr/local/Cellar/go/1.10/libexec/src/net/http/server.go:944 +0x16f
net/http.(*conn).serve(0xc4200a4820, 0x4312920, 0xc420020280)
        /usr/local/Cellar/go/1.10/libexec/src/net/http/server.go:1768 +0x4dc
created by net/http.(*Server).Serve
        /usr/local/Cellar/go/1.10/libexec/src/net/http/server.go:2795 +0x27b

goroutine 7 [IO wait]:
internal/poll.runtime_pollWait(0x5064e30, 0x72, 0xc420044658)
        /usr/local/Cellar/go/1.10/libexec/src/runtime/netpoll.go:173 +0x57
internal/poll.(*pollDesc).wait(0xc420110098, 0x72, 0xffffffffffffff00, 0x4310860, 0x441f528)
        /usr/local/Cellar/go/1.10/libexec/src/internal/poll/fd_poll_runtime.go:85 +0x9b
internal/poll.(*pollDesc).waitRead(0xc420110098, 0xc420116000, 0x1, 0x1)
        /usr/local/Cellar/go/1.10/libexec/src/internal/poll/fd_poll_runtime.go:90 +0x3d
internal/poll.(*FD).Read(0xc420110080, 0xc420116071, 0x1, 0x1, 0x0, 0x0, 0x0)
        /usr/local/Cellar/go/1.10/libexec/src/internal/poll/fd_unix.go:157 +0x1dc
net.(*netFD).Read(0xc420110080, 0xc420116071, 0x1, 0x1, 0x0, 0x0, 0x0)
        /usr/local/Cellar/go/1.10/libexec/src/net/fd_unix.go:202 +0x4f
net.(*conn).Read(0xc42000e040, 0xc420116071, 0x1, 0x1, 0x0, 0x0, 0x0)
        /usr/local/Cellar/go/1.10/libexec/src/net/net.go:176 +0x6a
net/http.(*connReader).backgroundRead(0xc420116060)
        /usr/local/Cellar/go/1.10/libexec/src/net/http/server.go:668 +0x5a
created by net/http.(*connReader).startBackgroundRead
        /usr/local/Cellar/go/1.10/libexec/src/net/http/server.go:664 +0xce

rax    0x17
rbx    0xc420072000
rcx    0x4057d15
rdx    0x0
rdi    0x2
rsi    0x42bbf02
rbp    0x70000f0e1080
rsp    0x70000f0e1070
r8     0x10
r9     0x0
r10    0x7ffeefbff9e0
r11    0x202
r12    0xc3
r13    0x2
r14    0x70000f174031
r15    0x11e8
rip    0x40542a2
rflags 0x202
cs     0x2b
fs     0x0
gs     0x0
exit status 2
```
