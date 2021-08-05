/*
 *  deconvolute.cpp
 *  Mothur
 *
 *  Created by Sarah Westcott on 1/21/09.
 *  Copyright 2009 Schloss Lab UMASS Amherst. All rights reserved.
 *
 */

#include "deconvolutecommand.h"
#include "sequence.hpp"

//**********************************************************************************************************************
vector<string> DeconvoluteCommand::setParameters(){	
	try {
		CommandParameter pfasta("fasta", "InputTypes", "", "", "none", "none", "none","fasta-name",false,true,true); parameters.push_back(pfasta);
		CommandParameter pname("name", "InputTypes", "", "", "namecount", "none", "none","name",false,false,true); parameters.push_back(pname);
        CommandParameter pcount("count", "InputTypes", "", "", "namecount", "none", "none","count",false,false,true); parameters.push_back(pcount);
        CommandParameter pformat("format", "Multiple", "count-name", "name", "", "", "","",false,false, true); parameters.push_back(pformat);
        CommandParameter poutput("output", "Multiple", "count-name", "name", "", "", "","",false,false, true); parameters.push_back(poutput);
        CommandParameter pseed("seed", "Number", "", "0", "", "", "","",false,false); parameters.push_back(pseed);
        CommandParameter pinputdir("inputdir", "String", "", "", "", "", "","",false,false); parameters.push_back(pinputdir);
		CommandParameter poutputdir("outputdir", "String", "", "", "", "", "","",false,false); parameters.push_back(poutputdir);
        
        abort = false; calledHelp = false;
       
        vector<string> tempOutNames;
        outputTypes["fasta"] = tempOutNames;
        outputTypes["name"] = tempOutNames;
        outputTypes["count"] = tempOutNames;
		
		vector<string> myArray;
		for (int i = 0; i < parameters.size(); i++) {	myArray.push_back(parameters[i].name);		}
		return myArray;
	}
	catch(exception& e) {
		m->errorOut(e, "DeconvoluteCommand", "setParameters");
		exit(1);
	}
}
//**********************************************************************************************************************
string DeconvoluteCommand::getHelpString(){	
	try {
		string helpString = "";
		helpString += "The unique.seqs command reads a fastafile and creates a name or count file.\n";
		helpString += "The unique.seqs command parameters are fasta, name, count and format.  fasta is required, unless there is a valid current fasta file.\n";
        helpString += "The name parameter is used to provide an existing name file associated with the fasta file. \n";
        helpString += "The count parameter is used to provide an existing count file associated with the fasta file. \n";
        helpString += "The format parameter is used to indicate what type of file you want outputted.  Choices are name and count, default=name unless count file used then default=count.\n";
		helpString += "The unique.seqs command should be in the following format: \n";
		helpString += "unique.seqs(fasta=yourFastaFile) \n";	
		return helpString;
	}
	catch(exception& e) {
		m->errorOut(e, "DeconvoluteCommand", "getHelpString");
		exit(1);
	}
}
//**********************************************************************************************************************
string DeconvoluteCommand::getOutputPattern(string type) {
    try {
        string pattern = "";
        
        if (type == "fasta") {  pattern = "[filename],unique,[extension]"; } 
        else if (type == "name") {  pattern = "[filename],names-[filename],[tag],names"; } 
        else if (type == "count") {  pattern = "[filename],count_table-[filename],[tag],count_table"; }
        else { m->mothurOut("[ERROR]: No definition for type " + type + " output pattern.\n"); m->setControl_pressed(true);  }
        
        return pattern;
    }
    catch(exception& e) {
        m->errorOut(e, "DeconvoluteCommand", "getOutputPattern");
        exit(1);
    }
}
/**************************************************************************************/
DeconvoluteCommand::DeconvoluteCommand(string option) : Command()  {	
	try {
		//allow user to run help
		if(option == "help") { help(); abort = true; calledHelp = true; }
		else if(option == "citation") { citation(); abort = true; calledHelp = true;}
        else if(option == "category") {  abort = true; calledHelp = true;  }
		
		else {
			OptionParser parser(option, setParameters());
			map<string,string> parameters = parser.getParameters();
			
			ValidParameters validParameter;
			fastafile = validParameter.validFile(parameters, "fasta");
			if (fastafile == "not open") { abort = true; }
			else if (fastafile == "not found") {
				fastafile = current->getFastaFile();
				if (fastafile != "") { m->mothurOut("Using " + fastafile + " as input file for the fasta parameter.\n");  }
				else { 	m->mothurOut("You have no current fastafile and the fasta parameter is required.\n");  abort = true; }
			}else { current->setFastaFile(fastafile); }
			
			 
            if (outputdir == ""){
				outputdir += util.hasPath(fastafile); 
			}
			
			namefile = validParameter.validFile(parameters, "name");
			if (namefile == "not open") { namefile = ""; abort = true; }
			else if (namefile == "not found"){	namefile = "";	}
			else { current->setNameFile(namefile); }
            
            countfile = validParameter.validFile(parameters, "count");
			if (countfile == "not open") { abort = true; countfile = ""; }	
			else if (countfile == "not found") { countfile = ""; }
			else { current->setCountFile(countfile); }
			
            if ((countfile != "") && (namefile != "")) { m->mothurOut("When executing a unique.seqs command you must enter ONLY ONE of the following: count or name.\n");  abort = true; }
			
            //allow format parameter to have two names - format or output
            format = validParameter.valid(parameters, "format");
            if(format == "not found"){
                format = validParameter.valid(parameters, "output");
                if(format == "not found"){
                    if (countfile != "") { format = "count";    }
                    else { format = "name";                     }
                }
            }
            
            if ((format != "name") && (format != "count")) {
                m->mothurOut(format + " is not a valid format option. Options are count or name.");
                if (countfile == "") { m->mothurOut("I will use name.\n"); format = "name"; }
                else {  m->mothurOut("I will use count.\n"); format = "count"; }
            }
            
			if (countfile == "") {
                if (namefile == "") {
                    vector<string> files; files.push_back(fastafile);
                    if (!current->getMothurCalling())  {  parser.getNameFile(files);  }
                }
            }
			
		}

	}
	catch(exception& e) {
		m->errorOut(e, "DeconvoluteCommand", "DeconvoluteCommand");
		exit(1);
	}
}
/**************************************************************************************/
int DeconvoluteCommand::execute() {	
	try {
		
		if (abort) { if (calledHelp) { return 0; }  return 2;	}
        
		//prepare filenames and open files
        map<string, string> variables; 
        variables["[filename]"] = outputdir + util.getRootName(util.getSimpleName(fastafile));
        string outNameFile = getOutputFileName("name", variables);
        string outCountFile = getOutputFileName("count", variables);
        variables["[extension]"] = util.getExtension(fastafile);
		string outFastaFile = getOutputFileName("fasta", variables);
		
		map<string, string> nameMap;
		map<string, string>::iterator itNames;
		if (namefile != "")  {
            util.readNames(namefile, nameMap);
            if (namefile == outNameFile){
                //prepare filenames and open files
                map<string, string> mvariables;
                mvariables["[filename]"] = outputdir + util.getRootName(util.getSimpleName(fastafile));
                mvariables["[tag]"] = "unique";
                outNameFile = getOutputFileName("name", mvariables);
            }
        }
        CountTable ct;
        if (countfile != "")  {  
            ct.readTable(countfile, true, false);
            if (countfile == outCountFile){
                //prepare filenames and open files
                map<string, string> mvariables;
                mvariables["[filename]"] = outputdir + util.getRootName(util.getSimpleName(fastafile));
                mvariables["[tag]"] = "unique";
                outCountFile = getOutputFileName("count", mvariables);   }
        }
		
		if (m->getControl_pressed()) { return 0; }
		
		ifstream in; 
		util.openInputFile(fastafile, in);
		
		ofstream outFasta;
		util.openOutputFile(outFastaFile, outFasta);
		
		map<string, string> sequenceStrings; //sequenceString -> list of names.  "atgc...." -> seq1,seq2,seq3.
		map<string, string>::iterator itStrings;
		set<string> nameInFastaFile; //for sanity checking
		set<string>::iterator itname;
		vector<string> nameFileOrder;
        CountTable newCt;
		int count = 0;
		while (!in.eof()) {
			
			if (m->getControl_pressed()) { in.close(); outFasta.close(); util.mothurRemove(outFastaFile); return 0; }
			
			Sequence seq(in);
			
			if (seq.getName() != "") {
				
				//sanity checks
				itname = nameInFastaFile.find(seq.getName());
				if (itname == nameInFastaFile.end()) { nameInFastaFile.insert(seq.getName());  }
				else { m->mothurOut("[ERROR]: You already have a sequence named " + seq.getName() + " in your fasta file, sequence names must be unique, please correct.\n");  }

				itStrings = sequenceStrings.find(seq.getAligned());
				
				if (itStrings == sequenceStrings.end()) { //this is a new unique sequence
					//output to unique fasta file
					seq.printSequence(outFasta);
					
					if (namefile != "") {
						itNames = nameMap.find(seq.getName());
						
						if (itNames == nameMap.end()) { //namefile and fastafile do not match
							m->mothurOut("[ERROR]: " + seq.getName() + " is in your fasta file, and not in your namefile, please correct.\n"); 
						}else {
                            if (format == "name") { sequenceStrings[seq.getAligned()] = itNames->second;  nameFileOrder.push_back(seq.getAligned());
                            }else {  newCt.push_back(seq.getName(), util.getNumNames(itNames->second)); sequenceStrings[seq.getAligned()] = seq.getName();	nameFileOrder.push_back(seq.getAligned()); }
						}
					}else if (countfile != "") {
                        if (format == "name") {
                            int numSeqs = ct.getNumSeqs(seq.getName());
                            string expandedName = seq.getName()+"_0";
                            for (int i = 1; i < numSeqs; i++) {  expandedName += "," + seq.getName() + "_" + toString(i);  }
                            sequenceStrings[seq.getAligned()] = expandedName;  nameFileOrder.push_back(seq.getAligned());
                        }else {
                            ct.getNumSeqs(seq.getName()); //checks to make sure seq is in table
                            sequenceStrings[seq.getAligned()] = seq.getName();	nameFileOrder.push_back(seq.getAligned());
                        }
                    }else {
                        if (format == "name") { sequenceStrings[seq.getAligned()] = seq.getName();	nameFileOrder.push_back(seq.getAligned()); }
                        else {  newCt.push_back(seq.getName()); sequenceStrings[seq.getAligned()] = seq.getName();	nameFileOrder.push_back(seq.getAligned()); }
                    }
				}else { //this is a dup
					if (namefile != "") {
						itNames = nameMap.find(seq.getName());
						
						if (itNames == nameMap.end()) { //namefile and fastafile do not match
							m->mothurOut("[ERROR]: " + seq.getName() + " is in your fasta file, and not in your namefile, please correct.\n"); 
						}else {
                            if (format == "name") { sequenceStrings[seq.getAligned()] += "," + itNames->second;  }
                            else {  int currentReps = newCt.getNumSeqs(itStrings->second);  newCt.setNumSeqs(itStrings->second, currentReps+(util.getNumNames(itNames->second)));  }
						}
                    }else if (countfile != "") {
                        if (format == "name") {
                            int numSeqs = ct.getNumSeqs(seq.getName());
                            string expandedName = seq.getName()+"_0";
                            for (int i = 1; i < numSeqs; i++) {  expandedName += "," + seq.getName() + "_" + toString(i);  }
                            sequenceStrings[seq.getAligned()] += "," + expandedName;
                        }else {
                            int num = ct.getNumSeqs(seq.getName()); //checks to make sure seq is in table
                            if (num != 0) { //its in the table
                                ct.mergeCounts(itStrings->second, seq.getName()); //merges counts and saves in uniques name
                            }
                        }
                    }else {
                        if (format == "name") {  sequenceStrings[seq.getAligned()] += "," + seq.getName(); }
                        else {  int currentReps = newCt.getNumSeqs(itStrings->second); newCt.setNumSeqs(itStrings->second, currentReps+1);  }
                    }
				}
				count++;
			}
			
			util.gobble(in);
			
			if(count % 1000 == 0)	{ m->mothurOutJustToScreen(toString(count) + "\t" + toString(sequenceStrings.size()) + "\n");	}
		}
		
		if(count % 1000 != 0)	{ m->mothurOut(toString(count) + "\t" + toString(sequenceStrings.size())); m->mothurOutEndLine();	}
		
		in.close();
		outFasta.close();
		
		if (m->getControl_pressed()) { util.mothurRemove(outFastaFile); return 0; }
        
		//print new names file
		ofstream outNames;
		if (format == "name") { util.openOutputFile(outNameFile, outNames); outputNames.push_back(outNameFile); outputTypes["name"].push_back(outNameFile);   }
        else { util.openOutputFile(outCountFile, outNames); outputTypes["count"].push_back(outCountFile); outputNames.push_back(outCountFile);                }
        
        if ((countfile != "") && (format == "count")) { ct.printHeaders(outNames); }
        else if ((countfile == "") && (format == "count")) { newCt.printHeaders(outNames); }
		
		for (int i = 0; i < nameFileOrder.size(); i++) {
			if (m->getControl_pressed()) { outputTypes.clear(); util.mothurRemove(outFastaFile); outNames.close(); for (int j = 0; j < outputNames.size(); j++) { util.mothurRemove(outputNames[j]); } return 0; }
			
			itStrings = sequenceStrings.find(nameFileOrder[i]);
			
			if (itStrings != sequenceStrings.end()) {
                if (format == "name") {
                    //get rep name
                    int pos = (itStrings->second).find_first_of(',');
                    
                    if (pos == string::npos) { // only reps itself
                        outNames << itStrings->second << '\t' << itStrings->second << endl;
                    }else {
                        outNames << (itStrings->second).substr(0, pos) << '\t' << itStrings->second << endl;
                    }
                }else {
                    if (countfile != "") {  ct.printSeq(outNames, itStrings->second);  }
                    else if (format == "count")  {  newCt.printSeq(outNames, itStrings->second);  }
                }
			}else{ m->mothurOut("[ERROR]: mismatch in namefile print.\n");  m->setControl_pressed(true); }
		}
		outNames.close();
		
		if (m->getControl_pressed()) { outputTypes.clear(); util.mothurRemove(outFastaFile); for (int j = 0; j < outputNames.size(); j++) { util.mothurRemove(outputNames[j]); }  return 0; }
		
		m->mothurOut("\nOutput File Names: \n"); 
		outputNames.push_back(outFastaFile);   outputTypes["fasta"].push_back(outFastaFile);  
        for (int i = 0; i < outputNames.size(); i++) {	m->mothurOut(outputNames[i] +"\n"); 	} m->mothurOutEndLine();

		//set fasta file as new current fastafile
		string currentName = "";
		itTypes = outputTypes.find("fasta");
		if (itTypes != outputTypes.end()) {
			if ((itTypes->second).size() != 0) { currentName = (itTypes->second)[0]; current->setFastaFile(currentName); }
		}
		
		itTypes = outputTypes.find("name");
		if (itTypes != outputTypes.end()) {
			if ((itTypes->second).size() != 0) { currentName = (itTypes->second)[0]; current->setNameFile(currentName); }
		}
        
        itTypes = outputTypes.find("count");
		if (itTypes != outputTypes.end()) {
			if ((itTypes->second).size() != 0) { currentName = (itTypes->second)[0]; current->setCountFile(currentName); }
		}
		
		return 0;
	}
	catch(exception& e) {
		m->errorOut(e, "DeconvoluteCommand", "execute");
		exit(1);
	}
}
/**************************************************************************************/
