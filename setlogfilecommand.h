#ifndef SETLOGFILECOMMAND_H
#define SETLOGFILECOMMAND_H

/*
 *  setlogfilecommand.h
 *  Mothur
 *
 *  Created by westcott on 4/27/10.
 *  Copyright 2010 Schloss Lab. All rights reserved.
 *
 */

#include "command.hpp"
#include "commandfactory.hpp"

/**********************************************************/

class SetLogFileCommand : public Command {
	
public:
	SetLogFileCommand(string);
	~SetLogFileCommand();
	int execute();
	void help();
	
private:
	CommandFactory* commandFactory;
	string name;
	bool abort, append;
		
};

/**********************************************************/
 
#endif

