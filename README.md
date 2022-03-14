# BattlEye_shellcode
模拟BattlEye扫描的shellcode

-检查符合报告条件的返回地址的异常处理程序

-通过检查内核时间增量来查找隐藏的系统线程

-检测想要捕获异常的钩子（KiUserExceptionDispatcher）

-检测列入黑名单的DLL（+检查导入等）+列入黑名单的驱动程序

-检查重要功能的完整性

-检查本地进程中的所有线程，并找到符合报告条件的RIP

-查找列入黑名单的签名
