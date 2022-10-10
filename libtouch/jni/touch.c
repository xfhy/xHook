//
// Created by xfhy on 2022/10/3.
//

#include <jni.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <pthread.h>
#include <android/log.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/prctl.h>
#include <sys/prctl.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "xhook.h"

//获取系统当前时间,单位:毫秒
long getCurrentTime() {
   struct timeval tv;
   gettimeofday(&tv,NULL);
   return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

long lastTime = 0;

ssize_t (*original_sendto)(int sockfd, const void *buf, size_t len, int flags,
                           const struct sockaddr *dest_addr, socklen_t addrlen);
ssize_t my_sendto(int sockfd, const void *buf, size_t len, int flags,
                  const struct sockaddr *dest_addr, socklen_t addrlen) {
    if (getCurrentTime() - lastTime > 5000) {
        __android_log_print(ANDROID_LOG_DEBUG, "xfhy_touch", "Touch有点卡顿");
        //todo xfhy 在这里调用java去dump主线程堆栈
    }
    long ret = original_sendto(sockfd, buf, len, flags, dest_addr, addrlen);
    
    //应用端已消费touch事件
    __android_log_print(ANDROID_LOG_DEBUG, "xfhy_touch", "my_sendto 收到了");

    return ret;
}

ssize_t (*original_recvfrom)(int sockfd, void *buf, size_t len, int flags,
                             struct sockaddr *src_addr, socklen_t *addrlen);
ssize_t my_recvfrom(int sockfd, void *buf, size_t len, int flags,
                    struct sockaddr *src_addr, socklen_t *addrlen) {
    lastTime = getCurrentTime();
    long ret = original_recvfrom(sockfd, buf, len, flags, src_addr, addrlen);

    //收到touch事件
    __android_log_print(ANDROID_LOG_DEBUG, "xfhy_touch", "my_recvfrom 收到了recvfrom");

    return ret;
}

void Java_com_xfhy_touch_TouchTest_start(JNIEnv *env, jclass clazz) {
    xhook_register(".*libinput\\.so$", "__sendto_chk",(void *) my_sendto, (void **) (&original_sendto));
    xhook_register(".*libinput\\.so$", "sendto",(void *) my_sendto, (void **) (&original_sendto));
    xhook_register(".*libinput\\.so$", "recvfrom",(void *) my_recvfrom, (void **) (&original_recvfrom));
}
