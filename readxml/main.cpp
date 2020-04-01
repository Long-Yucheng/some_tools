#include <QCoreApplication>
#include <iostream>

#include "MarkupSTL.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CMarkupSTL xml;
    bool    flag;

    //加载Xml文件
    flag = xml.Load("d:\\preradio_20170315_0906.xml");
    if (!flag) {
        cout << "load preradio_20170315_0906.xml failed" << endl;
        return 0;
    }

    //定位到Root Elem
    xml.ResetPos();
    flag = xml.FindElem("preradio");  //Root Elem为<UserInfos></UserInfos>
    if (!flag)
    {
        return 0;
    }

    xml.IntoElem();   //进入根节点
    if (xml.FindElem("option")) {
        string flag;
        flag = xml.GetAttrib("flag");
        cout << flag << endl;
    }

#if 1
    if (xml.FindElem("radio"))
    {
        xml.IntoElem();   //进入<UserInfo></UserInfo>

        //获取name节点数据
        while (xml.FindElem("tag"))
        {
            string cstrName, val;
            cstrName = xml.GetAttrib("tagid");
            val      = xml.GetAttrib("value");
            cout << cstrName << "--->" << val << endl;
        }
        xml.OutOfElem();  //跳出<UserInfo></UserInfo>
    }
    xml.OutOfElem();  //跳出根节点
#endif
    return a.exec();
}
