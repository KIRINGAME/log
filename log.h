
//**********************************************************************
// log
//**********************************************************************


#pragma once

#include <stdarg.h>
#include <stdio.h>
#include <thread>

#ifdef _WIN32
#include <Windows.h>   
#endif
#ifdef __ANDROID__
#include <android/log.h>
#endif


namespace cmn_log
{

#define LOG_BUFF_MAX 1024
	char thread_local __UI_LOG_BUFF__[LOG_BUFF_MAX];
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
		printf("[LOG]%s\n", __UI_LOG_BUFF__);
#endif
#ifdef _WIN32
		OutputDebugStringA("[SB]");
		OutputDebugStringA(__LOG__BUFF__);
		OutputDebugStringA("\r\n");

		// mutex the consoletextattribute
		std::unique_lock<std::mutex> lock(mMutex);
		
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		WORD wOldColorAttrs;
		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

		// Save the current color  
		GetConsoleScreenBufferInfo(h, &csbiInfo);
		wOldColorAttrs = csbiInfo.wAttributes;

		// Set the new color  
		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED);
		
		// print
		printf("%s\n", __LOG__BUFF__);

		// Restore the original color  
		SetConsoleTextAttribute(h, wOldColorAttrs);
#endif

#ifdef __ANDROID__
		__android_log_print(ANDROID_LOG_INFO, "[LOG]", __UI_LOG_BUFF__);
#endif
	}
}
#define LOG(...) cmn_log::log(__VA_ARGS__)
//**********************************************************************
