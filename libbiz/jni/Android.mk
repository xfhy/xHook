#源文件在开发树中的位置
LOCAL_PATH := $(call my-dir)

#清除LOCAL_PATH变量之外的LOCAL_XXX变量
include $(CLEAR_VARS)
LOCAL_MODULE            := xhook
LOCAL_SRC_FILES         := $(LOCAL_PATH)/../../libxhook/libs/$(TARGET_ARCH_ABI)/libxhook.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../libxhook/jni
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
#生成的模块名称
LOCAL_MODULE            := biz
#需要编译的文件
LOCAL_SRC_FILES         := biz.c
#会生成依赖关系，当库不存在时会去编译这个库。
LOCAL_SHARED_LIBRARIES  := xhook
#编译器的警告设置参数  -Wall       给出“几乎”所有的编译器警告
LOCAL_CFLAGS            := -Wall -Wextra -Werror
LOCAL_CONLYFLAGS        := -std=c11
#额外的动态链接库
LOCAL_LDLIBS            := -llog
include $(BUILD_SHARED_LIBRARY)
