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

#define 	XML_FILE_NAME 			"/root/test/1.xml"
#define 	XML_XPATH_STR 			"/config/language/string"

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
	xmlChar *xpath = BAD_CAST XML_XPATH_STR;
	
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

	xmlXPathObjectPtr result = parse_xpath_node(doc, xpath); 
	if(!result)
	{
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return -1;
	}
	
	xmlNodeSetPtr nodeset = result->nodesetval;
	xmlChar *name = NULL, *value = NULL;
	int i = 0, nodeNr = nodeset->nodeNr;
	printf("*** nodeset->nodeNr = %d ***\n", nodeNr);

	for(i = 0; i < nodeNr; i++)
	{
		cur = nodeset->nodeTab[i];
		printf("cur->name = %s\t", cur->name);
		cur = cur->children;
		while(cur)
		{
			//if(xmlStrcmp(cur->name, BAD_CAST "text"))
			//{
				//printf("cur->name = %s\t", cur->name);
				value = xmlGetProp(cur, BAD_CAST "number");
				printf("value = %s \n", value);
				xmlFree(name);
				xmlFree(value);
			//}
			cur = cur->next;
		}
		printf("\n");
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

