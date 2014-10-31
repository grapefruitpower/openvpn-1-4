/*
	strcon v0.1.0b
*	GPLv2
*	String Contains - by Lars Feldeisen
*	shortname: strcon
*/

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <errno.h>
#include "CreateConfig.h"
#include "Comp.h"

using namespace std;
	
void action(string source, string strA, string strB, string dest) {
	ifstream file(source.c_str());
        string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	
	/*
	* get string length for content
	*/
	int strLength = str.length();
	
	
        /* find strA and strB */
       	int aLength = str.find(strA);
        int bLength = str.find(strB);
	
	// start point
	aLength = aLength + strA.length();
	bLength = bLength - aLength;

	string fileName;
	if (strA == "<ca>") {
		fileName = "ca.crt";
	} else if (strA == "<cert>") {
		fileName = "client.crt";
	} else {
		fileName = "client.key";
	}

        ofstream ofs (dest.append(fileName).c_str());
        string output = str.substr(aLength,bLength);
        ofs << output;
        ofs.close();
}

bool pushFiles(string source, string dest, string cab, string cae, string caf) {
	Components cp;
	cp.setData(source, dest, cab, cae, caf);
	cp.getBeginPos();
	cp.getEndPos();
	cp.copyToFile();

	return true;
}

int main(int argc, char *argv[]) {
	int p = argc;
	if (p == 4) {
		string op	= argv[1];
		string source 	= argv[2];
		string dest	= argv[3];
		if (op == "ghost") {
			/*CreateConfig cc;
			cc.setData(source, dest);
			cc.createFile();
			cc.getEndPosAndCopy();
			*/
			//pushFiles(source, dest, "<ca>", "<cert>", "ca.crt");
		}	
	} else if (p == 3) {
		string ca 	= "<ca>";
		string eca 	= "</ca>";
		string client 	= "<cert>";
		string eclient 	= "</cert>";
		string key	= "<key>";
		string ekey 	= "</key>";

		string src 	= argv[1];
		string dest 	= argv[2];
	
		// check if destination has / <- as last character
	/*	if (dest.at(dest.length()) == "/")  {
			cout << "/ is set" << endl;
		} else {
			dest.append("/");
			cout << "append on dest /" << endl;
		}*/
		
		action (src, ca, eca, dest);
		action (src, client,eclient, dest);
		action (src, key,ekey, dest);
		
		CreateConfig cc;
		cc.setData(src, dest);
		cc.createFile();
		cc.getEndPosAndCopy();
	}
return 0;

}
