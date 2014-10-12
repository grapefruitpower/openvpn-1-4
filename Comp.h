/*
*	CreatConfig for strcon 
*	created by Lars Feldeisen
*	GPLv2 - Please read!
*
*/


#include <string.h>
#include <iostream>
#define CREATECONFIG_H

using namespace std;

class Components {
	private:
		size_t copyPosBegin;
		size_t copyPosEnd;
		string configContent;
	public:
		string sourceFile;
		string destFile;
		string symb1;
		string symb2;
		string symb3;

		void setData(string source, string dest, string sym1, string sym2, string sym3) {
			sourceFile = source;
			destFile = dest;
			symb1 = sym1;
			symb2 = sym2;
			symb3 = sym3;

		}
		void setPos(size_t copyPos) {
			copyPosBegin = copyPos;
		}
		string getSymb2() {
			return symb2;
		}
		size_t getCopyPosEnd() {
			return copyPosEnd;
		}
		
		/* create the config File and return FALSE when its not */
		bool createFile () {
			ofstream config (destFile.append(symb3).c_str());
			config.close();
			
			/* check if file exist */
			ifstream rConfig(destFile.c_str());
			if(rConfig.good()) {
				rConfig.close();
				return true;
			} else {
				rConfig.close();
				return false;
			}
		}
		/*
		*	get begin position
		*/	
		void getBeginPos() {
			ifstream sFile(sourceFile.c_str());
			string begSym((istreambuf_iterator<char>(sFile)), istreambuf_iterator<char>());
			
			size_t foundBegin = begSym.find(symb1);
			// + length of symbol. We need between 2 symbols!
			copyPosBegin = foundBegin+sizeof(symb1);	
		}
		
		/*
		*	get end position
		*/
		void getEndPos() {
			ifstream sFile(sourceFile.c_str());
			string fileStr((istreambuf_iterator<char>(sFile)), istreambuf_iterator<char>());
			
			size_t foundEnd = fileStr.find(symb2);
			//-1 pos of symbol	
			copyPosEnd = foundEnd;
		}
		
		/*
		*	get end position
		*	then copy Content
		*/
		bool copyToFile() {
			if (copyPosEnd > 0) {
				ifstream sFile(sourceFile.c_str());
				string fileStr((istreambuf_iterator<char>(sFile)), istreambuf_iterator<char>());
				ofstream file(destFile.append(symb3).c_str());
 	                        string out = fileStr.substr(copyPosBegin,copyPosEnd);
				sFile.close();
        	                file << out;
				file.close();
				
				return true;
			} else {
				return false;
			}
		}
};
