/*
Copyright (c) 2021 Cong

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#pragma once

#include <tinydir.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>

#ifdef _MSC_VER
#define _FSG_FUNC static __inline
#elif !defined __STDC_VERSION__ || __STDC_VERSION__ < 199901L
#define _FSG_FUNC static __inline__
#else
#define _FSG_FUNC static inline
#endif

#ifdef _MSC_VER
#include <windows.h>
#include <winerror.h>
#include <winreg.h>

	static void _query_reg_key(
		char *out, const HKEY key, const char *keypath, const char *valname)
	{
		HKEY pathkey;
		DWORD pathtype;
		DWORD pathlen;
		LONG res;

		if (ERROR_SUCCESS ==
			RegOpenKeyEx(key, keypath, 0, KEY_QUERY_VALUE, &pathkey))
		{
			if (ERROR_SUCCESS ==
					RegQueryValueEx(
						pathkey, valname, 0, &pathtype, NULL, &pathlen) &&
				pathtype == REG_SZ && pathlen != 0)
			{
				res = RegQueryValueEx(
					pathkey, valname, 0, NULL, (LPBYTE)out, &pathlen);
				if (res != ERROR_SUCCESS)
				{
					out[0] = '\0';
				}
			}
			RegCloseKey(pathkey);
		}
	}
#endif

	_FSG_FUNC
	bool fsg_game_exists(const char *name)
	{
#ifdef _MSC_VER
		char buf[4096];
		buf[0] = '\0';
		_query_reg_key(
			buf, HKEY_CURRENT_USER, "Software\\Valve\\Steam", "SteamPath");
		if (strlen(buf) == 0)
		{
			_query_reg_key(
				buf, HKEY_LOCAL_MACHINE, "Software\\Valve\\Steam",
				"InstallPath");
			if (strlen(buf) == 0)
				return false;
		}
		strcat(buf, "/SteamApps/common/");
		strcat(buf, name);

		tinydir_dir dir;
		if (tinydir_open(&dir, buf) != 0)
		{
			return false;
		}
		tinydir_close(&dir);
		return true;
#else
	return false;
#endif
	}

#ifdef __cplusplus
}
#endif
