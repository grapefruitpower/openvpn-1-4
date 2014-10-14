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

        /* find strA and strB */
        size_t foundA = str.find(strA);
        size_t foundB = str.find(strB);

        int lastPosFromA = foundA + sizeof(strA);

        // length du cut
        int cutLength = foundB - lastPosFromA;
		
        ofstream ofs (dest.c_str());
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
			pushFiles(source, dest, "<ca>", "<cert>", "ca.crt");
			
		}	
	} else if(argc != 5) {
		errno=EINVAL;
		perror("strcon source stringA stringB destination_file\n special characters with \\ ex. \\<\n");
		exit(1);
	} else {
		string source = argv[1]; //source filepath
         	string strA = argv[2];
         	string strB = argv[3];
         	string dest = argv[4];  //destination file
	
		action(source, strA, strB, dest);

	}
return 0;

}
