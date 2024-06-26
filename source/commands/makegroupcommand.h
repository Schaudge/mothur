#ifndef MAKEGROUPCOMMAND_H
#define MAKEGROUPCOMMAND_H

/*
 *  makegroupcommand.h
 *  Mothur
 *
 *  Created by westcott on 5/7/10.
 *  Copyright 2010 Schloss Lab. All rights reserved.
 *
 */

#include "command.hpp"

class MakeGroupCommand : public Command {
	
public:
	MakeGroupCommand(string);
	~MakeGroupCommand(){}
	
	vector<string> setParameters();
	string getCommandName()			{ return "make.group";	}
	string getCommandCategory()		{ return "General";		}
	
	string getHelpString();	
    string getOutputPattern(string);	
	string getCitation() { return "http://www.mothur.org/wiki/Make.group"; }
	string getDescription()		{ return "creates a group file"; }

	int execute(); 
	void help() { m->mothurOut(getHelpString()); }	
	
private:
		
	string fastaFileName, groups, output, format, fileFile;
	vector<string> fastaFileNames;
	vector<string> groupsNames, outputNames;
	
	bool abort;
    
    void processFastaFiles(map<string, string>&, map<string, long long>&);
    void processFileFile(map<string, string>&, map<string, long long>&);
};

#endif

