//Copyright [2016-12-29] <Copyright: Shuhui.li>

#ifndef _AES_H_
#define _AES_H_

//#if defined(WIN32)
//#if defined(AES_DLL)
//#define AES_EXPORT __declspec(dllexport)
//#else
//#define AES_EXPORT __declspec(dllimport)
//#endif

//#else
//#define AES_EXPORT
//#endif

#if _MSC_VER
#define  snprintf _snprintf
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif
//typedef unsigned char BYTE;
typedef unsigned char *LPBYTE;

class AES
{
public:
typedef enum ENUM_KeySize_
{
    BIT128 = 0,
    BIT192,
    BIT256
}ENUM_KEYSIZE;
public:
    AES(ENUM_KEYSIZE keysize, BYTE *key);
    ~AES(void);

    bool StrCode(const char *pInput, char *pOutput);
    bool StrDecode(const char *pInput, char *pOutput);

protected:
    BYTE *RotWord(BYTE *word);
    BYTE *SubWord(BYTE *word);
    void AddRoundKey(int round);
    void SubBytes();
    void InvSubBytes();
    void ShiftRows();
    void InvShiftRows();
    void MixColumns();
    void InvMixColumns();

    void Cipher(const BYTE *input, BYTE *output);
    void InvCipher(const BYTE *input, BYTE *output);

    bool StrToB16Str(const BYTE * inContent, BYTE * outContent, int inLen);
    void StrCipher(const BYTE * inContent, BYTE * outContent, int &nLength);

    bool B16StrToStr(const BYTE * inContent, BYTE * outContent, int *outLen);
    void StrInvCipher(const BYTE * inContent, BYTE * outContent, int inLen);

    static BYTE gfmultby01(BYTE b){
      return b;
    }

    static BYTE gfmultby02(BYTE b){
      if (b < 0x80)
        return (BYTE)(static_cast<int>(b <<1));
      else
        return (BYTE)( static_cast<int>(b << 1) ^ static_cast<int>(0x1b) );
    }

    static BYTE gfmultby03(BYTE b){
      return (BYTE) ( static_cast<int>(gfmultby02(b)) ^ static_cast<int>(b) );
    }

    static BYTE gfmultby09(BYTE b){
      return (BYTE)( static_cast<int>(gfmultby02(gfmultby02(gfmultby02(b)))) ^
                     static_cast<int>(b) );
    }

    static BYTE gfmultby0b(BYTE b){
      return (BYTE)( static_cast<int>(gfmultby02(gfmultby02(gfmultby02(b)))) ^
                     static_cast<int>(gfmultby02(b)) ^
                     static_cast<int>(b) );
    }

    static BYTE gfmultby0d(BYTE b)
    {
      return (BYTE)( static_cast<int>(gfmultby02(gfmultby02(gfmultby02(b)))) ^
                     static_cast<int>(gfmultby02(gfmultby02(b))) ^
                     static_cast<int>(b) );
    }

    static BYTE gfmultby0e(BYTE b){
      return (BYTE)( static_cast<int>(gfmultby02(gfmultby02(gfmultby02(b)))) ^
                     static_cast<int>(gfmultby02(gfmultby02(b))) ^
                     static_cast<int>(gfmultby02(b)));
    }
    int Nb;
    int Nk;
    int Nr;
    BYTE *key;// the seed key. size will be 4 * keySize from ctor.
    typedef struct BYTE4_{
        BYTE w[4];
    }BYTE4;
    BYTE4 *w;
    LPBYTE State[4];
    /*
    private byte[,] iSbox;  // inverse Substitution box
    private byte[,] w;      // key schedule array.
    private byte[,] Rcon;   // Round constants.
    private byte[,] State;  // State matrix*/

};
#endif
