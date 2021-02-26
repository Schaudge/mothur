/*
 *  setlogfilecommand.cpp
 *  Mothur
 *
 *  Created by westcott on 4/27/10.
 *  Copyright 2010 Schloss Lab. All rights reserved.
 *
 */

#include "setlogfilecommand.h"


//**********************************************************************************************************************
vector<string> SetLogFileCommand::setParameters(){	
	try {
		CommandParameter pappend("append", "Boolean", "", "F", "", "", "","",false,false); parameters.push_back(pappend);
		CommandParameter pname("name", "String", "", "", "", "", "","",false,true,true); parameters.push_back(pname);
		CommandParameter pseed("seed", "Number", "", "0", "", "", "","",false,false); parameters.push_back(pseed);
        CommandParameter pinputdir("inputdir", "String", "", "", "", "", "","",false,false); parameters.push_back(pinputdir);
		CommandParameter poutputdir("outputdir", "String", "", "", "", "", "","",false,false); parameters.push_back(poutputdir);
        
        abort = false; calledHelp = false;
		
		vector<string> myArray;
		for (int i = 0; i < parameters.size(); i++) {	myArray.push_back(parameters[i].name);		}
		return myArray;
	}
	catch(exception& e) {
		m->errorOut(e, "SetLogFileCommand", "setParameters");
		exit(1);
	}
}
//**********************************************************************************************************************
string SetLogFileCommand::getHelpString(){	
	try {
		string helpString = "";
		helpString += "The set.logfile command can be used to provide a specific name for your logfile and/or to append the log generated by mothur to an existing file.\n";
		helpString += "The set.logfile command parameters are name and append, name is required. Append is set to false by default.\n";
		helpString += "The set.logfile command should be in the following format: set.logfile(name=yourLogFileName, append=T).\n";
		helpString += "Example set.logfile(name=/Users/lab/desktop/output.txt, append=T).\n";
		return helpString;
	}
	catch(exception& e) {
		m->errorOut(e, "SetLogFileCommand", "getHelpString");
		exit(1);
	}
}
//**********************************************************************************************************************

SetLogFileCommand::SetLogFileCommand(string option)  {
	try {

		if(option == "help") { help(); abort = true; calledHelp = true; }
		else if(option == "citation") { citation(); abort = true; calledHelp = true;}
        else if(option == "category") {  abort = true; calledHelp = true;  }
		
		else {
			OptionParser parser(option, setParameters());
			map<string, string> parameters = parser.getParameters();
			
			ValidParameters validParameter;
			name = validParameter.validPath(parameters, "name");
			if (name == "not found") {  m->mothurOut("name is a required parameter for the set.logfile command."); abort = true; } 
			
			string temp = validParameter.valid(parameters, "append");		if (temp == "not found") {  temp = "F";  }
			append = util.isTrue(temp);
            
            if (outputdir == ""){ outputdir = util.hasPath(name); }
		}
	}
	catch(exception& e) {
		m->errorOut(e, "SetLogFileCommand", "SetLogFileCommand");
		exit(1);
	}
}

//**********************************************************************************************************************

int SetLogFileCommand::execute(){
	try {
		
		if (abort) { if (calledHelp) { return 0; }  return 2;	}
        
        string directory = util.hasPath(name);
        if (directory == "") {
            m->setLogFileName(outputdir+name, append);
        }else if (util.dirCheckWritable(directory)) {
            m->setLogFileName(name, append);
        }
		
        m->mothurOut("\nSetting logfile name to " + m->getLogFileName() + "\n\n");
        
		return 0;
	}
	catch(exception& e) {
		m->errorOut(e, "SetLogFileCommand", "execute");
		exit(1);
	}
}
//**********************************************************************************************************************/
