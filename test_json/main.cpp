#include "time.h"
#include "stdio.h"
#include "stdlib.h"

#include <openssl/sha.h>

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <thread>
#include <iomanip>

#include "rapidjson/document.h"
#include "SplicingJson.h"

using namespace std;


std::string rspStr = "{ \"code\":0,\"message\":\"操作成功\",\"object\":{\"name\":\"bt_svc_ap_d\",\"alias\":\"bt_svc_ap_d\",\"serviceName\":\"TO_USER_BANDWIDTH_BY_SERVICETYPE\",\"uri\":[{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10095\",\"key\":\"10095\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60109\",\"key\":\"60109\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10657\",\"key\":\"10657\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10414\",\"key\":\"10414\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10538\",\"key\":\"10538\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10537\",\"key\":\"10537\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60356\",\"key\":\"60356\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60355\",\"key\":\"60355\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15788\",\"key\":\"15788\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15787\",\"key\":\"15787\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10651\",\"key\":\"10651\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10530\",\"key\":\"10530\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10653\",\"key\":\"10653\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10411\",\"key\":\"10411\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10531\",\"key\":\"10531\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10654\",\"key\":\"10654\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10533\",\"key\":\"10533\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15673\",\"key\":\"15673\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"17\",\"key\":\"17\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60009\",\"key\":\"60009\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10547\",\"key\":\"10547\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60129\",\"key\":\"60129\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10667\",\"key\":\"10667\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10546\",\"key\":\"10546\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10669\",\"key\":\"10669\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10309\",\"key\":\"10309\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60247\",\"key\":\"60247\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60246\",\"key\":\"60246\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10308\",\"key\":\"10308\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"6\",\"key\":\"6\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"25112\",\"key\":\"25112\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60244\",\"key\":\"60244\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60001\",\"key\":\"60001\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60243\",\"key\":\"60243\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60363\",\"key\":\"60363\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60241\",\"key\":\"60241\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10662\",\"key\":\"10662\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10661\",\"key\":\"10661\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"任务系统(交友/寻欢/狼人杀)[10540]\",\"key\":\"10540\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10545\",\"key\":\"10545\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10665\",\"key\":\"10665\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10544\",\"key\":\"10544\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"22\",\"key\":\"22\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10635\",\"key\":\"10635\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"133\",\"key\":\"133\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60258\",\"key\":\"60258\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10638\",\"key\":\"10638\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10517\",\"key\":\"10517\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60257\",\"key\":\"60257\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60377\",\"key\":\"60377\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60376\",\"key\":\"60376\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10198\",\"key\":\"10198\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60375\",\"key\":\"60375\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15403\",\"key\":\"15403\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60254\",\"key\":\"60254\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60012\",\"key\":\"60012\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10197\",\"key\":\"10197\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60252\",\"key\":\"60252\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10199\",\"key\":\"10199\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10078\",\"key\":\"10078\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10510\",\"key\":\"10510\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60371\",\"key\":\"60371\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"30\",\"key\":\"30\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60370\",\"key\":\"60370\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10630\",\"key\":\"10630\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"31\",\"key\":\"31\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10646\",\"key\":\"10646\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10404\",\"key\":\"10404\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10403\",\"key\":\"10403\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10406\",\"key\":\"10406\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10648\",\"key\":\"10648\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10527\",\"key\":\"10527\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60149\",\"key\":\"60149\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10405\",\"key\":\"10405\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10529\",\"key\":\"10529\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60147\",\"key\":\"60147\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10528\",\"key\":\"10528\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60389\",\"key\":\"60389\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"1001\",\"key\":\"1001\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60387\",\"key\":\"60387\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10409\",\"key\":\"10409\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60386\",\"key\":\"60386\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60143\",\"key\":\"60143\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60385\",\"key\":\"60385\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60142\",\"key\":\"60142\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10640\",\"key\":\"10640\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10089\",\"key\":\"10089\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10642\",\"key\":\"10642\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10641\",\"key\":\"10641\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60381\",\"key\":\"60381\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10402\",\"key\":\"10402\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10051\",\"key\":\"10051\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"48\",\"key\":\"48\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10734\",\"key\":\"10734\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10733\",\"key\":\"10733\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10615\",\"key\":\"10615\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10736\",\"key\":\"10736\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10738\",\"key\":\"10738\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10737\",\"key\":\"10737\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60279\",\"key\":\"60279\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10619\",\"key\":\"10619\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60399\",\"key\":\"60399\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60035\",\"key\":\"60035\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60398\",\"key\":\"60398\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10618\",\"key\":\"10618\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"61245\",\"key\":\"61245\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60277\",\"key\":\"60277\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60155\",\"key\":\"60155\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60154\",\"key\":\"60154\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60396\",\"key\":\"60396\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60273\",\"key\":\"60273\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60394\",\"key\":\"60394\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60393\",\"key\":\"60393\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10730\",\"key\":\"10730\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60392\",\"key\":\"60392\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10732\",\"key\":\"10732\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"55\",\"key\":\"55\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"59\",\"key\":\"59\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10063\",\"key\":\"10063\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10624\",\"key\":\"10624\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10628\",\"key\":\"10628\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60166\",\"key\":\"60166\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60162\",\"key\":\"60162\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10740\",\"key\":\"10740\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15043\",\"key\":\"15043\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10390\",\"key\":\"10390\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15046\",\"key\":\"15046\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10391\",\"key\":\"10391\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10394\",\"key\":\"10394\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"62910\",\"key\":\"62910\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"62911\",\"key\":\"62911\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10712\",\"key\":\"10712\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10711\",\"key\":\"10711\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10713\",\"key\":\"10713\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10716\",\"key\":\"10716\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10718\",\"key\":\"10718\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10717\",\"key\":\"10717\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10033\",\"key\":\"10033\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10032\",\"key\":\"10032\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60054\",\"key\":\"60054\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"匹配服务(交友/寻欢/狼人杀)[10398]\",\"key\":\"10398\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10034\",\"key\":\"10034\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15048\",\"key\":\"15048\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60052\",\"key\":\"60052\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"50019\",\"key\":\"50019\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60171\",\"key\":\"60171\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60050\",\"key\":\"60050\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10710\",\"key\":\"10710\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15054\",\"key\":\"15054\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15053\",\"key\":\"15053\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15052\",\"key\":\"15052\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10042\",\"key\":\"10042\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10723\",\"key\":\"10723\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10722\",\"key\":\"10722\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10604\",\"key\":\"10604\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10725\",\"key\":\"10725\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10727\",\"key\":\"10727\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10726\",\"key\":\"10726\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10729\",\"key\":\"10729\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"50024\",\"key\":\"50024\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10607\",\"key\":\"10607\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10728\",\"key\":\"10728\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10721\",\"key\":\"10721\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10720\",\"key\":\"10720\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10370\",\"key\":\"10370\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10372\",\"key\":\"10372\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"50031\",\"key\":\"50031\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60079\",\"key\":\"60079\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10374\",\"key\":\"10374\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10373\",\"key\":\"10373\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60077\",\"key\":\"60077\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10375\",\"key\":\"10375\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10377\",\"key\":\"10377\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60081\",\"key\":\"60081\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60080\",\"key\":\"60080\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15031\",\"key\":\"15031\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15151\",\"key\":\"15151\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10381\",\"key\":\"10381\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10380\",\"key\":\"10380\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"64567\",\"key\":\"64567\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60405\",\"key\":\"60405\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"50042\",\"key\":\"50042\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10703\",\"key\":\"10703\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"50044\",\"key\":\"50044\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"30097\",\"key\":\"30097\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60400\",\"key\":\"60400\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10385\",\"key\":\"10385\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60087\",\"key\":\"60087\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15038\",\"key\":\"15038\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10386\",\"key\":\"10386\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15037\",\"key\":\"15037\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10388\",\"key\":\"10388\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60092\",\"key\":\"60092\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10590\",\"key\":\"10590\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15003\",\"key\":\"15003\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10592\",\"key\":\"10592\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10591\",\"key\":\"10591\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60408\",\"key\":\"60408\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60407\",\"key\":\"60407\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60406\",\"key\":\"60406\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60416\",\"key\":\"60416\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60415\",\"key\":\"60415\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60412\",\"key\":\"60412\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60533\",\"key\":\"60533\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"30085\",\"key\":\"30085\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60410\",\"key\":\"60410\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10354\",\"key\":\"10354\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15004\",\"key\":\"15004\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10597\",\"key\":\"10597\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15129\",\"key\":\"15129\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10599\",\"key\":\"10599\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15013\",\"key\":\"15013\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15012\",\"key\":\"15012\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10918\",\"key\":\"10918\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60417\",\"key\":\"60417\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"30079\",\"key\":\"30079\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60305\",\"key\":\"60305\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60303\",\"key\":\"60303\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60423\",\"key\":\"60423\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60422\",\"key\":\"60422\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60300\",\"key\":\"60300\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60421\",\"key\":\"60421\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60420\",\"key\":\"60420\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10365\",\"key\":\"10365\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10369\",\"key\":\"10369\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"20011\",\"key\":\"20011\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"20010\",\"key\":\"20010\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60428\",\"key\":\"60428\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10579\",\"key\":\"10579\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10339\",\"key\":\"10339\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15903\",\"key\":\"15903\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10218\",\"key\":\"10218\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60313\",\"key\":\"60313\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"15908\",\"key\":\"15908\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60310\",\"key\":\"60310\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10572\",\"key\":\"10572\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10693\",\"key\":\"10693\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10692\",\"key\":\"10692\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10571\",\"key\":\"10571\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10574\",\"key\":\"10574\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10573\",\"key\":\"10573\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10694\",\"key\":\"10694\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10697\",\"key\":\"10697\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10336\",\"key\":\"10336\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10578\",\"key\":\"10578\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10699\",\"key\":\"10699\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10698\",\"key\":\"10698\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10335\",\"key\":\"10335\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10577\",\"key\":\"10577\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10581\",\"key\":\"10581\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10580\",\"key\":\"10580\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60207\",\"key\":\"60207\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60328\",\"key\":\"60328\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10348\",\"key\":\"10348\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60204\",\"key\":\"60204\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60323\",\"key\":\"60323\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60320\",\"key\":\"60320\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10583\",\"key\":\"10583\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10582\",\"key\":\"10582\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10343\",\"key\":\"10343\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10100\",\"key\":\"10100\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10342\",\"key\":\"10342\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10587\",\"key\":\"10587\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10588\",\"key\":\"10588\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10346\",\"key\":\"10346\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10316\",\"key\":\"10316\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60339\",\"key\":\"60339\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10679\",\"key\":\"10679\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10557\",\"key\":\"10557\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60217\",\"key\":\"60217\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10559\",\"key\":\"10559\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60336\",\"key\":\"60336\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10317\",\"key\":\"10317\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60213\",\"key\":\"60213\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60212\",\"key\":\"60212\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60210\",\"key\":\"60210\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10550\",\"key\":\"10550\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10671\",\"key\":\"10671\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10670\",\"key\":\"10670\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10310\",\"key\":\"10310\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10673\",\"key\":\"10673\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10672\",\"key\":\"10672\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10551\",\"key\":\"10551\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10554\",\"key\":\"10554\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10312\",\"key\":\"10312\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10675\",\"key\":\"10675\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10674\",\"key\":\"10674\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10677\",\"key\":\"10677\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10676\",\"key\":\"10676\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10680\",\"key\":\"10680\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"64389\",\"key\":\"64389\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60108\",\"key\":\"60108\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10568\",\"key\":\"10568\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10326\",\"key\":\"10326\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60469\",\"key\":\"60469\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60347\",\"key\":\"60347\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60105\",\"key\":\"60105\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60104\",\"key\":\"60104\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"60224\",\"key\":\"60224\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10682\",\"key\":\"10682\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10561\",\"key\":\"10561\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10681\",\"key\":\"10681\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10560\",\"key\":\"10560\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10563\",\"key\":\"10563\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10684\",\"key\":\"10684\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10562\",\"key\":\"10562\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10683\",\"key\":\"10683\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10686\",\"key\":\"10686\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10685\",\"key\":\"10685\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10564\",\"key\":\"10564\"},{\"hasChildren\":true,\"childrenName\":\"Ap/Sp\",\"alias\":\"10567\",\"key\":\"10567\"}]},\"success\":true}";

std::string valueStr = "{\"code\":0,\"message\":null,\"object\":{\"data\":[[1582588800,2983946],[1582675200,35206555]],\"param\":{\"appName\":\"bt_svc_ap_d\",\"contrast\":0,\"delayType\":\"\",\"etime\":1582689190,\"host\":\"\",\"idc\":\"\",\"isp\":\"\",\"key\":null,\"period\":86400,\"periodTable\":60,\"periodUp\":86400,\"queryParamMd5\":\"03df72e9070fa53fbcffeea622a15697\",\"serviceName\":\"TO_USER_BANDWIDTH_BY_SERVICETYPE\",\"stime\":1582667590,\"tag\":\"s\",\"target\":\"topic\",\"topic\":\"TOTAL_DOWN_TO_CLIENT_DATA_SIZE\",\"trace\":null,\"tsAgg\":false,\"type\":\"counter\",\"uri\":\"10095\",\"uriType\":0,\"version\":\"\"}},\"success\":true}";

std::string value2 = "{\"code\":0,\"message\":null,\"object\":{\"data\":[[1580428800,null],[1580515200,null],[1580601600,null],[1580688000,null]],\"param\":{\"appName\":\"bt_svc_ap_d\",\"contrast\":0,\"delayType\":\"\",\"etime\":1582992000,\"host\":\"\",\"idc\":\"\",\"isp\":\"\",\"key\":null,\"period\":86400,\"periodTable\":60,\"periodUp\":86400,\"queryParamMd5\":\"222684a4e567f9a92a9be78ffa67a603\",\"serviceName\":\"TO_USER_BANDWIDTH_BY_SERVICETYPE\",\"stime\":1580486400,\"tag\":\"s\",\"target\":\"topic\",\"topic\":\"TOTAL_DOWN_TO_CLIENT_DATA_SIZE\",\"trace\":null,\"tsAgg\":false,\"type\":\"counter\",\"uri\":\"10078\",\"uriType\":0,\"version\":\"\"}},\"success\":true}";

std::string value3 = "{\"code\":0,\"message\":null,\"object\":{\"data\":[[1580428800,null],[1580515200,null],[1580601600,null],[1580688000,null],[1580774400,null],[1580860800,null],[1580947200,null],[1581033600,null],[1581120000,null],[1581206400,null],[1581292800,null],[1581379200,null],[1581465600,null],[1581552000,null],[1581638400,null],[1581724800,null],[1581811200,2415401205],[1581897600,2539148254],[1581984000,2321887895],[1582070400,2405894841],[1582156800,2886860390],[1582243200,2469047637],[1582329600,2537862248],[1582416000,5008307275],[1582502400,2676733016],[1582588800,2544820438],[1582675200,2414274082],[1582761600,2728614365],[1582848000,2550157624],[1582934400,2437930664]],\"param\":{\"appName\":\"bt_svc_ap_d\",\"contrast\":0,\"delayType\":\"\",\"etime\":1582992000,\"host\":\"\",\"idc\":\"\",\"isp\":\"\",\"key\":null,\"period\":86400,\"periodTable\":60,\"periodUp\":86400,\"queryParamMd5\":\"222684a4e567f9a92a9be78ffa67a603\",\"serviceName\":\"TO_USER_BANDWIDTH_BY_SERVICETYPE\",\"stime\":1580486400,\"tag\":\"s\",\"target\":\"topic\",\"topic\":\"TOTAL_DOWN_TO_CLIENT_DATA_SIZE\",\"trace\":null,\"tsAgg\":false,\"type\":\"counter\",\"uri\":\"10078\",\"uriType\":0,\"version\":\"\"}},\"success\":true}";

std::string value4 = "{\"code\":0,\"message\":\"操作成功\",\"object\":{\"name\":\"svc_uniap_d\",\"alias\":\"svc_uniap_d\",\"serviceName\":\"Summary\",\"uri\":[{\"hasChildren\":true,\"childrenName\":\"子URI\",\"alias\":\"WooHoo测试版[1415418005]\",\"key\":\"1415418005\"},{\"hasChildren\":true,\"childrenName\":\"子URI\",\"alias\":\"1692022008\",\"key\":\"1692022008\"},{\"hasChildren\":true,\"childrenName\":\"子URI\",\"alias\":\"NULL\",\"key\":\"NULL\"}]},\"success\":true}";

std::string v5 = "{\"appId\":\"costUser\",\"apiDate\":\"2020-03-04 16:06:13\",\"sign\":\"12f56e227fdeefc92302dda98e64fe6e51fce2f3\",\"ratioName\":\"全球化Service\",\"yyyyMM\":\"2020-02\",\"data\":[{\"idcId\":\"0\",\"other\":\"0\",\"ratio\":\"0.000007\"},{\"idcId\":\"0\",\"other\":\"10034\",\"ratio\":\"0.000035\"},{\"idcId\":\"0\",\"other\":\"1009532256\",\"ratio\":\"0.000007\"},{\"idcId\":\"0\",\"other\":\"1026915519\",\"ratio\":\"0.000002\"},{\"idcId\":\"0\",\"other\":\"10309\",\"ratio\":\"0.034725\"},{\"idcId\":\"0\",\"other\":\"1032837259\",\"ratio\":\"0.000479\"},{\"idcId\":\"0\",\"other\":\"1035925933\",\"ratio\":\"0.000015\"},{\"idcId\":\"0\",\"other\":\"1036180342\",\"ratio\":\"0.000017\"},{\"idcId\":\"0\",\"other\":\"1047301740\",\"ratio\":\"0.000017\"},{\"idcId\":\"0\",\"other\":\"1057411727\",\"ratio\":\"0.000055\"},{\"idcId\":\"0\",\"other\":\"1059445685\",\"ratio\":\"0.001450\"},{\"idcId\":\"0\",\"other\":\"1069761727\",\"ratio\":\"0.000589\"},{\"idcId\":\"0\",\"other\":\"1084078970\",\"ratio\":\"0.000040\"},{\"idcId\":\"0\",\"other\":\"1089823423\",\"ratio\":\"0.007052\"},{\"idcId\":\"0\",\"other\":\"1120316264\",\"ratio\":\"0.000007\"},{\"idcId\":\"0\",\"other\":\"1122112089\",\"ratio\":\"0.006214\"},{\"idcId\":\"0\",\"other\":\"1143951973\",\"ratio\":\"0.005456\"},{\"idcId\":\"0\",\"other\":\"1163842901\",\"ratio\":\"0.018429\"},{\"idcId\":\"0\",\"other\":\"1164671593\",\"ratio\":\"0.333907\"},{\"idcId\":\"0\",\"other\":\"1170901840\",\"ratio\":\"0.000002\"},{\"idcId\":\"0\",\"other\":\"1184410631\",\"ratio\":\"0.000002\"},{\"idcId\":\"0\",\"other\":\"1190250345\",\"ratio\":\"0.000012\"},{\"idcId\":\"0\",\"other\":\"1190652323\",\"ratio\":\"0.000017\"},{\"idcId\":\"0\",\"other\":\"1249193970\",\"ratio\":\"0.001590\"},{\"idcId\":\"0\",\"other\":\"1254806212\",\"ratio\":\"0.000017\"},{\"idcId\":\"0\",\"other\":\"1275655567\",\"ratio\":\"0.000045\"},{\"idcId\":\"0\",\"other\":\"1292464057\",\"ratio\":\"0.000035\"},{\"idcId\":\"0\",\"other\":\"1296334940\",\"ratio\":\"0.001961\"},{\"idcId\":\"0\",\"other\":\"1300740699\",\"ratio\":\"0.006843\"},{\"idcId\":\"0\",\"other\":\"1314493338\",\"ratio\":\"0.000245\"},{\"idcId\":\"0\",\"other\":\"1332142413\",\"ratio\":\"0.000358\"},{\"idcId\":\"0\",\"other\":\"1350626568\",\"ratio\":\"0.000017\"},{\"idcId\":\"0\",\"other\":\"1361255917\",\"ratio\":\"0.001675\"},{\"idcId\":\"0\",\"other\":\"1363316465\",\"ratio\":\"0.000396\"},{\"idcId\":\"0\",\"other\":\"1363787904\",\"ratio\":\"0.008916\"},{\"idcId\":\"0\",\"other\":\"1363787906\",\"ratio\":\"0.000010\"},{\"idcId\":\"0\",\"other\":\"1365487330\",\"ratio\":\"0.000030\"},{\"idcId\":\"0\",\"other\":\"1365812526\",\"ratio\":\"0.000170\"},{\"idcId\":\"0\",\"other\":\"1377406885\",\"ratio\":\"0.000017\"},{\"idcId\":\"0\",\"other\":\"1397167434\",\"ratio\":\"0.000005\"},{\"idcId\":\"0\",\"other\":\"1410593798\",\"ratio\":\"0.000007\"},{\"idcId\":\"0\",\"other\":\"1415418005\",\"ratio\":\"0.000017\"},{\"idcId\":\"0\",\"other\":\"1418227255\",\"ratio\":\"0.001442\"},{\"idcId\":\"0\",\"other\":\"1454807250\",\"ratio\":\"0.000012\"},{\"idcId\":\"0\",\"other\":\"1470236061\",\"ratio\":\"0.000010\"},{\"idcId\":\"0\",\"other\":\"1494645593\",\"ratio\":\"0.000203\"},{\"idcId\":\"0\",\"other\":\"1494894929\",\"ratio\":\"0.000002\"},{\"idcId\":\"0\",\"other\":\"1496412425\",\"ratio\":\"0.000007\"},{\"idcId\":\"0\",\"other\":\"1504984159\",\"ratio\":\"0.000010\"},{\"idcId\":\"0\",\"other\":\"1521299452\",\"ratio\":\"0.567281\"},{\"idcId\":\"0\",\"other\":\"1622951403\",\"ratio\":\"0.000017\"},{\"idcId\":\"0\",\"other\":\"1692022008\",\"ratio\":\"0.000030\"},{\"idcId\":\"0\",\"other\":\"1979482930\",\"ratio\":\"0.000057\"},{\"idcId\":\"0\",\"other\":\"2031498263\",\"ratio\":\"0.000010\"},{\"idcId\":\"0\",\"other\":\"60009\",\"ratio\":\"0.000030\"}]}";

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
                            
                            if (0 == strcmp(itKey->value.GetString(), "NULL"))
                            {
                                cout << "find NULL" << endl;
                            }
                                                      
                            cout << "key : " << itKey->value.GetString() << ", size = " << itKey->value.GetStringLength() <<",type =  " << itKey->value.GetType() << endl;
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
    cout << "into getValue" << endl;
    rapidjson::Document document;
    document.Parse(valueStr.c_str());
    cout << "Parse ok" << endl;

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
        cout << "============ 1" << endl;
        const rapidjson::Value& childValue = document["object"];
        cout << "============ 2" << endl;
        if (childValue.HasMember("data"))
        {
            cout << "============ 3" << endl;
            const rapidjson::Value& dataValue = childValue["data"];
            
            cout << "============ 4" << endl;
            if (dataValue.IsArray() && dataValue.Size() > 0)
            {
                for (size_t i = 0; i < dataValue.Size(); i++)
                {
                    const rapidjson::Value& array = dataValue[i];

                    if (array[1].IsUint64())
                    {
                        cout << array[1].GetUint64() << endl;
                    }

                    /*if (false == array[1].IsNull() && array[1].IsUint64())
                    {
                        cout << array[1].GetUint64() << endl;
                    }*/
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


bool getValuePro(std::string valueStr)
{
    rapidjson::Document document;
    document.Parse(valueStr.c_str());

    rapidjson::Value::ConstMemberIterator iter = document.FindMember("code");
    if (iter != document.MemberEnd()) {
        //cout << "code : " << iter->value.GetInt() << endl;
        //std::cout << "failed to getValue!" << std::endl;
        // todo 判断是不是0
    }
    else {
        //FUNLOG(Error, "Not find code", NULL);
        return false;
    }

    iter = document.FindMember("success");
    if (iter != document.MemberEnd()) {
        //cout << "success : " << iter->value.GetBool() << endl;
        bool ret = iter->value.GetBool();
        if (false == ret)
        {
            //FUNLOG(Error, "query result is : false", NULL);
            return false;
        }
    }
    else {
        //FUNLOG(Error, "Not find success", NULL);
        return false;
    }

    std::string uri;
    uint64_t sum = 0;
    uint64_t count = 0;

    if (document.HasMember("object"))
    {
        cout << "=============== 1" << endl;
        const rapidjson::Value& childValue = document["object"];

        if (childValue.HasMember("param"))
        {
            const rapidjson::Value& paramValue = childValue["param"];
            rapidjson::Value::ConstMemberIterator chileIter = paramValue.FindMember("uri");
            if (chileIter != paramValue.MemberEnd()) {
                uri = chileIter->value.GetString();
            }
        }

        cout << "=============== 2" << endl;

        if (childValue.HasMember("data"))
        {

            cout << "=============== 3" << endl;

            const rapidjson::Value& dataValue = childValue["data"];

            cout << "=============== 4" << endl;

            if (dataValue.IsArray() && dataValue.Size() > 0)
            {
                cout << "=============== 5" << endl;
                count = dataValue.Size();

                for (size_t i = 0; i < dataValue.Size(); i++)
                {
                    const rapidjson::Value& array = dataValue[i];

                    if (array[0].IsUint64())
                    {
                        cout << "time : " << array[0].GetUint64() << endl;
                    }

                    if (false == array[1].IsNull() && array[1].IsUint64())
                    {
                        cout << "=============== 6, " << array[1].GetUint64() << endl;
                        sum += array[1].GetUint64();
                    }
                }
            }
            else {
                //FUNLOG(Error, "Not find array", NULL);
                return false;
            }
        }
        else {
            //FUNLOG(Error, "Not find data", NULL);
            return false;
        }
    }
    else {
        //FUNLOG(Error, "Not find object", NULL);
        return false;
    }

    return true;
}

void getTimeForCostJson(std::string& timeStamp, std::string& ym)
{
    // 获取时间
    char now[64];
    memset(now, 0, 64);

    time_t tnow = time(0);
    struct tm* ttime;
    ttime = localtime(&tnow);
    strftime(now, 64, "%Y-%m-%d %H:%M:%S", ttime);

    timeStamp = std::string(now);

    // last month
    time_t nSeconds;
    time(&nSeconds); // 同 nSeconds = time(NULL);

    struct tm* pTM;
    pTM = localtime(&nSeconds);

    //cout << "year : " << pTM->tm_year + 1900 << endl;
    //cout << "mon :" << pTM->tm_mon + 1 << endl;
    //cout << "day :" << pTM->tm_mday << endl;

    char psDate[100] = { 0 };

    int year = (pTM->tm_mon > 0) ? (pTM->tm_year + 1900) : (pTM->tm_year + 1899);
    int lastMonth = (pTM->tm_mon > 0) ? pTM->tm_mon : 12;
    /* 系统日期,格式:YYYMMDD */
    sprintf(psDate, "%04d-%02d", year, lastMonth);

    //cout << psDate << endl;
    ym = std::string(psDate);
}

std::string getSignForCostJson(std::string appId, std::string appKey, std::string apiDate)
{
    std::string str = appId + appKey + apiDate;

    unsigned char digest[SHA_DIGEST_LENGTH];
    SHA1((unsigned char*)(str.c_str()), str.length(), (unsigned char*)&digest);

    char mdString[SHA_DIGEST_LENGTH * 2 + 1] = { 0 };

    for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);

    return std::string(mdString, SHA_DIGEST_LENGTH * 2);
}

const std::string appId = "costUser";
const std::string appKey = "EDFS#43!ff09";

void getSign()
{
    std::string timeStamp;
    std::string ym;
    getTimeForCostJson(timeStamp, ym);

    std::string apiDate = timeStamp;
    std::string yyyyMM = ym;

    std::string sign = getSignForCostJson(appId, appKey, apiDate);

    cout << "apiDate : " << apiDate << endl;
    cout << "sign : " << sign << endl;
}

// 判断两个时间戳是同一天
int isSameDay(time_t t1, time_t t2)
{
    struct tm stm1 = { 0 };
    localtime_r(&t1, &stm1);
    int day1 = stm1.tm_mday;

    struct tm stm2 = { 0 };
    localtime_r(&t2, &stm2);
    int day2 = stm2.tm_mday;

    if (day1 == day2)
    {
        return 0;
    }
    else if (day1 < day2){
        return -1;
    }
    else {
        return 1;
    }
}

void testV5(std::string jstr)
{
    std::cout << "into testV5" << std::endl;
    float sum = 0;

    rapidjson::Document document;
    document.Parse(v5.c_str());
    std::cout << "Parse ok" << std::endl;

    rapidjson::Value::ConstMemberIterator iter = document.FindMember("data");
    if (iter != document.MemberEnd()) {
        const rapidjson::Value& childValue = document["data"];

        if (childValue.IsArray() && childValue.Size() > 0)
        {
            for (size_t i = 0; i < childValue.Size(); i++)
            {
                const rapidjson::Value& obj = childValue[i];

                if (obj.HasMember("ratio"))
                {
                    const rapidjson::Value& rt = obj["ratio"];
                    
                    std::string rtstr = rt.GetString();
                    float f;

                    std::stringstream sStream;
                    sStream << rtstr;
                    sStream >> f;

                    sum += f;
                }
                
            }
        }
    }
    
    printf("sum = %f\n", sum);
    cout << "sum = " << sum << endl;
}


void strsplit(const std::string& s, char c,
    std::vector<std::string>& v) {
    std::string::size_type i = 0;
    std::string::size_type j = s.find(c);

    while (j != std::string::npos) {
        v.push_back(s.substr(i, j - i));
        i = ++j;
        j = s.find(c, j);

        if (j == std::string::npos)
            v.push_back(s.substr(i, s.length()));
    }
}


int main()
{
    std::string str = "10309,60009";

    //getKeyList(rspStr);

    cout << "===============" << endl;

    std::vector<std::string> ve;

    strsplit(str, ',', ve);

    for (auto x : ve)
    {
        cout << x << endl;
    }


    //testV5();

    //getKeyList(value4);

    //getValuePro(value2);

    //getValuePro(value3);


    //cout << isSameDay(1583206456, 1583201456) << endl;

    /*
    std::string zeroStr = "0.000000";
    float f_ok = 0.0002;
    double f_not0 = 0.0000099;
    float f_not = f_not0;

    int iok = f_ok * 1000000;
    int inot = f_not * 1000000;

    cout << "iok :" << iok << endl;
    cout << "inot :" << inot << endl;

    float x = inot;
    cout << "x :" << x << endl;
    printf("x : %f\n", x);

    float f2 = (float)(iok) / 1000000.0;
    printf("f2 : %f\n", f2);
    cout << "f2 : " << f2 << endl;

    float f3 = (float)(inot) / 1000000.0;
    printf("f3 : %f\n", f3);
    cout << "f3 : " << f3 << endl;

    //char dst[10] = { 0 };
    //sprintf(dst, "%.3f", f);

    std::string value;
    std::stringstream sStream;
    sStream << fixed << std::setprecision(6) << f2;
    sStream >> value;

    cout << "value = " << value << endl;
    printf("f2 = %f, value = %s\n", f2, value.c_str());

    std::string value0;
    std::stringstream sStream0;
    sStream0 << fixed << std::setprecision(6) << f3;
    sStream0 >> value0;

    cout << "value0 = " << value0 << endl;
    printf("f3 = %f, value = %s\n", f3, value0.c_str());

    //if (0 == zeroStr.compare(value))
    //{
    //    cout << " yes ,  Equal to 0" << endl;


    //}
    //else {
    //    cout << " Not Equal to 0" << endl;


    //}
    */


    return 0;
}
