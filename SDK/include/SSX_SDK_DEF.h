#pragma once
#include <string>
using namespace std;


#ifdef SSX_SDK_EXPORTS
#define SSX_SDK_API __declspec(dllexport)
#else
#define SSX_SDK_API __declspec(dllimport)
#endif

typedef void( *CallBackFun)(const char* strJsonData);
