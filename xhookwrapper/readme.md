

- xhook module:里面有libxhook.so,它引入了. 它就是用来操作xhook的那些so的,写了相应的工具类XHook+NativeHandler,初始化+refresh啥的.
- biz module:加载和使用libbiz编译出来的libbiz.so文件,去hook libtest.so里面的log输出
- app module: 引入libtest.so+xhook module+biz module,在MainActivity中
  1. 首先是进行了xhook的初始化
  2. 初始化biz,然后start,然后refresh
  3. 初始化test,然后start,然后refresh