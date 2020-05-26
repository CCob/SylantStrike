// SylantStrike.cpp : Hooked API implementations
//

#include "pch.h"
#include "framework.h"
#include "SylantStrike.h"

//Pointer to the trampoline function used to call the original API
pNtProtectVirtualMemory pOriginalNtProtectVirtualMemory = nullptr;

DWORD NTAPI NtProtectVirtualMemory(IN HANDLE ProcessHandle, IN OUT PVOID* BaseAddress, IN OUT PULONG NumberOfBytesToProtect, IN ULONG NewAccessProtection, OUT PULONG OldAccessProtection) {

	//Check to see if the calling application is requesting RWX
	if ((NewAccessProtection & PAGE_EXECUTE_READWRITE) == PAGE_EXECUTE_READWRITE) {
		//It was, so notify the user of naughtly behaviour and terminate the running program
		MessageBox(nullptr, TEXT("You've been a naughty little hax0r, terminating program"), TEXT("Hax0r Detected"), MB_OK);
		TerminateProcess(GetCurrentProcess(), 0xdead1337);
		//Unreachable code
		return 0;
	}

	//No it wasn't, so just call the original function as normal
	return pOriginalNtProtectVirtualMemory(ProcessHandle, BaseAddress, NumberOfBytesToProtect, NewAccessProtection, OldAccessProtection);
}
