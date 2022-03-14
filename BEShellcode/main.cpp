#include "beshellcode.h"

int thread_main(HMODULE dll) {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);



	//AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);


	printf("本程序根据BE动态shellcode编写而成，仅用于模仿最新BE扫描的内容。 \n");
	printf("By:XkHack   更新时间：2022/2/6 14：30 ");
    printf("开始:\n");
    beshellcode::find_system_threads();
    beshellcode::check_KiUserExceptionDispatcher_hook();
    beshellcode::check_modules();
    beshellcode::function_integrity();
    beshellcode::scan_threads();
    HANDLE handler = beshellcode::add_exception_handler(); //外壳代码被多次调用。钩子将在第一次调用后恢复
    beshellcode::scan_sigs();
	printf("结束:\n");
    system("pause");
    beshellcode::remove_exception_handler(handler);
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(dll, 0);
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  
    DWORD fdwReason,     
    LPVOID lpReserved) 
{

    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)thread_main, hinstDLL, 0, 0);
        break;
    }
    return TRUE;

}
