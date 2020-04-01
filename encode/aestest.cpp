//Copyright [2016-12-29] <Copyright: Shuhui.li>

#include <string.h>
#include <iostream>

#include "AES.h"

using std::cout;
using std::endl;

int main()
{
    const char *pKey = "1234567890123456";
    AES mAes = AES(AES::BIT128, (BYTE *)pKey);
    char pResult[64] = "";
    mAes.StrDecode("670B41B35D84F12FA979F833EF5CD609", pResult);

    cout << pResult << endl;

    mAes.StrCode("121.199.19.151", pResult);
    cout << pResult << endl;

    mAes.StrDecode("31C0E6244BFC19C2FD83D2F3EA6762DB", pResult);
    cout << pResult << endl;
    return 0;
}
