## sysinfo


Add `_sysinfotest` to `UPROGS`` in Makefile
this will instruct the makefile to compile the test program

./grade-lab-syscall will try to run the test program and fail.
```
user/sysinfotest.c:9:7: error: implicit declaration of function ‘sysinfo’; did you mean ‘sinfo’? [-Werror=implicit-function-declaration]
    9 |   if (sysinfo(info) < 0) {
      |       ^~~~~~~
      |       sinfo
cc1: all warnings being treated as errors
make: *** [<builtin>: user/sysinfotest.o] Error 1
```
Now we need to add the syscall sysinfo to the OS.

The first step is to make the syscall available to the user program, by adding the following to `user/user.h`
```c
// user/user.h
struct sysinfo;
int sysinfo(struct sysinfo*)
```
that `int struct(sysinfo is *)` is a prototype function and is implemented by autogenerate assembly code. The piece of code that handles the call from sysinfo on user space to the syscall on kernel space is generated when we add a entry to `user\usys.pl`:
```perl
# user/usys.pl
entry("sysinfo")
```

We also need to add a syscall number to `kernel/syscall.h` or the compilation will fail.
```c
// kernel/syscall.h
#define SYS_sysinfo 23
```

At this point we get no compilation erros, but we have no implementation of the syscall on kernel space.

This will add to prototype function to handle the syscall
```c
// kernel/syscall.c
extern uint64 sys_sysinfo(void);
```
And here we assing the syscall number defined on `SYS_sysinfo` to the prototype function.
```c
[SYS_sysinfo] sys_sysinfo,
```

