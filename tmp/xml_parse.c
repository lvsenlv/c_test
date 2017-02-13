/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2017年02月10日 星期五 14时16分54秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
//#include <string.h>

#define 	XML_FILE_NAME 			"/root/test/signed.xml"
#define 	XML_XPATH_STR 			"/resources"
#define 	XML_PROP1_STR 			"checksum"
#define 	XML_PROP2_STR 			"path"

xmlXPathObjectPtr parse_xpath_node(xmlDocPtr doc, xmlChar *xpath);

int main(int argc, char **argv)
{
	if(access(XML_FILE_NAME, F_OK))
	{
		fprintf(stderr, "*** %s does not exist ***\n", XML_FILE_NAME);
		return -1;
	}

	xmlDocPtr doc = NULL;
	xmlNodePtr cur = NULL;
	
	doc = xmlParseFile(XML_FILE_NAME);
	if(!doc)
	{
		fprintf(stderr, "*** failed to parse %s ***\n", XML_FILE_NAME);
		return -1;
	}

	cur = xmlDocGetRootElement(doc);
	if(!cur)
	{
		fprintf(stderr, "*** document is empty ***\n");
		return -1;
	}
	printf("root node : %s \n", cur->name);

	xmlXPathObjectPtr result = parse_xpath_node(doc, BAD_CAST XML_XPATH_STR); 
	if(!result)
	{
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return -1;
	}
	
	xmlNodeSetPtr nodeset = result->nodesetval;
	xmlChar *prop1 = NULL, *prop2 = NULL;
	int i = 0, node_num = nodeset->nodeNr;
	printf("number of node : %d \n", node_num);

	for(i = 0; i < node_num; i++)
	{
		cur = nodeset->nodeTab[i];
		printf("node name : %s \n", cur->name);
		cur = cur->children;
		while(cur)
		{
			if(xmlStrcmp(cur->name, BAD_CAST "text")) //if cur->name != "text"
			{
				printf("%s : \n", cur->name);
				prop1 = xmlGetProp(cur, BAD_CAST XML_PROP1_STR);
				printf("%s = %s \t", XML_PROP1_STR, prop1);
				prop2 = xmlGetProp(cur, BAD_CAST XML_PROP2_STR);
				printf("%s = %s \t", XML_PROP2_STR, prop2);
				if(cur->children)
					printf("content = %s \t", cur->children->content);
				xmlFree(prop1);
				xmlFree(prop2);
				printf("\n\n");
			}
			cur = cur->next;
		}
		printf("\n\n");
	}
	
	xmlXPathFreeObject(result);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	
	return 0;
}

xmlXPathObjectPtr parse_xpath_node(xmlDocPtr doc, xmlChar *xpath)
{
	xmlXPathContextPtr context = NULL;
	xmlXPathObjectPtr result = NULL;

	context = xmlXPathNewContext(doc);
	if(!context)
	{
		fprintf(stderr, "*** error in xmlXPathNewContext() ***");
		return NULL;
	}

	result = xmlXPathEvalExpression(xpath, context);
	xmlXPathFreeContext(context);
	if(!result)
	{
		fprintf(stderr, "*** error in xmlXPathEvalExpression() ***");
		return NULL;
	}
	
	if(xmlXPathNodeSetIsEmpty(result->nodesetval))
	{
		xmlXPathFreeObject(result);
		fprintf(stderr, "*** no result ***\n");
		return NULL;
	}

	return result;
}

