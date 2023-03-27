#include "XMLHelper.h"
#include <windows.h>
#include <fstream>

// Helper
// ============================================
bool beUtf8(const char* str);

std::string XMLHelper::ConvertUTF8ToGB2312(const char* i_utf8)
{
	if (!beUtf8(i_utf8))
	{
		std::string t = i_utf8;
		return t;
	}

	int len = MultiByteToWideChar(CP_UTF8, 0, i_utf8, -1, NULL, 0);

	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);

	MultiByteToWideChar(CP_UTF8, 0, i_utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);

	char* str = new char[len + 1];
	memset(str, 0, len + 1);

	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);

	if (wstr)
	{
		delete[] wstr;
		wstr = NULL;
	}

	return str;
}

unsigned int countGBK(const char* str)
{
	unsigned int len = (unsigned int)strlen(str);
	unsigned int counter = 0;
	unsigned char head = 0x80;
	unsigned char firstChar, secondChar;

	for (unsigned int i = 0; i < len - 1; ++i)
	{
		firstChar = (unsigned char)str[i];
		if (!(firstChar & head))continue;
		secondChar = (unsigned char)str[i];
		if (firstChar >= 161 && firstChar <= 247 && secondChar >= 161 && secondChar <= 254)
		{
			counter += 2;
			++i;
		}
	}
	return counter;
}

unsigned int countUTF8(const char* str)
{
	unsigned int len = (unsigned int)strlen(str);
	unsigned int counter = 0;
	unsigned char head = 0x80;
	unsigned char firstChar;
	for (unsigned int i = 0; i < len; ++i)
	{
		firstChar = (unsigned char)str[i];
		if (!(firstChar & head))continue;
		unsigned char tmpHead = head;
		unsigned int wordLen = 0, tPos = 0;
		while (firstChar & tmpHead)
		{
			++wordLen;
			tmpHead >>= 1;
		}
		if (wordLen <= 1)continue; //utf8 minimum length is 2
		wordLen--;
		if (wordLen + i >= len)break;
		for (tPos = 1; tPos <= wordLen; ++tPos)
		{
			unsigned char secondChar = (unsigned char)str[i + tPos];
			if (!(secondChar & head))break;
		}
		if (tPos > wordLen)
		{
			counter += wordLen + 1;
			i += wordLen;
		}
	}
	return counter;
}

bool beUtf8(const char* str)
{
	unsigned int iGBK = countGBK(str);
	unsigned int iUTF8 = countUTF8(str);
	if (iUTF8 > iGBK)return true;
	return false;
}

void XMLHelper::ConvertUTF8ToGB2312ForDoc(tinyxml2::XMLDocument* i_doc)
{
	tinyxml2::XMLElement* pRootElement = i_doc->RootElement();

	if (pRootElement != NULL)
	{
		// Convert Title
		tinyxml2::XMLElement* pTitle = pRootElement->FirstChildElement("Title");
		
		if (pTitle != NULL)
		{
			// set name
			tinyxml2::XMLElement* pTitleInfo = pTitle->FirstChildElement("Name");
			pTitleInfo->SetText(ConvertUTF8ToGB2312(pTitleInfo->GetText()).c_str());

			// set Chinese
			pTitleInfo = pTitle->FirstChildElement("Chinese");
			pTitleInfo->SetText(ConvertUTF8ToGB2312(pTitleInfo->GetText()).c_str());

			// set English
			pTitleInfo = pTitle->FirstChildElement("English");
			pTitleInfo->SetText(ConvertUTF8ToGB2312(pTitleInfo->GetText()).c_str());

			// set Math
			pTitleInfo = pTitle->FirstChildElement("Math");
			pTitleInfo->SetText(ConvertUTF8ToGB2312(pTitleInfo->GetText()).c_str());
		}

		tinyxml2::XMLElement* pDatas = pRootElement->FirstChildElement("Datas");

		if (pDatas != NULL)
		{
			tinyxml2::XMLElement* pData = pDatas->FirstChildElement("Data");

			while (pData)
			{
				// set name
				tinyxml2::XMLElement* pDataInfo = pData->FirstChildElement("Name");
				pDataInfo->SetText(ConvertUTF8ToGB2312(pDataInfo->GetText()).c_str());

				// set Chinese
				pDataInfo = pData->FirstChildElement("Chinese");
				pDataInfo->SetText(ConvertUTF8ToGB2312(pDataInfo->GetText()).c_str());

				// set English
				pDataInfo = pData->FirstChildElement("English");
				pDataInfo->SetText(ConvertUTF8ToGB2312(pDataInfo->GetText()).c_str());

				// set Math
				pDataInfo = pData->FirstChildElement("Math");
				pDataInfo->SetText(ConvertUTF8ToGB2312(pDataInfo->GetText()).c_str());

				pData = pData->NextSiblingElement("Data");
			}
		}
	}
}

std::vector<std::string> XMLHelper::GetElementArray(tinyxml2::XMLDocument* i_doc, std::string i_syntax)
{
	tinyxml2::XMLElement* pRootElement = i_doc->RootElement();
	std::vector<std::string> retValue;

	if (pRootElement != NULL)
	{
		tinyxml2::XMLElement* pDatas = pRootElement -> FirstChildElement("Datas");

		if (pDatas != NULL)
		{
			tinyxml2::XMLElement* pData = pDatas -> FirstChildElement("Data");

			while (pData)
			{
				// Get i_syntax Child
				tinyxml2::XMLElement* pDataInfo = pData -> FirstChildElement(i_syntax.c_str());

				if (pDataInfo != NULL)
				{
					const char* dataText = pDataInfo->GetText();
					retValue.push_back(ConvertUTF8ToGB2312(dataText));
				}

				pData = pData -> NextSiblingElement("Data");
			}
		}
	}

	return retValue;
}

void XMLHelper::InsertXMLFromInput(std::string i_path, std::vector<std::string> i_argument)
{
	tinyxml2::XMLDocument doc;

	doc.LoadFile(i_path.c_str());

	// Before we insert anything, we need to convert all data from uft-8 to GB2312
	ConvertUTF8ToGB2312ForDoc(&doc);

	// Get root Element
	tinyxml2::XMLElement* pRootElement = doc.RootElement();
	// Get 'Datas' Child
	tinyxml2::XMLElement* pDatas = pRootElement-> FirstChildElement("Datas");
	// Create new Element
	tinyxml2::XMLNode* pRoot;
	tinyxml2::XMLElement* pElement;

	for (size_t index = 0; index < i_argument.size(); index += 4)
	{
		pRoot = doc.NewElement("Data");
		pDatas->InsertEndChild(pRoot);

		// Name
		pElement = doc.NewElement("Name");
		pElement->SetText(i_argument[index].c_str());
		pRoot->InsertEndChild(pElement);

		// Chinese
		pElement = doc.NewElement("Chinese");
		pElement->SetText(i_argument[index + 1].c_str());
		pRoot->InsertEndChild(pElement);

		// English
		pElement = doc.NewElement("English");
		pElement->SetText(i_argument[index + 2].c_str());
		pRoot->InsertEndChild(pElement);

		// Math
		pElement = doc.NewElement("Math");
		pElement->SetText(i_argument[index + 3].c_str());
		pRoot->InsertEndChild(pElement);

		std::cout << "insert: <" << i_argument[index] << "," << i_argument[index + 1] << "," << i_argument[index + 2] << "," << i_argument[index + 3] << "> to " << i_path << std::endl;
	}

	//Save the changes into the XML file
	doc.SaveFile(i_path.c_str());
}

void XMLHelper::InsertXMLFromFile(std::string i_sourcePath, std::string i_insertPath)
{
	tinyxml2::XMLDocument sourceDoc;
	tinyxml2::XMLDocument insertDoc;

	sourceDoc.LoadFile(i_sourcePath.c_str());
	insertDoc.LoadFile(i_insertPath.c_str());

	//Get source file root Element
	tinyxml2::XMLElement* pRootElement_s = sourceDoc.RootElement();
	// Get source file 'Datas' Child
	tinyxml2::XMLElement* pDatas_s = pRootElement_s->FirstChildElement("Datas");

	//Get insert file root Element
	tinyxml2::XMLElement* pRootElement_i = insertDoc.RootElement();
	// Get insert file 'Datas' Child
	tinyxml2::XMLElement* pDatas_i = pRootElement_i->FirstChildElement("Datas");

	// Create new Element
	tinyxml2::XMLNode* pRoot_s;
	tinyxml2::XMLElement* pElement_s;

	tinyxml2::XMLElement* pRoot_i = pDatas_i->FirstChildElement("Data");
	//tinyxml2::XMLElement* pElement_i;

	while (pRoot_i != NULL)
	{
		pRoot_s = sourceDoc.NewElement("Data");
		pDatas_s->InsertEndChild(pRoot_s);

		// Name
		pElement_s = sourceDoc.NewElement("Name");
		tinyxml2::XMLElement* pDataInfo = pRoot_i->FirstChildElement("Name");
		pElement_s->SetText(pDataInfo->GetText());
		pRoot_s->InsertEndChild(pElement_s);

		// Chinese
		pElement_s = sourceDoc.NewElement("Chinese");
		pElement_s->SetText(pRoot_i->FirstChildElement("Chinese")->GetText());
		pRoot_s->InsertEndChild(pElement_s);

		// English
		pElement_s = sourceDoc.NewElement("English");
		pElement_s->SetText(pRoot_i->FirstChildElement("English")->GetText());
		pRoot_s->InsertEndChild(pElement_s);

		// Math
		pElement_s = sourceDoc.NewElement("Math");
		pElement_s->SetText(pRoot_i->FirstChildElement("Math")->GetText());
		pRoot_s->InsertEndChild(pElement_s);


		pRoot_i = pRoot_i->NextSiblingElement("Data");
	}

	//Save the changes into the XML file
	sourceDoc.SaveFile(i_sourcePath.c_str());
}

void XMLHelper::InsertXMLFromGradeTable(std::string i_sourcePath, GMHelper::GradeTable* i_gradeTabel)
{
	tinyxml2::XMLDocument sourceDoc;
	sourceDoc.LoadFile(i_sourcePath.c_str());

	//Get source file root Element
	tinyxml2::XMLElement* pRootElement_s = sourceDoc.RootElement();
	// Get source file 'Datas' Child
	tinyxml2::XMLElement* pDatas_s = pRootElement_s->FirstChildElement("Datas");

	// Create new Element
	tinyxml2::XMLNode* pRoot_s;
	tinyxml2::XMLElement* pElement_s;

	for (size_t index = 0; index < i_gradeTabel->GetTable().size(); index++)
	{
		pRoot_s = sourceDoc.NewElement("Data");
		pDatas_s->InsertEndChild(pRoot_s);

		// Name
		pElement_s = sourceDoc.NewElement("Name");
		pElement_s->SetText(i_gradeTabel->GetTable()[index].name.c_str());
		pRoot_s->InsertEndChild(pElement_s);

		// Chinese
		pElement_s = sourceDoc.NewElement("Chinese");
		pElement_s->SetText(std::to_string(i_gradeTabel->GetTable()[index].Chinese).c_str());
		pRoot_s->InsertEndChild(pElement_s);

		// English
		pElement_s = sourceDoc.NewElement("English");
		pElement_s->SetText(std::to_string(i_gradeTabel->GetTable()[index].English).c_str());
		pRoot_s->InsertEndChild(pElement_s);

		// Math
		pElement_s = sourceDoc.NewElement("Math");
		pElement_s->SetText(std::to_string(i_gradeTabel->GetTable()[index].Math).c_str());
		pRoot_s->InsertEndChild(pElement_s);

		std::cout << "insert: <" << i_gradeTabel->GetTable()[index].name << "," << i_gradeTabel->GetTable()[index].Chinese << "," << i_gradeTabel->GetTable()[index].English << "," << i_gradeTabel->GetTable()[index].Math << "> to " << i_sourcePath << std::endl;
	}

	//Save the changes into the XML file
	sourceDoc.SaveFile(i_sourcePath.c_str());
}