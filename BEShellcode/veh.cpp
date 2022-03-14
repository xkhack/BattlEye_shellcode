#include "veh.h"
std::vector<std::tuple<uintptr_t, BYTE>>checks;
LONG WINAPI veh::be_handler(struct _EXCEPTION_POINTERS* ExceptionInfo) {
	
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT) {
		for (std::vector<std::tuple<uintptr_t, BYTE>>::iterator it = checks.begin(); it != checks.end(); ++it)
		{
			if (std::get<0>(*it) == (uintptr_t)ExceptionInfo->ExceptionRecord->ExceptionAddress) {
				DWORD old;
				VirtualProtect((LPVOID)ExceptionInfo->ContextRecord->Rip, 0x1, PAGE_EXECUTE_READWRITE, &old);
				*(BYTE*)ExceptionInfo->ContextRecord->Rip = 0xC3;
				VirtualProtect((LPVOID)ExceptionInfo->ContextRecord->Rip, 0x1, old, &old);

	

				uintptr_t return_address = *(uintptr_t*)ExceptionInfo->ContextRecord->Rsp;
				MEMORY_BASIC_INFORMATION mbi{ 0 };
				size_t return_length{ 0 };
				if (
					(NtQueryVirtualMemory((HANDLE)-1, (PVOID)return_address, MemoryBasicInformation, &mbi, sizeof(mbi), &return_length) < 0) ||
					mbi.State != MEM_COMMIT ||
					mbi.Type != MEM_IMAGE && mbi.RegionSize > 0x2000 ||
					*(WORD*)return_address == 0x23FF ||
					*(WORD*)return_address == 0x26FF ||
					*(WORD*)return_address == 0x27FF ||
					*(WORD*)return_address == 0x65FF ||
					*(WORD*)return_address == 0xE3FF
					) {

					//��������
					beshellcode::report(beshellcode::report_ids::IllegaleCaller);
				}
			

			}
		}
	
		
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	else if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP) {
		if (ExceptionInfo->ContextRecord->Rip >= 0x8000000000000000) {
			beshellcode::report(beshellcode::report_ids::IllegaleCaller);
		}
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

void veh::add_func(uintptr_t func) {
	if (!func)
	{
		return;
	}
	while (*(BYTE*)func != 0xC3)
		func += 1;

	std::tuple<uintptr_t, BYTE>newcheck{ func, *(BYTE*)func };
	checks.push_back(newcheck);
	DWORD old;
	VirtualProtect((LPVOID)func, 0x1, PAGE_EXECUTE_READWRITE, &old);
	*(BYTE*)func = 0xCC;
	VirtualProtect((LPVOID)func, 0x1, old, &old);
}
