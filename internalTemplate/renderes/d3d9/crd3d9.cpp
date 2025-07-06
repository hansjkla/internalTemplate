#include "crd3d9.h"
#include <exception>

bool crd3d9::d3d9 = false;

bool crd3d9::Create()
{
	try
	{
		gui::Setup();
		hooks::Setup();
	}
	catch (const std::exception& error)
	{
		func::error("Creating d3d9 menu", "Failed...");
		return false;
	}
	d3d9 = true;
	return true;
}
