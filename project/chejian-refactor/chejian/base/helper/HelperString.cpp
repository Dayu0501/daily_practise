#include "HelperString.h"
#include <algorithm>
#include <memory.h>
#ifdef __linux
#include <iconv.h>
#else
#include <windows.h>
#endif

namespace hl
{
#define CODE_CONVERT_OUT_BUFFER_LEN     (1024*8)

static const std::string base64_chars="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64encode(unsigned char const* bytes_to_encode, unsigned int in_len)
{
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';

    }
    return ret;
}
std::string base64decode(std::string const& encoded_string)
{
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = (unsigned char)base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (j = 0; j < 4; j++)
            char_array_4[j] = (unsigned char)base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }
    return ret;
}
unsigned char toHex(const unsigned char &x)
{
    return x > 9 ? x - 10 + 'A' : x + '0';
}
unsigned char fromHex(const unsigned char &x)
{
    if (isdigit(x)) {
        return x - '0';
    } else if (isupper(x)) {
        return x - 'A' + 10;
    } else {
        return x - 'a' + 10;
    }
}
std::string urlencode(std::string &sIn)
{
    std::string sOut;
    for (size_t ix = 0; ix < sIn.size(); ix++)
    {
        unsigned char buf[4];
        memset(buf, 0, 4);
        if (isalnum((unsigned char)sIn[ix]))
        {
            buf[0] = sIn[ix];
        }
        else
        {
            buf[0] = '%';
            buf[1] = toHex((unsigned char)sIn[ix] >> 4);
            buf[2] = toHex((unsigned char)sIn[ix] % 16);
        }
        sOut += (char *)buf;
    }

    return sOut;

}
std::string urldecode(std::string &sIn)
{
    std::string sOut;
    for (size_t ix = 0; ix < sIn.size(); ix++)
    {
        unsigned char ch = 0;
        if (sIn[ix] == '%')
        {
            ch = (fromHex(sIn[ix + 1]) << 4);
            ch |= fromHex(sIn[ix + 2]);
            ix += 2;
        }
        else if (sIn[ix] == '+')
        {
            ch = ' ';
        }
        else
        {
            ch = sIn[ix];
        }
        sOut += (char)ch;
    }

    return sOut;
}
#ifdef __linux
int code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
    iconv_t cd;
    //int rc;
    char **pin = ( char ** ) &inbuf;
    char **pout = &outbuf;
    cd = iconv_open(to_charset,from_charset);
    if (cd==0) return -1;
    memset(outbuf,0,outlen);
    if (iconv(cd,pin,&inlen,pout,&outlen)==-1)
        return -1;
    iconv_close(cd);
    return 0;
}
std::string unicode2utf8(char* src ,size_t len)
{
    static char outbuffer[CODE_CONVERT_OUT_BUFFER_LEN];
    memset(outbuffer,0,CODE_CONVERT_OUT_BUFFER_LEN);
    size_t outlength=CODE_CONVERT_OUT_BUFFER_LEN;
    char* outbuf=outbuffer;
    int ret=code_convert("unicode","utf-8",src,len,outbuf,outlength);
    if(ret == -1)
        return "";
    return outbuf;
}
char* utf82unicode(std::string src,size_t& len)
{
    static char outbuffer[CODE_CONVERT_OUT_BUFFER_LEN];
    memset(outbuffer,0,CODE_CONVERT_OUT_BUFFER_LEN);
    size_t outlength=CODE_CONVERT_OUT_BUFFER_LEN;
    char* outbuf=outbuffer;
    size_t inlength=strlen(src.c_str())*sizeof(char);
    char* inbuffer = (char*)(src.c_str());
    int ret=code_convert("utf-8","unicode",inbuffer,inlength,outbuf,outlength);
    if(ret == -1)
        return NULL;
    len=outlength;
    return outbuf;
}
std::string gb23122utf8(char* src ,size_t len)
{
    static char outbuffer[CODE_CONVERT_OUT_BUFFER_LEN];
    memset(outbuffer,0,CODE_CONVERT_OUT_BUFFER_LEN);
    size_t outlength=CODE_CONVERT_OUT_BUFFER_LEN;
    char* outbuf=outbuffer;
    int ret=code_convert("gb2312","utf-8",src,len,outbuf,outlength);
    if(ret == -1)
        return "";
    return outbuf;
}
char* utf82gb2312(std::string src,size_t& len)
{
    static char outbuffer[CODE_CONVERT_OUT_BUFFER_LEN];
    memset(outbuffer,0,CODE_CONVERT_OUT_BUFFER_LEN);
    size_t outlength=CODE_CONVERT_OUT_BUFFER_LEN;
    char* outbuf=outbuffer;
    size_t inlength=strlen(src.c_str())*sizeof(char);
    char* inbuffer = (char*)(src.c_str());
    int ret=code_convert("utf-8","gb2312",inbuffer,inlength,outbuf,outlength);
    if(ret == -1)
        return NULL;
    len=outlength;
    return outbuf;
}
std::wstring string2wstring(const std::string str)
{
    if (str.size() == 0) {
        return std::wstring(L"");
    }
    unsigned len = str.size() * 2;
    setlocale(LC_CTYPE, "");
    wchar_t *p = new wchar_t[len];
    memset(p,0,sizeof(wchar_t)*len);
    mbstowcs(p, str.c_str(), len);
    std::wstring str1(p);
    delete[] p;
    return str1;
}
std::string wstring2string(const std::wstring str)
{
    if (str.size() == 0) {
        return std::string("");
    }
    unsigned len = str.size() * 4;
    setlocale(LC_CTYPE, "");
    char *p = new char[len];
    memset(p,0,sizeof(char)*len);
    wcstombs(p, str.c_str(), len);
    std::string str1(p);
    delete[] p;
    return str1;
}
#else
std::wstring ansi2wchar(std::string src)
{
    if(src=="")
        return std::wstring(L"");
    int nLen=MultiByteToWideChar( CP_ACP,0,src.c_str(),-1,NULL,0 );
    if(nLen<=0)
        return std::wstring(L"");
    wchar_t* pszDst = new wchar_t[nLen+1];
    if(NULL==pszDst)
        return std::wstring(L"");
    memset(pszDst,0,(nLen+1)*sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP,0,src.c_str(),-1,pszDst,nLen);
    std::wstring strTemp(pszDst);
    delete [] pszDst;
    return strTemp;
}
std::string wchar2ansi(std::wstring src)
{
    if(src==L"")
        return std::string("");
    int nLen=WideCharToMultiByte( CP_ACP,0,src.c_str(),-1,NULL,0,NULL,NULL );
    if(nLen<=0)
        return std::string("");
    char* pszDst = new char[nLen+1];
    if(NULL==pszDst)
        return std::string("");
    memset(pszDst,0,nLen+1);
    WideCharToMultiByte( CP_ACP,0,src.c_str(),-1,pszDst,nLen,NULL,NULL );
    std::string strTemp(pszDst);
    delete [] pszDst;
    return strTemp;
}
std::string wchar2utf8(std::wstring src)
{
    if( src == L"" )
        return std::string("");
    int nLen=WideCharToMultiByte( CP_UTF8,0,src.c_str(),-1,NULL,0,NULL,FALSE );
    if( nLen <= 0 )
        return std::string("");
    char* pszDst = new char[nLen+1];
    if( NULL == pszDst )
        return std::string("");
    memset( pszDst,0,nLen+1 );
    WideCharToMultiByte( CP_UTF8,0,src.c_str(),-1,pszDst,nLen,NULL,FALSE );
    std::string strTemp( pszDst );
    delete [] pszDst;
    return strTemp;
}
std::wstring utf82wchar(std::string src)
{
    if( src == "" )
        return std::wstring( L"" );
    int nLen=MultiByteToWideChar( CP_UTF8,0,src.c_str(),-1,NULL,0 );
    if(nLen<=0)
        return std::wstring(L"");
    wchar_t* pszDst = new wchar_t[nLen+1];
    if( NULL == pszDst )
        return std::wstring( L"" );
    memset( pszDst,0,(nLen+1)*sizeof(wchar_t) );
    MultiByteToWideChar( CP_UTF8,0,src.c_str(),-1,pszDst,nLen );
    std::wstring strTemp( pszDst );
    delete[] pszDst;
    return strTemp;
}
std::string utf82ansi(std::string src)
{
    return hl::wchar2ansi(hl::utf82wchar(src));
}
std::string ansi2utf8(std::string src)
{
    return wchar2utf8(ansi2wchar(src));
}
#endif
std::string buf2hex(uint8_t*buf, int32_t bufLen)
{
    if (bufLen <= 0)
        return "";
    std::string retStr;
    uint8_t* pTemp = new uint8_t[bufLen * 2 + 1];
    memset(pTemp, 0, bufLen * 2 + 1);
    for (int i = 0; i < bufLen; i++)
        sprintf((char*)(pTemp + 2 * i), "%02X", buf[i]);
    retStr = (char*)pTemp;
    if (pTemp)
        delete pTemp;
    return retStr;
}
uint32_t HEX2BYTE(uint8_t hex_ch)
{
    if (hex_ch >= '0' && hex_ch <= '9')
        return hex_ch - '0';
    if (hex_ch >= 'a' && hex_ch <= 'f')
        return hex_ch - 'a' + 10;
    if (hex_ch >= 'A' && hex_ch <= 'F')
        return hex_ch - 'A' + 10;
    return 0x00;
}
uint32_t hex2buf(std::string hex, uint8_t* outBuf)
{
    uint32_t hex_len = hex.length();
    uint32_t index = 0;
    if (hex_len % 2 == 1)
        hex_len -= 1;
    for (index = 0; index < hex_len; index += 2)
        outBuf[index / 2] = ((HEX2BYTE(hex[index]) << 4) & 0xF0) + HEX2BYTE(hex[index + 1]);
    return hex_len / 2;
}
void strsplit(std::vector<std::string>& lines, std::string src, std::string delims)
{
    auto n = src.find(delims);
    while (n != std::string::npos)
    {
        std::string tmp = src.substr(0, n);
        if (tmp != "")
            lines.push_back(tmp);
        src = src.substr(n + delims.length());
        n = src.find(delims);
    }
    if (src != "")
        lines.push_back(src);
}
std::string strreplace(std::string str, std::string src, std::string dest)
{
    std::string ret;
    std::string::size_type pos_begin = 0;
    std::string::size_type pos = str.find(src,pos_begin);
    while (pos != std::string::npos)
    {
        ret.append(str.data() + pos_begin, pos - pos_begin);
        ret += dest;
        pos_begin = pos + src.length();
        pos = str.find(src, pos_begin);
    }
    if (pos_begin < str.length())
    {
        ret.append(str.begin() + pos_begin, str.end());
    }
    return ret;
}
void str2upper(std::string& str, bool bUpper)
{
    if (bUpper)
        std::transform(str.begin(), str.end(), str.begin(), toupper);
    else
        std::transform(str.begin(), str.end(), str.begin(), tolower);
}
void FindMaxsubstr(const char *strA, const char *strB, char *maxSubStr)
{

        int maxPos = -1;
        int maxLen = 0;
        for (int i = 0; i < strlen(strA); i++)
        {
            for (int j = 0; j < strlen(strB); j++)
            {
                if (strA[i] == strB[j])
                {
                    for (int k = 1; (strA[i + k] == strB[j + k]) && (strA[i + k] != '\0'); )
                    {
                        if (k >= maxLen)
                        {
                            maxPos = i;
                            maxLen = k + 1;
                        }
                        k++;
                    }
                }
            }
        }
        if (maxPos == -1)
        {
            maxSubStr[0] = '\0';
        }
        else
        {
            memcpy(maxSubStr, strA + maxPos, maxLen);
            maxSubStr[maxLen] = '\0';
        }
}
}
