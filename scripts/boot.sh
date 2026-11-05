#!/usr/bin/env bash
set -euo pipefail

KERNEL="${KERNEL:-$HOME/linux/arch/x86/boot/bzImage}"
INITRD="${INITRD:-$HOME/initramfs.cpio.gz}"

for f in "$KERNEL" "$INITRD"; do
  [[ -f "$f" ]] || { echo "Missing file: $f" >&2; exit 1; }
done

exec qemu-system-x86_64 \
  -kernel "$KERNEL" \
  -initrd "$INITRD" \
  -append "console=ttyS0 init=/init panic=-1" \
  -nographic \
  -no-reboot \
  -monitor none
