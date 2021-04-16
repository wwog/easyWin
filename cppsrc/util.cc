#include <stringapiset.h>
#include <string>

std::wstring AnsiToUnicode(const std::string &strAnsi)
{
	int nUnicodeLen = ::MultiByteToWideChar(CP_ACP, 0, strAnsi.c_str(), -1, NULL, 0);
	wchar_t *pUnicode = new wchar_t[nUnicodeLen + 1];
	memset((void *)pUnicode, 0, (nUnicodeLen + 1) * sizeof(wchar_t));

	MultiByteToWideChar(CP_ACP, 0, strAnsi.c_str(), -1, (LPWSTR)pUnicode, nUnicodeLen);
	std::wstring strUnicode;
	strUnicode = (wchar_t *)pUnicode;
	delete[] pUnicode;
	return strUnicode;
}
std::string UnicodeToANSI(const std::wstring &strUnicode)
{
	int nAnsiLen = WideCharToMultiByte(CP_ACP, 0, strUnicode.c_str(), -1, NULL, 0, NULL, NULL);
	char *pAnsi = new char[nAnsiLen + 1];
	memset((void *)pAnsi, 0, (nAnsiLen + 1) * sizeof(char));
	WideCharToMultiByte(CP_ACP, 0, strUnicode.c_str(), -1, pAnsi, nAnsiLen, NULL, NULL);
	std::string strAnsi;
	strAnsi = pAnsi;
	delete[] pAnsi;
	return strAnsi;
}
std::wstring UTF8ToUnicode(const std::string& str)
{
	int nUnicodeLen = ::MultiByteToWideChar(CP_UTF8,0,str.c_str(),-1,NULL,0);
	wchar_t*  pUnicode;
	pUnicode = new wchar_t[nUnicodeLen + 1];
	memset((void*)pUnicode, 0, (nUnicodeLen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8,0,str.c_str(),-1,(LPWSTR)pUnicode,nUnicodeLen);
	std::wstring  strUnicode;
	strUnicode = (wchar_t*)pUnicode;
	delete []pUnicode;
	return strUnicode;
}
std::string UnicodeToUTF8(const std::wstring& strUnicode)
{
	int nUtf8Length = WideCharToMultiByte(CP_UTF8,0,strUnicode.c_str(),-1,NULL,0,NULL,NULL);
	char* pUtf8 = new char[nUtf8Length + 1];
	memset((void*)pUtf8, 0, sizeof(char) * (nUtf8Length + 1));
	WideCharToMultiByte(CP_UTF8,0,strUnicode.c_str(),-1,pUtf8,nUtf8Length,NULL,NULL);
	std::string strUtf8;
	strUtf8 = pUtf8;
	delete[] pUtf8;
	return strUtf8;
}
std::string AnsiToUtf8(const std::string &strAnsi)
{
	std::wstring strUnicode = AnsiToUnicode(strAnsi);
	return UnicodeToUTF8(strUnicode);
}
std::string Utf8ToAnsi(const std::string &strUtf8)
{
	std::wstring strUnicode = UTF8ToUnicode(strUtf8);
	return UnicodeToANSI(strUnicode);
}