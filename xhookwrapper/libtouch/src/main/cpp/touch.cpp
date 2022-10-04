#include <jni.h>
#include <string>
#include <sys/utsname.h>
#include <unistd.h>
#include <pthread.h>
#include <android/log.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/prctl.h>
#include <sys/prctl.h>
#include <sys/resource.h>

#include <cstdio>
#include <ctime>
#include <csignal>
#include <thread>
#include <memory>
#include <string>
#include <optional>
#include <sstream>
#include <fstream>

#include "xhook.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_xfhy_touch_NativeLib_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



ssize_t (*original_sendto)(int sockfd, const void *buf, size_t len, int flags,
                           const struct sockaddr *dest_addr, socklen_t addrlen);
ssize_t my_sendto(int sockfd, const void *buf, size_t len, int flags,
                  const struct sockaddr *dest_addr, socklen_t addrlen) {

    long ret = original_sendto(sockfd, buf, len, flags, dest_addr, addrlen);

    //todo xfhy 打印日志  "my_sendto 收到了"
    __android_log_print(ANDROID_LOG_DEBUG, "xfhy_touch", "my_sendto 收到了");

    return ret;
}

ssize_t (*original_recvfrom)(int sockfd, void *buf, size_t len, int flags,
                             struct sockaddr *src_addr, socklen_t *addrlen);
ssize_t my_recvfrom(int sockfd, void *buf, size_t len, int flags,
                    struct sockaddr *src_addr, socklen_t *addrlen) {
    long ret = original_recvfrom(sockfd, buf, len, flags, src_addr, addrlen);

    //todo xfhy 打印日志  "my_recvfrom 收到了recvfrom"
    __android_log_print(ANDROID_LOG_DEBUG, "xfhy_touch", "my_recvfrom 收到了recvfrom");

    return ret;
}

extern "C" JNIEXPORT void JNICALL Java_com_xfhy_touch_TouchTest_start(JNIEnv* env, jobject /* this */)
{

    xhook_register(".*libinput\\.so$", "__sendto_chk",(void *) my_sendto, (void **) (&original_sendto));
    xhook_register(".*libinput\\.so$", "sendto",(void *) my_sendto, (void **) (&original_sendto));
    xhook_register(".*libinput\\.so$", "recvfrom",(void *) my_recvfrom, (void **) (&original_recvfrom));

}