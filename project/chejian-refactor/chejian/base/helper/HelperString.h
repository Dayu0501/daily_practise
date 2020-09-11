#ifndef HELPERSTRING_H
#define  HELPERSTRING_H
#include <string>
#include <stdint.h>
#include <vector>

//#pragma  warning(disable:4996)
namespace hl
{
#ifdef __linux
std::string unicode2utf8(char* src ,size_t len);
std::string gb23122utf8(char* src ,size_t len);
char* utf82unicode(std::string src,size_t& len);
char* utf82gb2312(std::string src,size_t& len);
std::string wstring2string(const std::wstring str);
std::wstring string2wstring(const std::string str);
#else
std::string wchar2ansi(std::wstring src);
std::wstring ansi2wchar(std::string src);
std::string wchar2utf8(std::wstring src);
std::wstring utf82wchar(std::string src);
std::string utf82ansi(std::string src);
std::string ansi2utf8(std::string src);
#endif
std::string urlencode(std::string &sIn);
std::string urldecode(std::string &sIn);
std::string base64encode(unsigned char const*, unsigned int len);
std::string base64decode(std::string const& s);
std::string buf2hex(unsigned char*buf, int bufLen);
uint32_t hex2buf(std::string hex, unsigned char*outBuf);
void strsplit(std::vector<std::string>& lines, std::string src, std::string delims);
std::string strreplace(std::string str, std::string src, std::string dest);
void str2upper(std::string& str, bool bUpper = true);
std::string randomstr(int charNum);
std::string sha1str(std::string str);
std::string md5str(std::string str);
void FindMaxsubstr(const char *strA, const char *strB, char *maxSubStr);

}

#endif
