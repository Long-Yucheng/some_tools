#include <iostream>
#include "http_client.h"

#include "../rapidjson/document.h"

using namespace std;

void getKeyList(std::string rspStr)
{
    rapidjson::Document document;
    document.Parse(rspStr.c_str());

    rapidjson::Value::ConstMemberIterator iter = document.FindMember("code");
    if (iter != document.MemberEnd()) {
        cout << "code : " << iter->value.GetInt() << endl;
        // todo 判断是不是0
    }
    else {
        // todo 告警
    }

    iter = document.FindMember("success");
    if (iter != document.MemberEnd()) {
        cout << "success : " << iter->value.GetBool() << endl;
        // todo 判断 true or false
    }
    else {
        // todo 告警
    }

    if (document.HasMember("object"))
    {
        const rapidjson::Value& childValue = document["object"];
        for (rapidjson::Value::ConstMemberIterator it = childValue.MemberBegin(); it != childValue.MemberEnd(); ++it) {
            cout << "    " << it->name.GetString() << endl;
        }

        if (childValue.HasMember("uri"))
        {
            const rapidjson::Value& uriValue = childValue["uri"];
            if (uriValue.Size() > 0)
            {
                cout << "uri size = " << uriValue.Size() << endl;

                if (uriValue.IsArray()) {
                    for (rapidjson::SizeType i = 0; i < uriValue.Size(); i++) {
                        const rapidjson::Value& uriMeta = uriValue[i];
                        rapidjson::Value::ConstMemberIterator itKey = uriMeta.FindMember("key");
                        if (itKey != document.MemberEnd()) {
                            cout << "key : " << itKey->value.GetString() << endl;
                        }
                        else {
                            // todo 告警
                        }
                    }
                }
                else {
                    // todo 告警
                }
            }
            else {
                // todo 告警
            }
        }
        else {
            // todo 告警
        }
    }
    else {
        // todo 告警
    }
}

void getValue(std::string valueStr)
{
    rapidjson::Document document;
    document.Parse(valueStr.c_str());

    rapidjson::Value::ConstMemberIterator iter = document.FindMember("code");
    if (iter != document.MemberEnd()) {
        cout << "code : " << iter->value.GetInt() << endl;
        // todo 判断是不是0
    }
    else {
        // todo 告警
    }

    iter = document.FindMember("success");
    if (iter != document.MemberEnd()) {
        cout << "success : " << iter->value.GetBool() << endl;
        // todo 判断 true or false
    }
    else {
        // todo 告警
    }

    if (document.HasMember("object"))
    {
        const rapidjson::Value& childValue = document["object"];
        if (childValue.HasMember("data"))
        {
            const rapidjson::Value& dataValue = childValue["data"];

            if (dataValue.IsArray() && dataValue.Size() > 0)
            {
                for (size_t i = 0; i < dataValue.Size(); i++)
                {
                    const rapidjson::Value& array = dataValue[i];

                    cout << array[0].GetInt() << "  " << array[1].GetInt() << endl;
                }
            }
            else {

            }
        }
        else {
            // todo 告警
        }
    }
}

void handle_func(std::string rsp)
{
    // do sth according to rsp
    std::cout << "http rsp: " << rsp << std::endl;
}

void handle_json(std::string rsp)
{   

}

int main()
{
#if 0
    // GET请求
    std::string url1 = "http://127.0.0.1:7999/api/hello";
    HttpClient::SendReq(url1, handle_func);
    std::cout << "==================================== " << std::endl;
    

    HttpClient::SendReq(url1, handle_func);

    // POST请求
    //std::string url2 = "http://localhost:7999/api/sum";
    //HttpClient::SendReq(url2, 
    //    handle_func, 
    //    "Content-Type: application/x-www-form-urlencoded\r\n", 
    //    "n1=20&n2=18");


    std::string url3 = "http://monitor.sysop.duowan.com/webservice/loadAppInfo.do";
    HttpClient::SendReq(url3,
        getKeyList,
        "Content-Type: application/x-www-form-urlencoded\r\n",
        "includes=uri&appName=bt_svc_ap_d&serviceName=TO_USER_BANDWIDTH_BY_SERVICETYPE&tag=s&topic=TOTAL_DOWN_TO_CLIENT_DATA_SIZE&type=counter&uri=");

    std::cout << "==================================== " << std::endl;
    std::cout << "==================================== " << std::endl;
#endif


#if 1
    // 查询所有 appid 的数据
    /*
    std::string para_head1 = "topic=TOTAL_DOWN_TO_CLIENT_DATA_SIZE&type=counter&unit=byte&title=业务下行流量(TOTAL_DOWN_TO_CLIENT_DATA_SIZE)&appName=bt_svc_ap_d&";
    std::string para_head2 = "serviceName=TO_USER_BANDWIDTH_BY_SERVICETYPE&relation=package&tag=s&uri=";
    std::string para_appid = "10095";
    std::string para_head3 = "&version=&isp=&idc=&host=&contrast=0&parentUri=&stime=";
    std::string para_startTime = "1580486400";
    std::string para_head4 = "&etime=";
    std::string para_endTime = "1582992000";
    std::string para_head5 = "&target=topic&delayType=&dimensions[0]=uri";
    std::string parameter2 = para_head1 + para_head2 + para_appid + para_head3 + para_startTime + para_head4 + para_endTime + para_head5;
    */


    
    std::string para_appid = "20010";
    std::string para_head1 = "topic=templateCount&type=counter&unit=&title=templateCount&appName=voice_online_stat_V3_d&serviceName=online_stat&relation=package";
    std::string para_head3 = "&tag=s&uri=";
    std::string para_head4 = "&version=&isp=&idc=&host=&contrast=0&parentUri=&stime=1580486400&etime=1582992000";
    std::string para_head5 = "&target=topic&delayType=&dimensions[0]=uri";
    std::string parameter2 = para_head1 + para_head3 + para_appid + para_head4 + para_head5;

    std::cout << parameter2 << std::endl;

    std::string x = "topic=templateCount&type=counter&unit=&title=templateCount&appName=voice_online_stat_V3_d&serviceName=online_stat&relation=package&tag=s&uri=20010&version=&isp=&idc=&host=&contrast=0&parentUri=&stime=1584514559&etime=1584536159&target=topic&delayType=&dimensions[0]=uri";
    std::cout << x << std::endl;

    std::string url4 = "http://monitor.sysop.duowan.com/webservice/queryServerMetricsData.do";
    HttpClient::SendReq(url4,
        handle_func,
        "Content-Type: application/x-www-form-urlencoded\r\n",
        x.c_str());
#endif


    return 0;
}
