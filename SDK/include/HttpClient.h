#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <WINSOCK2.H>   

#ifdef WIN32
#pragma comment(lib,"ws2_32.lib")
#endif

using namespace std;

#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H
namespace ssx_sdk {
	class HttpClient
	{
	public:
		HttpClient();
		~HttpClient();

		string post(string & url, string & dataStr);
		string multForm(string & url, string & dataStr,string &filePath);
		string uploadFile(string & url, string & dataStr, string &filePath);
		string get(string & url, string & dataStr);
	private:

	};
}

#endif // !HTTP_CLIENT_H

