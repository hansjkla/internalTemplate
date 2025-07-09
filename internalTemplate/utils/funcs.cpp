#include "funcs.h"

void func::error(const char* error_title, const char* error_message)
{
	MessageBox(0, error_message, error_title, 0);
	exit(-1);
}

bool func::CreateConsole()
{
	if (!AllocConsole()) return false; // Create a new console window

	// Redirect stdout to the console
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	freopen_s(&fp, "CONIN$", "r", stdin);

	// Optional: Use C++ streams
	std::cout.clear();
	std::clog.clear();
	std::cerr.clear();
	std::cin.clear();

	std::cout << "Console allocated!\n";
	console = true;
	return true;
}

void func::unload(const HMODULE instance)
{
	uninjecting = true;

    //if (crd3d9::d3d9) gui::Destroy();

	//menuGL::Destroy();

	if (menu::isMenuSetup) menu::Destroy();

	if (MinHook) func::DestroyMH();

	if (console) FreeConsole();

	Sleep(100);
	FreeLibraryAndExitThread(instance, 0);
}

void func::DestroyMH()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

uintptr_t func::FindDMAAddy(const uintptr_t ptr, const std::vector<unsigned int> offsets)
{
	if (!ptr) return NULL;

	uintptr_t addr = ptr;
	for (int i = 0; i < offsets.size(); i++)
	{
		if (!addr)
		{
			func::error("FindDMAAddy", "One of the ptrs is wrong.");
		}

		addr = *(uintptr_t*)addr;

		addr += offsets[i];
	}
	return addr;
}

bool func::PatchBytes(BYTE* dst, BYTE* src, unsigned int size)
{
	DWORD oldProtect;
	if (!VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect))
	{
		return false;
	}

	if (memcpy_s(dst, size, src, size) != 0) return false;

	if (!VirtualProtect(dst, size, oldProtect, &oldProtect))
	{
		return false;
	}
	return true;
}

bool func::NopBytes(BYTE* dst, unsigned int size)
{
	DWORD oldProtect;
	if (!VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect))
	{
		return false;
	}

	memset(dst, 0x90, size);

	if (!VirtualProtect(dst, size, oldProtect, &oldProtect))
	{
		return false;
	}
	return true;
}

char* func::ScanBasic(char* pattern, char* mask, char* begin, intptr_t size)
{
	if (strlen(pattern) == 0 || strlen(mask) == 0 || strlen(begin) == 0 || !size)
	{
		func::error("ScanBasic", "One of the args contains unvalid data.");
	}

	intptr_t patternLen = strlen(mask);

	for (int i = 0; i < size; i++)
	{
		bool found = true;
		for (int j = 0; j < patternLen; j++)
		{
			if (mask[j] != '?' && pattern[j] != *(char*)((uintptr_t)begin + i + j))
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return (begin + i);
		}
	}
	return nullptr;
}

char* func::ScanInternal(char* pattern, char* mask, char* begin, intptr_t size)
{
	char* match{ nullptr };
	MEMORY_BASIC_INFORMATION mbi{};

	for (char* curr = begin; curr < begin + size; curr += mbi.RegionSize)
	{
		if (!VirtualQuery(curr, &mbi, sizeof(mbi)) || mbi.Protect != PAGE_NOACCESS || mbi.State != MEM_COMMIT) continue;

		match = func::ScanBasic(pattern, mask, begin, size);

		if (match != nullptr) break;
	}

	return match;
}

func::BytePatch::BytePatch(BYTE* dst, BYTE* src, unsigned int size)
	: destination(dst), size(size), active(false)
{
	if (size == 0)
		throw std::invalid_argument("Size must be greater than 0.");

	originalBytes = new BYTE[size];
	srcBytes = new BYTE[size];

	if (memcpy_s(originalBytes, size, dst, size) != 0)
		throw std::runtime_error("Failed to copy original bytes.");

	if (memcpy_s(srcBytes, size, src, size) != 0)
		throw std::runtime_error("Failed to copy src bytes.");

	activate();
}

func::BytePatch::~BytePatch()
{
	deactivate();
	delete[] originalBytes;
	delete[] srcBytes;
}

bool func::BytePatch::activate()
{
	if (active) return true;
	active = true;
	return func::PatchBytes(destination, srcBytes, size);
}

bool func::BytePatch::deactivate()
{
	if (!active) return true;
	active = false;
	return func::PatchBytes(destination, originalBytes, size);
}

bool func::BytePatch::toggle()
{
	if (active)
		return deactivate();
	return activate();
}


func::ByteNop::ByteNop(BYTE* dst, unsigned int size)
	: destination(dst), size(size), active(false)
{
	if (size == 0)
		throw std::invalid_argument("Size must be greater than 0.");

	originalBytes = new BYTE[size];

	if (memcpy_s(originalBytes, size, dst, size) != 0)
		throw std::runtime_error("Failed to copy original bytes.");

	activate();
}

func::ByteNop::~ByteNop()
{
	deactivate();
	delete[] originalBytes;
}

bool func::ByteNop::activate()
{
	if (active) return true;
	active = true;
	return func::NopBytes(destination, size);
}

bool func::ByteNop::deactivate()
{
	if (!active) return true;
	active = false;
	return func::PatchBytes(destination, originalBytes, size);
}

bool func::ByteNop::toggle()
{
	if (active)
		return deactivate();
	return activate();
}