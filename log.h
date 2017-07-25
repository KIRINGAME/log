
//**********************************************************************
// log
//**********************************************************************


#pragma once

#include <stdarg.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>   
#endif
#ifdef __ANDROID__
#include <android/log.h>
#endif


namespace cmn_log
{

#define LOG_BUFF_MAX 1024
	char __UI_LOG_BUFF__[LOG_BUFF_MAX];
	void log(const char *format, ...)
	{
		va_list ap;
		va_start(ap, format);
#ifdef _WIN32
		_vsnprintf_s(__UI_LOG_BUFF__, LOG_BUFF_MAX, format, ap);
#else
		vsnprintf(__UI_LOG_BUFF__, LOG_BUFF_MAX, format, ap);
#endif
		va_end(ap);

#ifdef __APPLE__
		printf("[SB]%s\n", __UI_LOG_BUFF__);
#endif
#ifdef _WIN32
		OutputDebugStringA("[SB]");
		OutputDebugStringA(__UI_LOG_BUFF__);
		OutputDebugStringA("\r\n");
#endif

#ifdef __ANDROID__
		__android_log_print(ANDROID_LOG_INFO, "SB", __UI_LOG_BUFF__);
#endif
	}
}
#define LOG(...) cmn_log::log(__VA_ARGS__)
//**********************************************************************
