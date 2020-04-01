#include <string>

/**
* ƴ��int
*/
std::string getKeyValue(std::string sKey, int iValue)
{
    char szDoubleQutoes[] = "\"";
    char szColon[] = ":";
    char szValue[50] = { 0 };

    std::string strResult;

    strResult.append(szDoubleQutoes);
    strResult.append(sKey);
    strResult.append(szDoubleQutoes);

    strResult.append(szColon);
    sprintf(szValue, "%d", iValue);
    strResult.append(szValue);

    return strResult;
}

/**
* ƴ��float������3λ
*/
std::string getKeyValue(std::string sKey, float fValue)
{
    char szDoubleQutoes[] = "\"";
    char szColon[] = ":";
    char szValue[50] = { 0 };

    std::string strResult;

    strResult.append(szDoubleQutoes);
    strResult.append(sKey);
    strResult.append(szDoubleQutoes);

    strResult.append(szColon);
    sprintf(szValue, "%0.3f", fValue);
    strResult.append(szValue);

    return strResult;
}

/**
* ƴ��string
*/
std::string getKeyValue(std::string sKey, std::string sValue)
{
    char szDoubleQutoes[] = "\"";
    char szColon[] = ":";
    std::string strResult;

    strResult.append(szDoubleQutoes);
    strResult.append(sKey);
    strResult.append(szDoubleQutoes);

    strResult.append(szColon);
    strResult.append(szDoubleQutoes);
    strResult.append(sValue);
    strResult.append(szDoubleQutoes);

    return strResult;
}

/**
* ƴ��object
*/
//std::string getKeyValueObject(std::string sKey, std::string sObject)
//{
//    char szDoubleQutoes[] = "\"";
//    char szColon[] = ":";
//    std::string strResult;
//
//    strResult.append(szDoubleQutoes);
//    strResult.append(sKey);
//    strResult.append(szDoubleQutoes);
//
//    strResult.append(szColon);
//    strResult.append(sObject);
//
//    return strResult;
//}

/**
* ƴ��array
*/
std::string getKeyValueArray(std::string sKey, std::string sArray)
{
    char szDoubleQutoes[] = "\"";
    char szColon[] = ":";
    std::string strResult;

    strResult.append(szDoubleQutoes);
    strResult.append(sKey);
    strResult.append(szDoubleQutoes);

    strResult.append(szColon);
    strResult.append("[");
    strResult.append(sArray);
    strResult.append("]");

    return strResult;
}

/**
* ��������, ������obj
*/
std::string getKeyValueArray(std::string sKey, std::vector<std::string> vecObj)
{
    if (0 == sKey.size() || 0 == vecObj.size())
    {
        return "";
    }

    char szDoubleQutoes[] = "\"";
    char szColon[] = ":";
    std::string strResult;

    strResult.append(szDoubleQutoes);
    strResult.append(sKey);
    strResult.append(szDoubleQutoes);

    strResult.append(szColon);
    strResult.append("[");


    for (auto it = vecObj.begin(); it != vecObj.end(); )
    {
        strResult.append(*it);

        ++it;

        if (it != vecObj.end())
        {
            strResult.append(",");
        }
    }

    strResult.append("]");

    return strResult;
}

// ���ض���
std::string getKeyValueObject(std::string sKey, std::string sValue)
{
    std::string strObjResult("{");
    char szDoubleQutoes[] = "\"";
    char szColon[] = ":";

    strObjResult.append(szDoubleQutoes);
    strObjResult.append(sKey);
    strObjResult.append(szDoubleQutoes);

    strObjResult.append(szColon);

    strObjResult.append(szDoubleQutoes);
    strObjResult.append(sValue);
    strObjResult.append(szDoubleQutoes);

    strObjResult.append("}");

    return strObjResult;
}

// ���ض�Լ�ֵ����
std::string getKeyValueObject(std::map<std::string, std::string> data)
{
    if (data.size() == 0) {
        return "";
    };

    std::string strObjResult("{");
    char szDoubleQutoes[] = "\"";
    char szColon[] = ":";

    for (auto it = data.begin(); it != data.end();)
    {
        strObjResult.append(szDoubleQutoes);
        strObjResult.append(it->first);
        strObjResult.append(szDoubleQutoes);

        strObjResult.append(szColon);

        strObjResult.append(szDoubleQutoes);
        strObjResult.append(it->second);
        strObjResult.append(szDoubleQutoes);

        ++it;
        if (it != data.end())
        {
            strObjResult.append(",");
        }
    }

    strObjResult.append("}");

    return strObjResult;
}