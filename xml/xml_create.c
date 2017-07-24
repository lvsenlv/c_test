/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2017年02月09日 星期四 10时16分02秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <libxml/parser.h>

#define     XML_FILE_PATH       "/root/test"
#define 	XML_FILE_NAME 		"/root/test/1.xml"
#define 	BUF_SIZE 			128

#ifndef _DEBUG_0
#ifndef _DEBUG_1
#ifndef _DEBUG_2
char *str[] = {
    XML_FILE_PATH,
    "_DEBUG_0 : simple example of creating 1.xml",
    "_DEBUG_1 : complex example of creating 1.xml",
    "_DEBUG_2 : middle example of creating 1.xml",
    NULL,
};

int main(int argc, char **argv)
{
    char **ptr = str;

    while(*ptr)
        printf("%s \n", *ptr++);

    return 0;
}

#endif
#endif
#endif

#ifdef _DEBUG_2
int main(int argc, char **argv)
{
	char buf[BUF_SIZE] = {0};	
    if(!opendir(XML_FILE_PATH))
    {
		snprintf(buf, sizeof(buf), "mkdir -p %s", XML_FILE_PATH);
        system(buf);
    }
	if(!access(XML_FILE_NAME, F_OK))
	{
		snprintf(buf, sizeof(buf), "rm %s", XML_FILE_NAME);
		system(buf);
	}
	
	xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
	xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "all_products");
	xmlDocSetRootElement(doc ,root_node);

	xmlNodePtr node = NULL, tmp_node = NULL;
	node = xmlNewNode(NULL, BAD_CAST "products");
	xmlAddChild(root_node, node);
	tmp_node = xmlNewNode(NULL, BAD_CAST "product");
	xmlNewProp(tmp_node, BAD_CAST "name", BAD_CAST "name11");
	xmlNewProp(tmp_node, BAD_CAST "value", BAD_CAST "value11");
	xmlAddChild(tmp_node, xmlNewText(BAD_CAST "content11"));
	xmlAddChild(node, tmp_node);
	tmp_node = xmlNewNode(NULL, BAD_CAST "product");
	xmlNewProp(tmp_node, BAD_CAST "name", BAD_CAST "name12");
	xmlNewProp(tmp_node, BAD_CAST "value", BAD_CAST "value12");
	xmlAddChild(tmp_node, xmlNewText(BAD_CAST "content12"));
	xmlAddChild(node, tmp_node);
	tmp_node = xmlNewNode(NULL, BAD_CAST "product");
	xmlNewProp(tmp_node, BAD_CAST "name", BAD_CAST "name13");
	xmlNewProp(tmp_node, BAD_CAST "value", BAD_CAST "value13");
	xmlAddChild(tmp_node, xmlNewText(BAD_CAST "content13"));
	xmlAddChild(node, tmp_node);
	tmp_node = xmlNewNode(NULL, BAD_CAST "product");
	xmlNewProp(tmp_node, BAD_CAST "name", BAD_CAST "name14");
	xmlNewProp(tmp_node, BAD_CAST "value", BAD_CAST "value14");
	xmlAddChild(tmp_node, xmlNewText(BAD_CAST "content14"));
	xmlAddChild(node, tmp_node);

	node = xmlNewNode(NULL, BAD_CAST "products");
	xmlAddChild(root_node, node);
	tmp_node = xmlNewNode(NULL, BAD_CAST "product");
	xmlNewProp(tmp_node, BAD_CAST "name", BAD_CAST "name21");
	xmlNewProp(tmp_node, BAD_CAST "value", BAD_CAST "value21");
	xmlAddChild(tmp_node, xmlNewText(BAD_CAST "content21"));
	xmlAddChild(node, tmp_node);
	tmp_node = xmlNewNode(NULL, BAD_CAST "product");
	xmlNewProp(tmp_node, BAD_CAST "name", BAD_CAST "name22");
	xmlNewProp(tmp_node, BAD_CAST "value", BAD_CAST "value22");
	xmlAddChild(tmp_node, xmlNewText(BAD_CAST "content22"));
	xmlAddChild(node, tmp_node);
	tmp_node = xmlNewNode(NULL, BAD_CAST "product");
	xmlNewProp(tmp_node, BAD_CAST "name", BAD_CAST "name23");
	xmlNewProp(tmp_node, BAD_CAST "value", BAD_CAST "value23");
	xmlAddChild(tmp_node, xmlNewText(BAD_CAST "content23"));
	xmlAddChild(node, tmp_node);

	node = xmlNewNode(NULL, BAD_CAST "products");
	xmlAddChild(root_node, node);
	tmp_node = xmlNewNode(NULL, BAD_CAST "product");
	xmlNewProp(tmp_node, BAD_CAST "name", BAD_CAST "name31");
	xmlNewProp(tmp_node, BAD_CAST "value", BAD_CAST "value31");
	//xmlAddChild(tmp_node, xmlNewText(BAD_CAST "content31"));
	xmlAddChild(node, tmp_node);
	tmp_node = xmlNewNode(NULL, BAD_CAST "product");
	xmlNewProp(tmp_node, BAD_CAST "name", BAD_CAST "name32");
	xmlNewProp(tmp_node, BAD_CAST "value", BAD_CAST "value32");
	//xmlAddChild(tmp_node, xmlNewText(BAD_CAST "content32"));
	xmlAddChild(node, tmp_node);

	xmlSaveFormatFileEnc(XML_FILE_NAME, doc, "UTF-8", 1);
	xmlFreeDoc(doc);

	return 0;
}
#endif //_DEBUG_2

#ifdef _DEBUG_1
extern char *xml_strings[];

int main(int argc, char **argv)
{
	char buf[BUF_SIZE] = {0};	
    if(!opendir(XML_FILE_PATH))
    {
		snprintf(buf, sizeof(buf), "mkdir -p %s", XML_FILE_PATH);
        system(buf);
    }
	if(!access(XML_FILE_NAME, F_OK))
	{
		snprintf(buf, sizeof(buf), "rm %s", XML_FILE_NAME);
		system(buf);
	}

	xmlDocPtr doc = NULL;
	xmlNodePtr root_node = NULL, node = NULL, tmp_node = NULL;
	int i = 0;

	doc = xmlNewDoc(BAD_CAST "1.0");
	root_node = xmlNewNode(NULL, BAD_CAST "config");
	xmlDocSetRootElement(doc, root_node);

	node = xmlNewNode(NULL, BAD_CAST "language");
	xmlNewProp(node, BAD_CAST "name", BAD_CAST "zh_CN");
	xmlAddChild(root_node, node);

	while(xml_strings[i])
	{
		tmp_node = xmlNewChild(node, NULL, BAD_CAST "string", BAD_CAST xml_strings[i]);
		snprintf(buf, sizeof(buf), "%d", i++);
		xmlNewProp(tmp_node, BAD_CAST "number", BAD_CAST buf);
		xmlNewProp(tmp_node, BAD_CAST "encoding", BAD_CAST "UTF-8");
	}

	xmlSaveFormatFileEnc(XML_FILE_NAME, doc, "UTF-8", 1);
	xmlFreeDoc(doc);

	return 0;
}
#endif //_DEBUG_1

#ifdef _DEBUG_0
int main(void)
{
	char buf[BUF_SIZE] = {0};	
    if(!opendir(XML_FILE_PATH))
    {
		snprintf(buf, sizeof(buf), "mkdir -p %s", XML_FILE_PATH);
        system(buf);
    }
	if(!access(XML_FILE_NAME, F_OK))
	{
		snprintf(buf, sizeof(buf), "rm %s", XML_FILE_NAME);
		system(buf);
	}
	
	xmlDocPtr doc = NULL;
	xmlNodePtr root_node = NULL, node = NULL, tmp_node = NULL;

	//create xml document, root node
	doc = xmlNewDoc(BAD_CAST "1.0");
	root_node = xmlNewNode(NULL, BAD_CAST "root");
	xmlDocSetRootElement(doc, root_node);
	

	//create a node attaching to root node
	xmlNewChild(root_node, NULL, BAD_CAST "node1", BAD_CAST "content of node1");
	//create attributes
	node = xmlNewChild(root_node, NULL, BAD_CAST "node2", BAD_CAST "content of node1");
	xmlNewProp(node, BAD_CAST "node2_attribute", BAD_CAST "yes");

	//another way to create node	
	node = xmlNewNode(NULL, BAD_CAST "node11");
	tmp_node = xmlNewText(BAD_CAST "content of node11");
	xmlAddChild(node, tmp_node);
	xmlAddChild(root_node, node);
	
	node = xmlNewNode(NULL, BAD_CAST "node22");
	tmp_node = xmlNewText(BAD_CAST "content of node22");
	xmlAddChild(node, tmp_node);
	xmlNewProp(node, BAD_CAST "node22_attribute", BAD_CAST "yes");
	xmlAddChild(root_node, node);

	
	//dump document to stdio or file
	xmlSaveFormatFileEnc(XML_FILE_NAME, doc, "UTF-8", 1);

	//free the document
	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();

	
    return 0;
}
#endif //_DEBUG_0

char *xml_strings[] = {
"系统文件损坏，请联系管理员！",
"与服务器通讯异常，请与管理员联系！",
"您的网络可能已经断开！",
"请输入用户名！",
"用户所属域不存在！",
"连接超时！",
"用户未分配资源，请与管理员联系！",
"*请联系网络管理员获取域名信息",
"记住密码",
"自动登录",
"正在配置IP......",
"配置IP失败......",
"网络配置失败！",
"断开服务器......",
"找不到服务器，请检查网络或服务器地址！",
"确定立即关机？",
"您的账号在另一地点登录，您被迫下线。如果这不是您本人的操作，那么您的密码可能已经泄露。建议修改密码确保账户安全。",
"用户名或密码错误！",
"退出",
"系统时间",
"正在升级中请稍后！",
"开",
"关",
"提示",
"确认",
"用户名",
"原始密码",
"新密码",
"确认密码",
"请输入密码",
"*请输入密码",
"*请输入用户名",
"*请输入旧密码",
"*请输入原始密码",
"*请输入新密码",
"*请再次输入新密码",
"*请输入确认密码",
"*两次输入的密码不一致",
"*您输入的密码过于简单",
"*密码长度至少为6位",
"您的密码已修改成功！",
"*密码输入错误，请重新输入",
"*原始密码输入错误",
"*连接超时",
"*用户名或密码错误",
"修改密码成功，请用新密码登录！",
"*修改密码失败！",
"请使用管理员身份登录进行操作！",
"不是有效项。请指定一个介于 0 - 255 之间的值！",
"不是有效项。请指定一个除 127 以外并介于 1-223 之间的值！",
"不是有效项。请指定一个介于 1-223 之间的值！",
"IP获取失败，请检查网络！",
"请输入密码！",
"IP地址（",
"）不冲突，可以正常使用！",
"）与网络上其他设备存在冲突，请确认并修改！",
"开机操作执行失败，请联系您的管理员！",
"首选 DNS 服务器",
"备用 DNS 服务器",
"自动获得DNS服务器地址",
"使用下面的DNS服务器地址",
"IP 地址",
"子网掩码",
"默认网关",
"自动获得IP地址",
"使用下面的IP地址",
"IP地址是否冲突?",
"立即检查",
"ping",
"如果网络支持此功能,则可以获取自动指派的IP设置,否则,您需要从网络系统管理员处获得适当的IP设置",
"请输入完整的IP地址！",
"请输入一个IP地址！",
"请输入完整的子网掩码！",
"所输入的地址缺少子网掩码。请添加子网掩码！",
"请输入完整的网关地址！",
"请输入完整的DNS服务器地址！",
"请指定一个DNS服务器地址！",
"输入主机名或IP:",
"请指定一个",
"的IP地址或域名！",
"请输入一个合法的端口号，取值（0～65535）！",
"IP地址或域名",
"端口",
"https端口",
"自动发现服务器",
"指定服务器 (IP地址或域名)",
"云电脑服务",
"系统设定",
"网络设置",
"服务器",
"系统设置",
"软件升级",
"修改密码",
"系统信息",
"设备型号",
"内核版本号",
"硬件序列号",
"网络地址",
"物理地址",
"软件版本号",
"正在保存设置，请稍等...",
"您使用的VGA线无法获取显示器支持的最大分辨率，强制设置可能引起黑屏，确定要设置吗？",
"您所选择的分辨率超出了当前显示器支持的最大分辨率",
"，请重新选择！",
"分辨率设置需要重启，确定立即设置并重启？",
"屏幕分辨率",
"自动选择最佳分辨率",
"手动选择分辨率",
"休眠模式",
"1分钟",
"10分钟",
"30分钟",
"1小时",
"从不",
"允许远程连接控制这台设备",
"升级确认",
"升级需要重启系统，请确保在升级期间电源保持接通，USB设备保持连接，否则可能会导致系统无法正常启动。确定是否立即升级？",
"例：192.168.66.42:8080",
"请指定升级路径！",
"无效的升级路径，请检查网络或服务器地址！",
"升级地址",
"自动升级",
"适合办公应用",
"适合看视频娱乐",
"适合窄带宽视频(需要硬件支持)",
"若长时间未成功，请尝试强制重启或者联系管理员。",
"不能获取组虚拟机，请与网络管理员联系！",
"请注意！虚拟机将不保存数据，直接断电！是否确定立即关闭虚拟机？",
"请注意！虚拟机将不保存数据，直接断电重启！是否确定立即重启虚拟机？",
"连接方式",
"强制重启",
"执行中...",
"自动开机",
"开机",
"开机中...",
"关机",
"关机中...",
"暂停",
"丢失",
"准备中...",
"离线",
"连接操作失败，请联系您的管理员！",
"RDP",
"GROUP",
"PC",
"请插入U盘！",
"挂载U盘失败！",
"没有可以执行的升级文件，请确认！",
"无效的端口号，请检查端口输入是否正确！",
"当前使用的软件已是最新版本！",
"服务器版本不兼容，无法进行更新检查，如需升级，请联系管理员！",
"读取版本信息失败，无法进行升级！",
"当前版本为",
"，可升级的版本为",
"，是否立即升级？",
"Tancer Desktop",
"Tancer Device Manager",
"当前虚拟机不存在于当前服务器中，无法执行操作！",
"当前虚拟机已开机，无法执行开机操作！",
"当前虚拟机已关机，无法执行强制关机操作！",
"当前虚拟机已暂停，无法执行暂停操作！",
"当前虚拟机已暂停，无法执行开机操作！",
"当前服务器内存不足，无法执行恢复操作！",
"当前服务器内存不足，无法执行开机操作！",
"当前虚拟机状态未知。",
"当前虚拟机已关机，无法执行强制重启操作！",
"当前虚拟机已关机，无法执行恢复操作！",
"3Tcloud-X900-P",
"设置",
"连接协议",
"CHP",
"RDP",
"设备和资源",
"打印机",
"USB设备",
"性能",
"与连接质量相关的功能",
"桌面背景",
"字体平滑",
"桌面合成",
"拖动时显示窗口内容",
"菜单和窗口动画",
"视觉样式",
"持久位图缓存",
"如果连接中断，则重新连接",
"调制解调器 (56 Kbps)",
"低速宽带 (256 Kbps - 2 Mbps)",
"卫星 (2 Mbps - 16 Mbps，高延迟)",
"高速宽带 (2 Mbps - 10 Mbps)",
"WAN (10 Mbps或更高速度，高延迟)",
"局域网 (10 Mbps或更高)",
"自动检测连接质量",
"update.3tcloud.com",
"允许以下功能",
"独享",
"共享",
"应用",
"连接设置",
"宽带(PPPoE)",
"状态:",
"密码",
"自动连接",
"连接成功",
"已断开连接",
"连接失败,请与管理员联系",
"断开连接失败,请与管理员联系",
"个字符",
"新密码最少为",
"最大为",
"你修改密码过于频繁，请于",
"分钟后再试",
"修改的密码不能和前",
"次相同",
"您的帐号已经被锁定，请等待解锁后重新登陆",
"您在规定时间内密码输入错误次数已达到上限，锁定当前ip：",
"您已输错密码",
"次",
"输入密码错误次数达到",
"该用户将被锁定",
"许可已经达到上限，如需要连接虚拟机，请联系管理员",
"请确认当前学生机的座位号！",
"请输入座位号",
"*座位号不能为空",
NULL,
};//char *xml_strings[]

