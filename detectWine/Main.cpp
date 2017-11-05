#include <windows.h>
#include <stdio.h>
int main(void)
{
#ifdef _UNICODE
	typedef const char *wine_get_version_func(void);
	static const wchar_t * (CDECL *pwine_get_version)(void);
	HMODULE hntdll = GetModuleHandle(L"ntdll.dll");
#else
	typedef const char *wine_get_version_func(void);
	HMODULE hntdll = GetModuleHandle("ntdll.dll");
#endif // _UNICODE

	if (!hntdll)
	{
		puts("Not running on NT.");
		return 1;
	}

	wine_get_version_func *wine_get_version = (CDECL wine_get_version_func *)GetProcAddress(hntdll, "wine_get_version");
	if (wine_get_version)
	{
		printf("Running on Wine... %s\n", wine_get_version());
	}
	else
	{
		puts("did not detect Wine.");
	}
	
	fflush(stdin);
	getchar();

	return 0;
}