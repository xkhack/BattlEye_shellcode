#include "beshellcode.h"

int thread_main(HMODULE dll) {
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);



	//AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);


	printf("���������BE��̬shellcode��д���ɣ�������ģ������BEɨ������ݡ� \n");
	printf("By:XkHack   ����ʱ�䣺2022/2/6 14��30 ");
    printf("��ʼ:\n");
    beshellcode::find_system_threads();
    beshellcode::check_KiUserExceptionDispatcher_hook();
    beshellcode::check_modules();
    beshellcode::function_integrity();
    beshellcode::scan_threads();
    HANDLE handler = beshellcode::add_exception_handler(); //��Ǵ��뱻��ε��á����ӽ��ڵ�һ�ε��ú�ָ�
    beshellcode::scan_sigs();
	printf("����:\n");
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
