# if-this-doesnt-get-me-out-of-CSE-1222-I-am-annoyed

It's kinda planning. more so ramblings of ideas.

### HTTP Learning.

The goal is not highly optimized performance (its a lot of work) or intuitive functionality like golang (though it would be great). The goal is to get file listing and file downloading via HTTP 1.1, and then adding SSL via openssl later.

### broski connect

Calling it a RAT (remote access tool) implies it is malicious, so I'm going to stick with "broski connect". Only thing that seperates a bad actor and someone helping you is whether they get permission. *I do not condone malignant hacking*.

Milestones:
- [ ] Establish an unauthenticated gRPC connection between a client and server
- [ ]

Dependencies:
```bash
sudo pacman -S base-devel cmake grpc protobuf
```

Building:
```bash
mkdir build && cd build

cmake ..

make -j$(nproc)
```

If clangd is getting annoyed by the generated proto definitions you need to great a symbolic link:
```bash
ln -s build/compile_commands.json .
```
