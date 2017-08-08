#pragma once
#define DLL_EXPORT_API extern "C" _declspec(dllexport)
//Function
DLL_EXPORT_API int Add(int a,int b);
class _declspec(dllexport) DLL2
{
public:
	
	int Multiply(int a,int b);
};

