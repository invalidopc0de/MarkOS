#!/bin/bash

sudo /sbin/losetup /dev/loop0 floppy.img
sudo mount /dev/loop0 /mnt/osdev
sudo cp ../Build/kernel.bin /mnt/osdev/kernel
sudo umount /dev/loop0
sudo /sbin/losetup -d /dev/loop0
