#pragma once
#include "includes.h"
#include "../src/conts.h"
#include "../renderes/d3d9/crd3d9.h"
#include "../ext/mihook/minhook.h"
#include "../renderes/opengl/glhook.h"
#include "../renderes/menu/menu.h"
#include "../renderes/d3d11/dx11Hook.h"
#include "../renderes/d3d12/dx12Hook.h"

namespace func
{
	void error(const char* error_title, const char* error_message);

	template <typename T>
	void msg(T value, const char* title)
	{
		std::stringstream string;
		string << "Value: " << std::hex << value;

		MessageBox(0, string.str().c_str(), title, 0);
	}

	bool CreateConsole();

	void unload(const HMODULE instance);

	HWND getGameHWND();

	void DestroyMH();

	uintptr_t FindDMAAddy(const uintptr_t startAddress,const std::vector<unsigned int>);

	bool PatchBytes(BYTE* dst, BYTE* src, unsigned int size);

	bool NopBytes(BYTE* dst, unsigned int size);

	// Create an object with: func::BytePatch* VAR_NAME = new func::BytePatch{ dst, src, size };
	// Delete at the end with delet VAR_NAME;
	class BytePatch
	{
	public:
		bool active;
		BytePatch(BYTE* dst, BYTE* src, unsigned int size);
		~BytePatch();

		bool activate();
		bool deactivate();
		bool toggle();

	private:
		BYTE *originalBytes;
		BYTE *destination;
		BYTE *srcBytes;
		unsigned int size;
	};

	class ByteNop
	{
	public:
		bool active;
		ByteNop(BYTE* dst, unsigned int size);
		~ByteNop();

		bool activate();
		bool deactivate();
		bool toggle();
	private:
		BYTE* originalBytes;
		BYTE* destination;
		unsigned int size;
	};

	char* ScanBasic(char* pattern, char* mask, char* begin, intptr_t size);

	char* ScanInternal(char* pattern, char* mask, char* begin, intptr_t size);
}

