#!/bin/bash

ndk-build -C ./libxhook/jni
ndk-build -C ./libbiz/jni
ndk-build -C ./libtest/jni
ndk-build -C ./libtouch/jni
