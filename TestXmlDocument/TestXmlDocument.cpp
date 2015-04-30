////////////////////////////////////////////////////////////////////////////////
// TestFileCatalogue.cpp - Test operations on Xml Document                    //
// ver 1.0                                                                    //
// Language:    Visual C++, Visual Studio 2013                                                                            //
// Application: CSE687 2015 Project 1 - File Catalogue                        //  
// Platform:    Win7, Visual Studio 2013                                      //
// Author:      Wenting Wang, wwang34@syr.edu                                 //                                            
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <functional>
#include "..\XmlDocument\XmlDocument.h"
#include "..\DisplayHelper\DisplayHelper.h"

using namespace DisplayHelperNS;
using namespace XmlProcessing;
using namespace std;

class Test{
public:
	void TestReadxmlfile(const string& filename){
		title("\n Testing reading a xml file: "+ filename);
		doc1 = XmlDocument(filename, XmlDocument::sourceType::filename);
		DisplayHelper::displayResultPrompt();
		std::cout << doc1.writeToXmlstring();
	}
	void TestReadxmlstring(){
		title("\n Testing reading a xml string");
		string teststring = "<?xml version=\"1.0\" ?><!-- top level comment --><?xml-stylesheet href='style.css' type='text\\css'?><Dir><path pattrib1=\"pattribv1\" pattrib2=\"pattribv2\"><path1><path11>/TestFile/Dir1</path11></path1></path><File fattrib=\"fattribv\"><name><name1>text1.txt</name1></name><date>02/11/2012</date></File></Dir>";
		doc2 = XmlDocument(teststring, XmlDocument::sourceType::string);
		DisplayHelper::displayResultPrompt();
		std::cout << doc2.writeToXmlstring() << "\n";
	}
	void TestElement(){
		tag = "book";
		title("\n Testing element(\"" + tag + "\")");
		doc1.element(tag);
		DisplayHelper::displayResultPrompt();
		DisplayHelper::displayElementQueryResult(doc1.select());
	}
	void TestElements(){
		tag = "book";
		title("\n Testing elements(\"" + tag + "\")");
		doc1.elements(tag);
		DisplayHelper::displayResultPrompt();
		DisplayHelper::displayElementQueryResult(doc1.select());
	}
	void TestElementWithID(){
		idname = "id";
		idvalue = "bk103";
		title("\n Testing elementwID(\"" + idname + "\", \"" + idvalue + "\") ");
		doc1.elementwID(idname, idvalue);
		DisplayHelper::displayResultPrompt();
		DisplayHelper::displayElementQueryResult(doc1.select());
		idvalue = "bk100";
		title("\n Testing elementwID(\"" + idname + "\", \"" + idvalue + "\") ");
		doc1.elementwID(idname, idvalue);
		DisplayHelper::displayResultPrompt();
		DisplayHelper::displayElementQueryResult(doc1.select());
	}
	void TestAttributes(){
		tag = "path";
		title("\n Testing element(" + tag + ").attributes()");
		std::vector<std::pair<std::string, std::string>> attribs = doc2.element(tag).attributes();
		DisplayHelper::displayResultPrompt();
		DisplayHelper::displayAttributesQueryResult(attribs);
		attribname = "nonexsitattri";
		title("\n Testing element(" + tag + ").attributes(" + attribname + ")");
		attribs = doc2.element(tag).attributes(attribname);
		doc2.select(); //clear doc2's query result;
		DisplayHelper::displayResultPrompt();
		DisplayHelper::displayAttributesQueryResult(attribs);
		tag = "File";
		attribname = "fattrib";
		title("\n Testing element(" + tag + ").attributes(" + attribname + ")");
		attribs = doc2.element(tag).attributes(attribname);
		doc2.select(); //clear doc2's query result;
		DisplayHelper::displayResultPrompt();
		DisplayHelper::displayAttributesQueryResult(attribs);
	}
	void Testdescendents(){
		tag = "author";
		title("\n Testing descendents(" + tag + ")");
		doc1.descendents(tag);
		DisplayHelper::displayResultPrompt();
		DisplayHelper::displayElementQueryResult(doc1.select());
		tag = "File";
		title("\n Testing element(" + tag + ").descendents() ");
		doc2.element(tag).descendents();
		DisplayHelper::displayResultPrompt();
		DisplayHelper::displayElementQueryResult(doc2.select());
	}
	void TestChildren(){
		title("\n Testing children() ");
		doc2.children();
		DisplayHelper::displayResultPrompt();
		DisplayHelper::displayElementQueryResult(doc2.select());
		tag = "catalog";
		title("\n Testing element(" + tag + ").children() ");
		doc1.element(tag).children();
		DisplayHelper::displayResultPrompt();
		DisplayHelper::displayElementQueryResult(doc1.select());
		tag = "book";
		childTag = "price";
		title("\n Testing element(" + tag + ").children(" + childTag + ")");
		doc1.element(tag).children(childTag);
		DisplayHelper::displayResultPrompt();
		DisplayHelper::displayElementQueryResult(doc1.select());
	}
	void TestaddChild(){
		tag = "country";
		idname = "id";
		idvalue = "bk101";
		title("\n Testing elementwID(" + idname + ", " + idvalue + ").addChild(makeTaggedElement(" + tag + "))");
		if (doc1.elementwID(idname, idvalue).addChild(makeTaggedElement(tag))){
			std::cout << "\n added the child " << tag << " to the element\n";
		};
		text = "USA"; 
		doc1.select(); //clear doc1's query result;
		title("\n Testing elementwID(" + idname + ", " + idvalue + ").element(" + tag + ").addChild(makeTextElement(" + text + ")) ");
		if (doc1.elementwID(idname, idvalue).element(tag).addChild(makeTextElement(text))){
			std::cout << "\n added the grand child " << text << " to the element\n";
		};
		DisplayHelper::displayResultPrompt();
		std::cout << doc1.writeToXmlstring() << "\n";
	}
	void TestaddAttrib(){
		attribname = "lang";
		attribvalue = "Eng";
		idname = "id";
		idvalue = "bk101";
		tag = "country";
		doc1.select(); //clear doc1's query result;
		title("\n Testing element(" + tag + ").addAttrib(" + attribname + ", " + attribvalue + ")");
		if (doc1.elementwID(idname, idvalue).element(tag).addAttrib(attribname, attribvalue)){
			std::cout << "\n added the attribute " << attribname << "\n";
		};
		DisplayHelper::displayResultPrompt();
		std::cout << doc1.writeToXmlstring() << "\n";
	}
	void TestremoveChild(){
		std::vector<XmlDocument::sPtr> v;
		idname = "id";
		idvalue = "bk103";
		doc1.select(); //clear doc1's query result;
		v = doc1.elementwID(idname, idvalue).select();
		if (v.size() > 0){
			temEl = v[0];
		};
		tag = "catalog";
		title("\n Testing element(" + tag + ").removeChild(smartpointer)");
		if (doc1.element(tag).removeChild(temEl)){
			std::cout << "\n removed the child with id value " + idvalue + "\n";
		}
		idname = "id";
		idvalue = "bk101";
		childTag = "publish_date";
		title("\n Testing elementwID(" + idname + ", " + idvalue + ").removeChild(" + childTag + ")");
		doc1.select(); //clear doc1's query result;
		if (doc1.elementwID(idname, idvalue).removeChild(childTag)){
			std::cout << "\n removed the child with the tag " + childTag + " of the element with id " + idvalue + "\n";
		};
		DisplayHelper::displayResultPrompt();
		std::cout << doc1.writeToXmlstring() << "\n";
	}
	void TestremoveAttrib(){
		attribname = "lang";
		idname = "id";
		idvalue = "bk101";
		tag = "country";
		title("\n Testing element(" + tag + ").removeAttrib(" + attribname + ")");
		if (doc1.elementwID(idname, idvalue).element(tag).removeAttrib(attribname)){
			std::cout << "\n removed the attribute with name " + attribname + " of the element with tag " + tag + "\n";
		};
		DisplayHelper::displayResultPrompt();
		std::cout << doc1.writeToXmlstring();
		std::cout << "\n";
	}
	void TestcreateRoot(){
		tag = "RootElement";
		title("\n Testing createRoot(" + tag + ")");
		if (doc4.createRoot(makeTaggedElement(tag))){
			std::cout << "\n Root element was created.";
		};
		title("\n Testing addChild() on created root");
		std::vector<XmlDocument::sPtr> v = doc4.elements().select();
		if (v.size() > 2) temEl = v[2];
		childTag = "FirstChild";
		if (temEl->addChild(makeTaggedElement(childTag))){
			std::cout << "\n Child was added to the root element. \n";
		};
		DisplayHelper::displayResultPrompt();
		std::cout << doc4.writeToXmlstring() << "\n";
	}
	void TestmoveConstruction(){
		title("\n Testing move constrution");
		XmlDocument doc(std::move(doc2));
		std::cout << "\n  The constructed doc is as following: \n";
		std::cout << doc.writeToXmlstring();
		std::cout << "\n\n  The moved doc is as following: \n";
		std::cout << doc2.writeToXmlstring();
		std::cout << "\n";
	}
	void TestmoveAssignment(){
		title("\n Testing move assignment operation");
		doc3 = std::move(doc4);
		std::cout << "\n  The assigned doc is as following: \n";
		std::cout << doc3.writeToXmlstring();
		std::cout << "\n\n  The moved doc is as following: \n";
		std::cout << doc4.writeToXmlstring() << "\n";
	}
	void TestWritetofile(){
		writeFilename = "NewFile.xml";
		title("\n Testing writing to a new xml file: " + writeFilename);
		if (doc1.writeToFile(writeFilename)){
			std::cout << "\n The file was created. \n";
		};
	}
private:
	XmlDocument doc1;
	XmlDocument doc2;
	XmlDocument doc3;
	XmlDocument doc4;
	XmlDocument::sPtr temEl;
	std::string tag;
	std::string idname;
	std::string idvalue;
	std::string attribname;
	std::string attribvalue;
	std::string childTag;
	std::string text;
	std::string writeFilename;
};
int main(int argc, char* argv[])
{
	Test t;
	DisplayHelper::section("Demonstrating requirement #3 #10");
	if(argc>1) t.TestReadxmlfile(argv[1]);
	t.TestReadxmlstring();
	DisplayHelper::section("Demonstrating requirement #6");
	t.TestElement();
	t.TestElements();
	DisplayHelper::section("Demonstrating requirement #5");
	t.TestElementWithID();
	DisplayHelper::section("Demonstrating requirement #8 (return attributes)");
	t.TestAttributes();
	t.Testdescendents();
	DisplayHelper::section("Demonstrating requirement #8 (return children)");
	t.TestChildren();
	DisplayHelper::section("Demonstrating requirement #6 (add, remove child)");
	t.TestaddChild();
	t.TestremoveChild();
	DisplayHelper::section("Demonstrating requirement #9");
	t.TestaddAttrib();
	t.TestremoveAttrib();
	DisplayHelper::section("Demonstrating requirement #6 (create root element)");
	t.TestcreateRoot();
	DisplayHelper::section("Demonstrating requirement #4");
	t.TestmoveConstruction();
	t.TestmoveAssignment();
	DisplayHelper::section("Demonstrating requirement #10");
	t.TestWritetofile();

	cout << "\n\n";
}