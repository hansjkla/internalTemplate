#define WIN32_MEAN_AND_LEAN
#include <Windows.h>
#include <string>
#include <thread>
#include <libloaderapi.h>
#include <TlHelp32.h>

#define APP "cs2.exe"
#define DLL_NAME "internalTemplate.dll"

using namespace std;

DWORD getProcId(const string procName)
{
	::PROCESSENTRY32 entry = { };
	entry.dwSize = sizeof(::PROCESSENTRY32);
	DWORD procId;

	const auto processSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	while (::Process32Next(processSnapshot, &entry))
	{

		if (!procName.compare(entry.szExeFile))
		{

			procId = entry.th32ProcessID;
			break;
		}
	}

	if (processSnapshot)
	{
		::CloseHandle(processSnapshot);
	}

	return procId;
}

void error(const char* error_title, const char* error_message)
{
	MessageBox(0, error_title, error_message, 0);
	exit(-1);
}

bool fileExists(const string file_name)
{
	struct stat buffer;
	return (stat(file_name.c_str(), &buffer) == 0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	DWORD procId = NULL;
	char dll_path[MAX_PATH];
	const char* dll_name = DLL_NAME;
	const string file_name = APP;

	if (!fileExists(dll_name))
	{
		error("fileExists", "File doesnt exists!");
	}

	if (!GetFullPathName(dll_name, MAX_PATH, dll_path, nullptr))
	{
		error("GetFullPathName", "Unable to get full path!");
	}

	procId = getProcId(file_name);

	if (procId == NULL)
	{
		error("getProcId", "Unable to get the process ID!");
	}

	HANDLE h_proc = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	if (!h_proc)
	{
		error("OpenProcess", "Unable to open process!");
	}

	void* allocatedMemory = VirtualAllocEx(h_proc, nullptr, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	if (!allocatedMemory)
	{
		error("VirtualAllocEx", "Unable to allocate memory in the target process!");
	}

	if (!WriteProcessMemory(h_proc, allocatedMemory, dll_path, MAX_PATH, nullptr))
	{
		error("WriteProcessMemory", "Unable to write process memory!");
	}

	HANDLE h_thread = CreateRemoteThread(h_proc, nullptr, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, allocatedMemory, NULL, nullptr);

	if (!h_thread)
	{
		error("CreateRemoteThread", "Unable to create remote thread!");
	}

	CloseHandle(h_proc);
	VirtualFreeEx(h_proc, allocatedMemory, NULL, MEM_RELEASE);
	return 0;
}
