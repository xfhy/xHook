#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <jni.h>
#include <android/log.h>
#include "xhook.h"

static int my_system_log_print(int prio, const char* tag, const char* fmt, ...)
{
    va_list ap;
    char buf[1024];
    int r;
    
    snprintf(buf, sizeof(buf), "[%s] %s", (NULL == tag ? "" : tag), (NULL == fmt ? "" : fmt));

    va_start(ap, fmt);
    r = __android_log_vprint(prio, "xhook_system", buf, ap);
    va_end(ap);
    return r;
}

static int my_libtest_log_print(int prio, const char* tag, const char* fmt, ...)
{
    //VA_LIST 是在C语言中解决变参问题的一组宏，所在头文件：#include <stdarg.h>，用于获取不确定个数的参数
    va_list ap;
    //buf是想要输出的内容
    char buf[1024];
    int r;

    //snprintf()，函数原型为int snprintf(char *str, size_t size, const char *format, ...)。
     //将可变参数 “…” 按照format的格式格式化为字符串，然后再将其拷贝至str中。
    snprintf(buf, sizeof(buf), "[%s] %s", (NULL == tag ? "" : tag), (NULL == fmt ? "" : fmt));

    //获取可变参数列表的第一个参数的地址（list是类型为va_list的指针，param1是可变参数最左边的参数）：
    va_start(ap, fmt);

    r = __android_log_vprint(prio, "xhook_libtest_hook", buf, ap);

    //清空va_list可变参数列表：
    va_end(ap);
    return r;
}

void Java_com_qiyi_biz_NativeHandler_start(JNIEnv* env, jobject obj)
{
    (void)env;
    (void)obj;

    //注册hook信息
    //系统的log输出hook成自己的my_system_log_print
    xhook_register("^/system/.*\\.so$",  "__android_log_print", my_system_log_print,  NULL);
    xhook_register("^/vendor/.*\\.so$",  "__android_log_print", my_system_log_print,  NULL);
    //libtest.so的log输出hook成自己的my_libtest_log_print
    xhook_register(".*/libtest\\.so$", "__android_log_print", my_libtest_log_print, NULL);

    //just for testing
    //忽略部分hook信息
    xhook_ignore(".*/liblog\\.so$", "__android_log_print"); //ignore __android_log_print in liblog.so
    xhook_ignore(".*/libjavacore\\.so$", NULL); //ignore all hooks in libjavacore.so
}
