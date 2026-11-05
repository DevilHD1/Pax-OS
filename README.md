# Pax OS

A Linux-based operating system I built and booted myself: a kernel compiled
from source, a hand-written PID-1 init program in C, and a minimal root
filesystem — running in QEMU.

Built by Devilition(Peter), age 15. First boot: 5 November 2026.

## What this actually is

Pax OS is three pieces:

1. **A Linux kernel compiled from source** (kernel.org tree)
2. **`init` — my own PID-1 init program**, written in C from scratch:
   - talks to the kernel via raw syscalls (`write`, `mount`, `execve`)
   - mounts `/proc` and `/sys`
   - hands control over to a shell
   - includes a fallback loop so PID-1 never exits
3. **An initramfs** — a minimal root filesystem packed as a cpio archive,
   containing only `init` and busybox

## Boot it

Requirements: Linux, `qemu-system-x86_64`, a compiled kernel (`bzImage`).

    ./scripts/boot.sh

or:

    qemu-system-x86_64 -kernel <path-to>/bzImage \
      -initrd initramfs.cpio.gz -append "console=ttyS0" -nographic

You'll see the kernel boot, then:

    Hello, world!

printed by my init running as the first process, followed by a busybox shell.

## Build init from source

    gcc -static -o init init/init.c
    file init   # must say: statically linked

## Build the initramfs

Copy `init` and busybox into the tree, make them executable, then:

    cd initramfs-root
    find .   cpio -o -H newc | gzip > ../initramfs.cpio.gz

## What I learned building this

- How a Linux system boots: kernel → initramfs → /init (PID 1) → shell
- Why init must be statically linked (hint: at boot, there are no libraries yet)
- Syscalls: `write`, `mount`, `execve` — and why `execve` *replaces* your program
- Reading kernel panics like error messages, not like disasters

## Roadmap

- [x] Compile and boot my own kernel
- [x] Hand-written init + busybox shell
- [ ] Read /proc and understand what the kernel exposes
- [ ] First loadable kernel module (kernelspace!)
- [ ] Contribute a patch to the real Linux kernel
