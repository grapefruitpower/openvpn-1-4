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

class CreateConfig {
	private:
		size_t copyPosBegin;
		size_t copyPosEnd;
		string configContent;
	public:
		string sourceFile;
		string destFile;
		
		void setData(string source, string dest) {
			sourceFile = source;
			destFile = dest;
		}
		string getSource() {
			return sourceFile;
		}
		/* create the config File and return FALSE when its not */
		bool createFile () {
			ofstream config (destFile.append("client.cfg").c_str());
			config << "#Config by strcon\n";
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
		*	get end position
		*	then copy Content
		*/
		bool getEndPosAndCopy () {
			ifstream sFile(sourceFile.c_str());
			string endSym((istreambuf_iterator<char>(sFile)), istreambuf_iterator<char>());
		
			// it could be <ca> or <key>
			size_t foundEnd = endSym.find("<");
			
			copyPosEnd = foundEnd-1;
			
			if (copyPosEnd > 0) {
				ofstream config(destFile.c_str());
 	                        string out = endSym.substr(copyPosBegin,copyPosEnd);
				sFile.close();
        	                config << out;
				config.close();
				
				return true;
			} else {
				sFile.close();
				return false;
			}
		}
};
