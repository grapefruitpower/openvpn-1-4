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
	cout << strA << endl;
	cout << strB << endl;
	cout << dest << endl;
	ifstream file(source.c_str());
        string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        /* find strA and strB */
        size_t foundA = str.find(strA);
        size_t foundB = str.find(strB);

        int lastPosFromA = foundA + sizeof(strA);

        // length du cut
        int cutLength = foundB - lastPosFromA;
	
	string fileName;
	if (strA == "<ca>") {
		fileName = "ca.crt";
	} else if (strA == "<client>") {
		fileName = "client.crt";
	} else {
		fileName = "client.key";
	}

        ofstream ofs (dest.append(fileName).c_str());
        string output = str.substr(foundA+sizeof(strA),cutLength);
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
		string client 	= "<client>";
		string eclient 	= "</client>";
		string key	= "<key>";
		string ekey 	= "</key>";

		string src 	= argv[1];
		string dest 	= argv[2];
		action (src, ca, eca, dest);
		action (src, client,eclient, dest);
		action (src, key,ekey, dest);
	}
return 0;

}
