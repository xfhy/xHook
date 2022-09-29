#!/bin/bash

adb push ./main/libs/armeabi-v7a/libtest.so ./main/libs/armeabi-v7a/main /data/local/tmp
adb shell "chmod +x /data/local/tmp/main"
adb shell "export LD_LIBRARY_PATH=/data/local/tmp; /data/local/tmp/main"


ndk-build -C ./libtest/jni
ndk-build -C ./main/jni

adb push ./main/libs/x86/libtest.so ./main/libs/x86/main /data/local/tmp
adb shell
chmod +x /data/local/tmp/main
export LD_LIBRARY_PATH=/data/local/tmp; /data/local/tmp/main
