#include <Windows.h>
#include <TlHelp32.h>

#include <iostream>
#include <tchar.h> // _tcscmp
#include <vector>

namespace memory {

	inline HANDLE hProcess = nullptr;
	inline DWORD pID = 0;

	
	
	template <typename  T> void Read(DWORD addr, T* value, int bytes = 4) {
		if (bytes != 4) {
			ReadProcessMemory(hProcess, (BYTE*)addr, value, bytes, nullptr);
			return;
		}
		ReadProcessMemory(hProcess, (BYTE*)addr, value, sizeof(T), nullptr);
	}
	
	template <typename  T> void Write(DWORD addr, T* value) {
		WriteProcessMemory(hProcess, (BYTE*)addr, value, sizeof(T), nullptr);
	}

	//DWORD GetModuleBaseAddress(const std::string moduleName);
	
	DWORD GetModuleBaseAddress(TCHAR* lpszModuleName);

	

}
