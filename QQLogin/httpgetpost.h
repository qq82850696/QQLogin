#pragma once
#include <winsock2.h>
#include<iostream>
#include<string>
#include <sstream>
#include<windows.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
bool GetIpByDomainName(char *szHost, char* szIp){
	WSADATA wsaData;
	HOSTENT *pHostEnt;
	int nAdapter = 0;
	struct sockaddr_in   sAddr;
	if (WSAStartup(0x0101, &wsaData)){
		printf(" gethostbyname error for host:\n");
		return 0;
	}
	pHostEnt = gethostbyname(szHost);
	if (pHostEnt){
		if (pHostEnt->h_addr_list[nAdapter]){
			memcpy(&sAddr.sin_addr.s_addr, pHostEnt->h_addr_list[nAdapter], pHostEnt->h_length);
			sprintf_s(szIp, 256, "%s", inet_ntoa(sAddr.sin_addr));
		}
	}
	else{
		//      DWORD  dwError = GetLastError();
		//      CString  csError;
		//      csError.Format("%d", dwError);
	}
	WSACleanup();
	return 1;
}
string wstring2string(wstring wstr){
	string result;
	//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	//宽字节编码转换成多字节编码  
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}
char* deleteheader(char* ret, unsigned int &len);
string sendRequest(char* ip,u_short port,const char* bufSend,unsigned int&lenth) {
	WSADATA wData;
	::WSAStartup(MAKEWORD(2, 2), &wData);

	SOCKET clientSocket = socket(AF_INET, 1, 0);
	struct sockaddr_in ServerAddr = { 0 };
//	int Ret = 0;
//	int AddrLen = 0;
//	HANDLE hThread = 0;
	char* retdata;
	string encodedata;
	ServerAddr.sin_addr.s_addr = inet_addr(ip);
	ServerAddr.sin_port = htons(port);;
	ServerAddr.sin_family = AF_INET;
	char bufRecv[10240] = { 0 };
	int errNo = 0;
	errNo = connect(clientSocket, (sockaddr*)&ServerAddr, sizeof(ServerAddr));
	if (errNo == 0)
	{
		//如果发送成功，则返回发送成功的字节数;
		if (send(clientSocket, bufSend, strlen(bufSend), 0)>0)
		{
			//cout << bufSend << endl;
			//cout << "发送成功\n"<< endl;
		}
		//如果接受成功，则返回接受的字节数;
		Sleep(100);
		int reclen = 0;
		if ((reclen = recv(clientSocket, bufRecv, sizeof(bufRecv), 0))>0)
		{
			//cout << "接收成功\n"<< endl;
			//下面的代码用于转换编码，否则中文乱码
			retdata =deleteheader(bufRecv, lenth);
			int  unicodeLen = ::MultiByteToWideChar(CP_UTF8, 0, retdata, -1, NULL, 0);
			wchar_t *pUnicode = new  wchar_t[unicodeLen];
			memset(pUnicode, 0, unicodeLen * sizeof(wchar_t));
			::MultiByteToWideChar(CP_UTF8, 0, retdata, -1, (LPWSTR)pUnicode, unicodeLen);
			wstring  rt = pUnicode;
			encodedata = wstring2string(rt);
			//cout << bufRecv << endl;
		}
	}
	else{
		errNo = WSAGetLastError();
		cout << errNo << endl;
	}
	//socket环境清理;
	::WSACleanup();
	return encodedata;
}
string httpheader =
	" HTTP/1.1\r\n"
	"Accept: application/javascript, */*;q=0.8\r\n"
	"Accept-Language: zh-Hans-CN,zh-Hans;q=0.8,en-US;q=0.5,en;q=0.3\r\n"
	"Accept-Encoding: gzip, deflate\r\n"
	"Connection: Keep-Alive\r\n"
	"User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko Core/1.53.2669.400 QQBrowser/9.6.11054.400\r\n"
;
string sendGetRequest(char* host,char* path="", char* param="", u_short port=80) {//GET方式
	
	UNREFERENCED_PARAMETER(param);

	char ip[256] = { 0 };
	GetIpByDomainName(host, ip);//获得IP
	stringstream stream;
	string sp;
	stream >> sp;//将int转为string
	string data = "GET /"+string(path)+ httpheader+"Host:"+host+":"+sp+"\r\n\r\n";
	unsigned int len = 10240;
	return sendRequest(ip, port, data.data(),len);
}
string sendPostRequest(char* host, char* path, char* param, u_short port = 80) {//POST方式
	UNREFERENCED_PARAMETER(param);
	char ip[256] = { 0 };
	GetIpByDomainName(host, ip);
	stringstream stream;
	string sp;
	stream >> sp;
	string data = "POST /" + string(path) + httpheader + "Host:" + host + ":" + sp + "\r\n\r\n";
	unsigned int len = 10240;
	return sendRequest(ip, port, data.data(),len);
}
char* deleteheader(char* ret, unsigned int& len) {//去除首部和缓冲区尾部多余内容
	int i = -1;
	while (!(*(ret + ++i) == '\r'&& *(ret + ++i) == '\n' && *(ret + ++i) == '\r' && *(ret + ++i) == '\n'));
	while (*(ret + ++i) == '\0');
	while (*(ret+ --len)=='\0');
	len = len - i + 1;
	return ret+i;
}