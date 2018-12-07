#pragma once
#include <string>
#include <exception>
#include <Windows.h>

using std::string;
using std::exception;

#ifndef HTTP_EXCEPTION_H
#define HTTP_EXCEPTION_H
namespace ssx_sdk {
	class HttpException : public exception
	{
	public:
		int exc;
		string msg;
		DWORD err;

	public:
		HttpException(int e, const string str, DWORD er) {
			exc = e;
			msg = str;
			err = er;
		}

		~HttpException() {
		}
	};
}
#endif // !HTTP_EXCEPTION_H
