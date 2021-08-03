/*
 *  getseqscommand.cpp
 *  Mothur
 *
 *  Created by Sarah Westcott on 7/8/09.
 *  Copyright 2009 Schloss Lab UMASS Amherst. All rights reserved.
 *
 */

#include "getseqscommand.h"
#include "sequence.hpp"
#include "listvector.hpp"
#include "counttable.h"
#include "fastqread.h"
#include "inputdata.h"
#include "contigsreport.hpp"
#include "alignreport.hpp"

//**********************************************************************************************************************
vector<string> GetSeqsCommand::setParameters(){	
	try {
		CommandParameter pfasta("fasta", "InputTypes", "", "", "none", "FNGLT", "none","fasta",false,false,true); parameters.push_back(pfasta);
        CommandParameter pfastq("fastq", "InputTypes", "", "", "none", "FNGLT", "none","fastq",false,false,true); parameters.push_back(pfastq);
        CommandParameter pname("name", "InputTypes", "", "", "NameCount", "FNGLT", "none","name",false,false,true); parameters.push_back(pname);
        CommandParameter pcount("count", "InputTypes", "", "", "NameCount-CountGroup", "FNGLT", "none","count",false,false,true); parameters.push_back(pcount);
		CommandParameter pgroup("group", "InputTypes", "", "", "CountGroup", "FNGLT", "none","group",false,false,true); parameters.push_back(pgroup);
		CommandParameter plist("list", "InputTypes", "", "", "none", "FNGLT", "none","list",false,false,true); parameters.push_back(plist);
		CommandParameter ptaxonomy("taxonomy", "InputTypes", "", "", "none", "FNGLT", "none","taxonomy",false,false,true); parameters.push_back(ptaxonomy);
		CommandParameter palignreport("alignreport", "InputTypes", "", "", "none", "FNGLT", "none","alignreport",false,false); parameters.push_back(palignreport);
        CommandParameter pcontigsreport("contigsreport", "InputTypes", "", "", "FNGLT", "FNGLT", "none","contigsreport",false,false); parameters.push_back(pcontigsreport);
		CommandParameter pqfile("qfile", "InputTypes", "", "", "none", "FNGLT", "none","qfile",false,false); parameters.push_back(pqfile);
		CommandParameter paccnos("accnos", "InputTypes", "", "", "none", "none", "none","",false,true,true); parameters.push_back(paccnos);
		CommandParameter pdups("dups", "Boolean", "", "T", "", "", "","",false,false); parameters.push_back(pdups);
		CommandParameter pseed("seed", "Number", "", "0", "", "", "","",false,false); parameters.push_back(pseed);
        CommandParameter pinputdir("inputdir", "String", "", "", "", "", "","",false,false); parameters.push_back(pinputdir);
        CommandParameter pformat("format", "Multiple", "sanger-illumina-solexa-illumina1.8+", "illumina1.8+", "", "", "","",false,false,true); parameters.push_back(pformat);
		CommandParameter poutputdir("outputdir", "String", "", "", "", "", "","",false,false); parameters.push_back(poutputdir);
		CommandParameter paccnos2("accnos2", "InputTypes", "", "", "none", "none", "none","",false,false); parameters.push_back(paccnos2);
        
        abort = false; calledHelp = false;
        
        vector<string> tempOutNames;
        outputTypes["fasta"] = tempOutNames;
        outputTypes["fastq"] = tempOutNames;
        outputTypes["taxonomy"] = tempOutNames;
        outputTypes["name"] = tempOutNames;
        outputTypes["group"] = tempOutNames;
        outputTypes["alignreport"] = tempOutNames;
        outputTypes["contigsreport"] = tempOutNames;
        outputTypes["list"] = tempOutNames;
        outputTypes["qfile"] = tempOutNames;
        outputTypes["count"] = tempOutNames;
        outputTypes["accnosreport"] = tempOutNames;

		vector<string> myArray;
		for (int i = 0; i < parameters.size(); i++) {	myArray.push_back(parameters[i].name);		}
		return myArray;
	}
	catch(exception& e) {
		m->errorOut(e, "GetSeqsCommand", "setParameters");
		exit(1);
	}
}
//**********************************************************************************************************************
string GetSeqsCommand::getHelpString(){	
	try {
		string helpString = "";
		helpString += "The get.seqs command reads an .accnos file and any of the following file types: fasta, name, group, count, list, taxonomy, quality, fastq, contigsreport or alignreport file.\n";
		helpString += "It outputs a file containing only the sequences in the .accnos file.\n";
		helpString += "The get.seqs command parameters are accnos, fasta, name, group, list, taxonomy, qfile, alignreport, contigsreport, fastq and dups.  You must provide accnos unless you have a valid current accnos file, and at least one of the other parameters.\n";
		helpString += "The dups parameter allows you to add the entire line from a name file if you add any name from the line. default=true. \n";
        helpString += "The format parameter is used to indicate whether your sequences are sanger, solexa, illumina1.8+ or illumina, default=illumina1.8+.\n";
		helpString += "The get.seqs command should be in the following format: get.seqs(accnos=yourAccnos, fasta=yourFasta).\n";
		helpString += "Example get.seqs(accnos=amazon.accnos, fasta=amazon.fasta).\n";
		;
		return helpString;
	}
	catch(exception& e) {
		m->errorOut(e, "GetSeqsCommand", "getHelpString");
		exit(1);
	}
}
//**********************************************************************************************************************
string GetSeqsCommand::getOutputPattern(string type) {
    try {
        string pattern = "";
        
        if (type == "fasta")            {   pattern = "[filename],pick,[extension]";    }
        else if (type == "fastq")       {   pattern = "[filename],pick,[extension]";    }
        else if (type == "taxonomy")    {   pattern = "[filename],pick,[extension]";    }
        else if (type == "name")        {   pattern = "[filename],pick,[extension]";    }
        else if (type == "group")       {   pattern = "[filename],pick,[extension]";    }
        else if (type == "count")       {   pattern = "[filename],pick,[extension]";    }
        else if (type == "list")        {   pattern = "[filename],[distance],pick,[extension]";    }
        else if (type == "qfile")       {   pattern = "[filename],pick,[extension]";    }
        else if (type == "accnosreport")        {   pattern = "[filename],pick.accnos.report";      }
        else if (type == "alignreport")         {   pattern = "[filename],pick.align.report";       }
        else if (type == "contigsreport")       {   pattern = "[filename],pick.contigs.report";       }
        else { m->mothurOut("[ERROR]: No definition for type " + type + " output pattern.\n"); m->setControl_pressed(true);  }
        
        return pattern;
    }
    catch(exception& e) {
        m->errorOut(e, "GetSeqsCommand", "getOutputPattern");
        exit(1);
    }
}
//**********************************************************************************************************************

GetSeqsCommand::GetSeqsCommand(set<string> n, string dupsFile, string dupsFileType, string output) {
    try {
        names = n;
        dups = true;
        outputdir = output;
        
        abort = false; calledHelp = false;
        vector<string> tempOutNames;
        outputTypes["name"] = tempOutNames;
        outputTypes["count"] = tempOutNames;
        
        if (dupsFile != "") {
            if (dupsFileType == "count") {
                countfile = dupsFile;
                readCount();
            }else { //names
                namefile = dupsFile;
                readName();
            }
        }
    }
    catch(exception& e) {
        m->errorOut(e, "GetSeqsCommand", "GetSeqsCommand - mothurRun");
        exit(1);
    }
}

//**********************************************************************************************************************
GetSeqsCommand::GetSeqsCommand(string option)  {
	try {
		//allow user to run help
		if(option == "help") { help(); abort = true; calledHelp = true; }
		else if(option == "citation") { citation(); abort = true; calledHelp = true;}
        else if(option == "category") {  abort = true; calledHelp = true;  }
		
		else {
			OptionParser parser(option, setParameters());
			map<string,string> parameters = parser.getParameters();
			
			ValidParameters validParameter;
			
			//check for required parameters
			accnosfile = validParameter.validFile(parameters, "accnos");
			if (accnosfile == "not open") { abort = true; }
			else if (accnosfile == "not found") {  
				accnosfile = current->getAccnosFile(); 
				if (accnosfile != "") {  m->mothurOut("Using " + accnosfile + " as input file for the accnos parameter.\n");  }
				else { 
					m->mothurOut("You have no valid accnos file and accnos is required.\n");  abort = true;
				} 
			}else { current->setAccnosFile(accnosfile); }	
			
			if (accnosfile2 == "not found") { accnosfile2 = ""; }
			
			fastafile = validParameter.validFile(parameters, "fasta");
			if (fastafile == "not open") { fastafile = ""; abort = true; }
			else if (fastafile == "not found") {  fastafile = "";  }
			else { current->setFastaFile(fastafile); }
			
			namefile = validParameter.validFile(parameters, "name");
			if (namefile == "not open") { namefile = ""; abort = true; }
			else if (namefile == "not found") {  namefile = "";  }	
			else { current->setNameFile(namefile); }
			
			groupfile = validParameter.validFile(parameters, "group");
			if (groupfile == "not open") { abort = true; }
			else if (groupfile == "not found") {  groupfile = "";  }	
			else { current->setGroupFile(groupfile); }
			
			alignfile = validParameter.validFile(parameters, "alignreport");
			if (alignfile == "not open") { abort = true; }
			else if (alignfile == "not found") {  alignfile = "";  }
            
            contigsreportfile = validParameter.validFile(parameters, "contigsreport");
            if (contigsreportfile == "not open") { abort = true; }
            else if (contigsreportfile == "not found") {  contigsreportfile = "";  }
            else { current->setContigsReportFile(contigsreportfile); }
			
			listfile = validParameter.validFile(parameters, "list");
			if (listfile == "not open") { abort = true; }
			else if (listfile == "not found") {  listfile = "";  }
			else { current->setListFile(listfile); }
			
			taxfile = validParameter.validFile(parameters, "taxonomy");
			if (taxfile == "not open") { taxfile = ""; abort = true; }
			else if (taxfile == "not found") {  taxfile = "";  }
			else { current->setTaxonomyFile(taxfile); }
			
			qualfile = validParameter.validFile(parameters, "qfile");
			if (qualfile == "not open") { abort = true; }
			else if (qualfile == "not found") {  qualfile = "";  }
			else { current->setQualFile(qualfile); }
            
            fastqfile = validParameter.validFile(parameters, "fastq");
			if (fastqfile == "not open") { abort = true; }
			else if (fastqfile == "not found") {  fastqfile = "";  }
			
			accnosfile2 = validParameter.validFile(parameters, "accnos2");
			if (accnosfile2 == "not open") { abort = true; }
			else if (accnosfile2 == "not found") {  accnosfile2 = "";  }
			
            countfile = validParameter.validFile(parameters, "count");
            if (countfile == "not open") { countfile = ""; abort = true; }
            else if (countfile == "not found") { countfile = "";  }	
            else { current->setCountFile(countfile); }
            
            if ((namefile != "") && (countfile != "")) {
                m->mothurOut("[ERROR]: you may only use one of the following: name or count.\n");  abort = true;
            }
            
            if ((groupfile != "") && (countfile != "")) {
                m->mothurOut("[ERROR]: you may only use one of the following: group or count.\n");  abort=true;
            }

			
			string usedDups = "true";
			string temp = validParameter.valid(parameters, "dups");	if (temp == "not found") { temp = "true"; usedDups = ""; }
			dups = util.isTrue(temp);
            
            format = validParameter.valid(parameters, "format");		if (format == "not found"){	format = "illumina1.8+";	}
            
            if ((format != "sanger") && (format != "illumina") && (format != "illumina1.8+") && (format != "solexa"))  {
                m->mothurOut(format + " is not a valid format. Your format choices are sanger, solexa, illumina1.8+ and illumina, aborting.\n" );
                abort=true;
            }
			
			if ((fastqfile == "") && (fastafile == "") && (namefile == "") && (groupfile == "") && (alignfile == "") && (listfile == "") && (taxfile == "") && (qualfile == "") && (accnosfile2 == "") && (countfile == "") && (contigsreportfile == ""))  { m->mothurOut("You must provide one of the following: fasta, name, group, count, alignreport, contigsreport, taxonomy, quality, fastq or listfile.\n");  abort = true; }
            
            //read accnos file
            if (!abort) { names = util.readAccnos(accnosfile);  } 
		}
	}
	catch(exception& e) {
		m->errorOut(e, "GetSeqsCommand", "GetSeqsCommand");
		exit(1);
	}
}
//**********************************************************************************************************************

int GetSeqsCommand::execute(){
	try {
		
		if (abort) { if (calledHelp) { return 0; }  return 2;	}
        
		//read through the correct file and output lines you want to keep
		if (namefile != "")			    {		readName();			}
		if (fastafile != "")		    {		readFasta();		}
        if (fastqfile != "")		    {		readFastq();		}
		if (groupfile != "")		    {		readGroup();		}
        if (countfile != "")		    {		readCount();		}
		if (alignfile != "")		    {		readAlign();		}
        if (contigsreportfile != "")    {       readContigs();      }
		if (listfile != "")			    {		readList();			}
		if (taxfile != "")			    {		readTax();			}
		if (qualfile != "")			    {		readQual();			}
		if (accnosfile2 != "")		    {		compareAccnos();	}
        
        if (m->getDebug()) { runSanityCheck(); }
		
		if (m->getControl_pressed()) { outputTypes.clear(); for (int i = 0; i < outputNames.size(); i++) {	util.mothurRemove(outputNames[i]);  } return 0; }
		
		
		if (outputNames.size() != 0) {
			m->mothurOut("\nOutput File Names:\n");
			for (int i = 0; i < outputNames.size(); i++) {	m->mothurOut(outputNames[i]+"\n"); 	}
			m->mothurOutEndLine();
			
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
			
			itTypes = outputTypes.find("group");
			if (itTypes != outputTypes.end()) {
				if ((itTypes->second).size() != 0) { currentName = (itTypes->second)[0]; current->setGroupFile(currentName); }
			}
			
			itTypes = outputTypes.find("list");
			if (itTypes != outputTypes.end()) {
				if ((itTypes->second).size() != 0) { currentName = (itTypes->second)[0]; current->setListFile(currentName); }
			}
			
			itTypes = outputTypes.find("taxonomy");
			if (itTypes != outputTypes.end()) {
				if ((itTypes->second).size() != 0) { currentName = (itTypes->second)[0]; current->setTaxonomyFile(currentName); }
			}
			
			itTypes = outputTypes.find("qfile");
			if (itTypes != outputTypes.end()) {
				if ((itTypes->second).size() != 0) { currentName = (itTypes->second)[0]; current->setQualFile(currentName); }
			}
			
            itTypes = outputTypes.find("count");
			if (itTypes != outputTypes.end()) {
				if ((itTypes->second).size() != 0) { currentName = (itTypes->second)[0]; current->setCountFile(currentName); }
			}
		}
		
		return 0;		
	}

	catch(exception& e) {
		m->errorOut(e, "GetSeqsCommand", "execute");
		exit(1);
	}
}
//**********************************************************************************************************************
void GetSeqsCommand::readFastq(){
	try {
		bool wroteSomething = false;
		int selectedCount = 0;
        
		ifstream in; util.openInputFile(fastqfile, in);
		
		string thisOutputDir = outputdir;
		if (outputdir == "") {  thisOutputDir += util.hasPath(fastqfile);  }
		map<string, string> variables;
        variables["[filename]"] = thisOutputDir + util.getRootName(util.getSimpleName(fastqfile));
        variables["[extension]"] = util.getExtension(fastqfile);
		string outputFileName = getOutputFileName("fastq", variables);
		ofstream out;
		util.openOutputFile(outputFileName, out);

        set<string> uniqueNames;
		while(!in.eof()){
			
			if (m->getControl_pressed()) { in.close(); out.close(); util.mothurRemove(outputFileName); return; }
			
			//read sequence name
            bool ignore;
            FastqRead fread(in, ignore, format); util.gobble(in);
            
			if (!ignore) {
                string name = fread.getName();
                
                if (names.count(name) != 0) {
                    if (uniqueNames.count(name) == 0) { //this name hasn't been seen yet
                        wroteSomething = true;
                        selectedCount++;
                        fread.printFastq(out);
                        uniqueNames.insert(name);
                    }else {
                        m->mothurOut("[WARNING]: " + name + " is in your fastq file more than once.  Mothur requires sequence names to be unique. I will only add it once.\n");
                    }
                }
            }
            
			util.gobble(in);
		}
		in.close();
		out.close();
        
		if (wroteSomething == false) { m->mothurOut("Your file does not contain any sequence from the .accnos file.\n");   }
		outputNames.push_back(outputFileName);  outputTypes["fastq"].push_back(outputFileName);
		
		m->mothurOut("Selected " + toString(selectedCount) + " sequences from your fastq file.\n");
		
		return;
	}
	catch(exception& e) {
		m->errorOut(e, "GetSeqsCommand", "readFastq");
		exit(1);
	}
}
//**********************************************************************************************************************
void GetSeqsCommand::readFasta(){
	try {
		string thisOutputDir = outputdir;
		if (outputdir == "") {  thisOutputDir += util.hasPath(fastafile);  }
		map<string, string> variables; 
        variables["[filename]"] = thisOutputDir + util.getRootName(util.getSimpleName(fastafile));
        variables["[extension]"] = util.getExtension(fastafile);
		string outputFileName = getOutputFileName("fasta", variables);
		ofstream out; util.openOutputFile(outputFileName, out);
		
		ifstream in; util.openInputFile(fastafile, in);
		string name;
		
		bool wroteSomething = false;
		int selectedCount = 0;
        
        if (m->getDebug()) { set<string> temp; sanity["fasta"] = temp; }
		
        set<string> uniqueNames; int line = 0; int redundNum = 0;
		while(!in.eof()){
		
			if (m->getControl_pressed()) { in.close(); out.close(); util.mothurRemove(outputFileName);  return; }
			
			Sequence currSeq(in);
			name = currSeq.getName();
            
            if (!dups) {//adjust name if needed
                map<string, string>::iterator it = uniqueMap.find(name);
                if (it != uniqueMap.end()) { currSeq.setName(it->second); }
            }
			
            name = currSeq.getName();
            
			if (name != "") {
                line++;
				//if this name is in the accnos file
				if (names.count(name) != 0) {
                    if (uniqueNames.count(name) == 0) { //this name hasn't been seen yet
                        wroteSomething = true;
					
                        currSeq.printSequence(out);
                        selectedCount++;
                        uniqueNames.insert(name);
                    
                        if (m->getDebug()) { sanity["fasta"].insert(name); }
                    }else {
                        m->mothurOut("[WARNING]: " + name + " is in your fasta file more than once.  Mothur requires sequence names to be unique. I will only add it once.\n");
                        redundNum++;
                    }
                }
			}
			util.gobble(in);
		}
		in.close();	
		out.close();
		
		if (wroteSomething == false) { m->mothurOut("Your file does not contain any sequence from the .accnos file.\n");  }
		outputNames.push_back(outputFileName);  outputTypes["fasta"].push_back(outputFileName); 
		
		m->mothurOut("Selected " + toString(selectedCount) + " sequences from your fasta file.\n");
		
		return;
	}
	catch(exception& e) {
		m->errorOut(e, "GetSeqsCommand", "readFasta");
		exit(1);
	}
}
//**********************************************************************************************************************
void GetSeqsCommand::readQual(){
	try {
		string thisOutputDir = outputdir;
		if (outputdir == "") {  thisOutputDir += util.hasPath(qualfile);  }
		map<string, string> variables; 
        variables["[filename]"] = thisOutputDir + util.getRootName(util.getSimpleName(qualfile));
        variables["[extension]"] = util.getExtension(qualfile);
		string outputFileName = getOutputFileName("qfile", variables);
		ofstream out;
		util.openOutputFile(outputFileName, out);
		
		ifstream in;
		util.openInputFile(qualfile, in);
		string name;
		
		bool wroteSomething = false;
		int selectedCount = 0;
		
        if (m->getDebug()) { set<string> temp; sanity["qual"] = temp; }
		
        set<string> uniqueNames;
		while(!in.eof()){
            
			QualityScores qual(in); util.gobble(in);
            
            if (!dups) {//adjust name if needed
                map<string, string>::iterator it = uniqueMap.find(qual.getName());
                if (it != uniqueMap.end()) { qual.setName(it->second); }
            }
            
            string name = qual.getName();
            
            if (names.count(name) != 0) {
                if (uniqueNames.count(name) == 0) { //this name hasn't been seen yet
                    uniqueNames.insert(name);
                    wroteSomething = true;
                    
                    qual.printQScores(out);
                    selectedCount++;
                    if (m->getDebug()) { sanity["qual"].insert(name); }
                }else {
                    m->mothurOut("[WARNING]: " + name + " is in your qfile more than once.  Mothur requires sequence names to be unique. I will only add it once.\n");
                }
            }
			
			util.gobble(in);
		}
		in.close();
		out.close();
		
		if (wroteSomething == false) { m->mothurOut("Your file does not contain any sequence from the .accnos file.\n");   }
		outputNames.push_back(outputFileName);  outputTypes["qfile"].push_back(outputFileName); 
		
		m->mothurOut("Selected " + toString(selectedCount) + " sequences from your quality file.\n");

		return;
	}
	catch(exception& e) {
		m->errorOut(e, "GetSeqsCommand", "readQual");
		exit(1);
	}
}
//**********************************************************************************************************************
void GetSeqsCommand::readCount(){
	try {
		string thisOutputDir = outputdir;
		if (outputdir == "") {  thisOutputDir += util.hasPath(countfile);  }
		map<string, string> variables; 
		variables["[filename]"] = thisOutputDir + util.getRootName(util.getSimpleName(countfile));
        variables["[extension]"] = util.getExtension(countfile);
		string outputFileName = getOutputFileName("count", variables);
		
        CountTable ct; ct.readTable(countfile, true, false, names);
        
        bool wroteSomething = false;
        int selectedCount = ct.getNumSeqs();
        if (selectedCount != 0) { wroteSomething = true; }
        
        ct.printTable(outputFileName);
		
		if (wroteSomething == false) {  m->mothurOut("Your file does not contain any sequence from the .accnos file.\n");   }
		outputTypes["count"].push_back(outputFileName); outputNames.push_back(outputFileName);
		
		m->mothurOut("Selected " + toString(selectedCount) + " sequences from your count file.\n");
        
		return;
	}
	catch(exception& e) {
		m->errorOut(e, "GetSeqsCommand", "readCount");
		exit(1);
	}
}
//**********************************************************************************************************************
void GetSeqsCommand::readList(){
	try {
		string thisOutputDir = outputdir;
		if (outputdir == "") {  thisOutputDir += util.hasPath(listfile);  }
        map<string, string> variables; 
		variables["[filename]"] = thisOutputDir + util.getRootName(util.getSimpleName(listfile));
        variables["[extension]"] = util.getExtension(listfile);
        InputData input(listfile, "list", nullVector);
        ListVector* list = input.getListVector();
		
		bool wroteSomething = false;
		int selectedCount = 0;
        
        if (m->getDebug()) { set<string> temp; sanity["list"] = temp; }
		
		while(list != NULL) {
			
            set<string> uniqueNames;
			selectedCount = 0;

            //make a new list vector
			ListVector newList;
			newList.setLabel(list->getLabel());
            
            variables["[distance]"] = list->getLabel();
            string outputFileName = getOutputFileName("list", variables);
			
			ofstream out;
			util.openOutputFile(outputFileName, out);
			outputTypes["list"].push_back(outputFileName);  outputNames.push_back(outputFileName);
            
            vector<string> binLabels = list->getLabels();
            vector<string> newBinLabels;
            
            if (m->getControl_pressed()) { out.close();  return; }
			
			//for each bin
			for (int i = 0; i < list->getNumBins(); i++) {
			
				//parse out names that are in accnos file
				string binnames = list->get(i);
                vector<string> bnames;
                util.splitAtComma(binnames, bnames);
				
				string newNames = "";
                for (int j = 0; j < bnames.size(); j++) {
                    string name = bnames[j];
                    
                    //if that name is in the .accnos file, add it
                    if (names.count(name) != 0) {
                        if (uniqueNames.count(name) == 0) { //this name hasn't been seen yet
                            uniqueNames.insert(name);
                            newNames += name + ",";
                            selectedCount++;
                            if (m->getDebug()) { sanity["list"].insert(name); }
                        }else {
                            m->mothurOut("[WARNING]: " + name + " is in your list file more than once.  Mothur requires sequence names to be unique. I will only add it once.\n");
                        }
                    }
                }
			
				//if there are names in this bin add to new list
				if (newNames != "") { 
					newNames = newNames.substr(0, newNames.length()-1); //rip off extra comma
					newList.push_back(newNames);
                    newBinLabels.push_back(binLabels[i]);
				}
			}
				
			//print new listvector
			if (newList.getNumBins() != 0) {
				wroteSomething = true;
				newList.setLabels(newBinLabels);
				newList.print(out, false);
			}
			
			
            out.close();
            
            delete list;
            list = input.getListVector();
		}
		
		
		if (wroteSomething == false) { m->mothurOut("Your file does not contain any sequence from the .accnos file.\n");  }
		
		m->mothurOut("Selected " + toString(selectedCount) + " sequences from your list file.\n");
		
		return;
	}
	catch(exception& e) {
		m->errorOut(e, "GetSeqsCommand", "readList");
		exit(1);
	}
}
//**********************************************************************************************************************
void GetSeqsCommand::readName(){
	try {
		string thisOutputDir = outputdir;
		if (outputdir == "") {  thisOutputDir += util.hasPath(namefile);  }
        map<string, string> variables; 
		variables["[filename]"] = thisOutputDir + util.getRootName(util.getSimpleName(namefile));
        variables["[extension]"] = util.getExtension(namefile);
		string outputFileName = getOutputFileName("name", variables);
		ofstream out; util.openOutputFile(outputFileName, out);
		
		ifstream in; util.openInputFile(namefile, in);
		string name, firstCol, secondCol;
		
		bool wroteSomething = false;
		int selectedCount = 0;
        
        if (m->getDebug()) { set<string> temp; sanity["name"] = temp; }
        if (m->getDebug()) { set<string> temp; sanity["dupname"] = temp; }
		
        set<string> uniqueNames;
		while(!in.eof()){
		
			if (m->getControl_pressed()) { in.close(); out.close(); util.mothurRemove(outputFileName);  return; }

			in >> firstCol;			util.gobble(in);
			in >> secondCol;        util.gobble(in);
			
			string hold = "";
			if (dups) { hold = secondCol; }
			
			vector<string> parsedNames;
			util.splitAtComma(secondCol, parsedNames);
			
			vector<string> validSecond; vector<string> parsedNames2;
            bool parsedError = false;
			for (int i = 0; i < parsedNames.size(); i++) {
                if (names.count(parsedNames[i]) != 0) {
                    if (uniqueNames.count(parsedNames[i]) == 0) { //this name hasn't been seen yet
                        uniqueNames.insert(parsedNames[i]);
                        validSecond.push_back(parsedNames[i]);
                        parsedNames2.push_back(parsedNames[i]);
                        if (m->getDebug()) { sanity["dupname"].insert(parsedNames[i]); }
                    }else {
                        m->mothurOut("[WARNING]: " + parsedNames[i] + " is in your name file more than once.  Mothur requires sequence names to be unique. I will only add it once.\n");
                        parsedError = true;
                    }
				}
			}
            if (parsedError) {
                parsedNames = parsedNames2;
                hold = "";
                if (parsedNames.size() != 0) {
                    for (int i = 0; i < parsedNames.size()-1; i++) {  hold += parsedNames[i] + ',';  }
                    hold += parsedNames[parsedNames.size()-1] + '\n';
                }
            }

			if (dups && (validSecond.size() != 0)) { //dups = true and we want to add someone, then add everyone
				for (int i = 0; i < parsedNames.size(); i++) {  names.insert(parsedNames[i]); if (m->getDebug()) { sanity["dupname"].insert(parsedNames[i]); } }
				out << firstCol << '\t' << hold << endl;
				wroteSomething = true;
				selectedCount += parsedNames.size();
                if (m->getDebug()) { sanity["name"].insert(firstCol); }
			}else {
                
                if (validSecond.size() != 0) {
                    selectedCount += validSecond.size();
                    
                    //if the name in the first column is in the set then print it and any other names in second column also in set
                    if (names.count(firstCol) != 0) {
                        
                        wroteSomething = true;
                        
                        out << firstCol << '\t';
                        
                        //you know you have at least one valid second since first column is valid
                        for (int i = 0; i < validSecond.size()-1; i++) {  out << validSecond[i] << ',';  }
                        out << validSecond[validSecond.size()-1] << endl;
                        
                        if (m->getDebug()) { sanity["name"].insert(firstCol); }
                        
                        
                        //make first name in set you come to first column and then add the remaining names to second column
                    }else {
                        
                        //you want part of this row
                        if (validSecond.size() != 0) {
                            
                            wroteSomething = true;
                            
                            out << validSecond[0] << '\t';
                            //we are changing the unique name in the fasta file
                            uniqueMap[firstCol] = validSecond[0];
                            
                            //you know you have at least one valid second since first column is valid
                            for (int i = 0; i < validSecond.size()-1; i++) {  out << validSecond[i] << ',';  }
                            out << validSecond[validSecond.size()-1] << endl;
                            
                            if (m->getDebug()) { sanity["name"].insert(validSecond[0]); }
                        }
                    }
                }
			}
		}
		in.close(); out.close();
		
		if (wroteSomething == false) { m->mothurOut("Your file does not contain any sequence from the .accnos file.\n");  }
		outputNames.push_back(outputFileName); outputTypes["name"].push_back(outputFileName);
		
		m->mothurOut("Selected " + toString(selectedCount) + " sequences from your name file.\n");
		
		return;
	}
	catch(exception& e) {
		m->errorOut(e, "GetSeqsCommand", "readName");
		exit(1);
	}
}
//**********************************************************************************************************************
void GetSeqsCommand::readGroup(){
	try {
		string thisOutputDir = outputdir;
		if (outputdir == "") {  thisOutputDir += util.hasPath(groupfile);  }
		map<string, string> variables; 
		variables["[filename]"] = thisOutputDir + util.getRootName(util.getSimpleName(groupfile));
        variables["[extension]"] = util.getExtension(groupfile);
		string outputFileName = getOutputFileName("group", variables);
		ofstream out;
		util.openOutputFile(outputFileName, out);
		

		ifstream in;
		util.openInputFile(groupfile, in);
		string name, group;
		
		bool wroteSomething = false;
		int selectedCount = 0;
        
        if (m->getDebug()) { set<string> temp; sanity["group"] = temp; }
		
        set<string> uniqueNames;
		while(!in.eof()){

			if (m->getControl_pressed()) { in.close(); out.close(); util.mothurRemove(outputFileName);  return; }


			in >> name;		util.gobble(in);		//read from first column
			in >> group;			//read from second column
            
			
            if (names.count(name) != 0) {
                if (uniqueNames.count(name) == 0) { //this name hasn't been seen yet
                    uniqueNames.insert(name);
                    wroteSomething = true;
                    
                    out << name  << '\t' << group << endl;
                    selectedCount++;
                    
                    if (m->getDebug()) {  sanity["group"].insert(name); }
                }else {
                    m->mothurOut("[WARNING]: " + name + " is in your group file more than once.  Mothur requires sequence names to be unique. I will only add it once.\n");
                }
            }
					
			util.gobble(in);
		}
		in.close();
		out.close();
		
		if (wroteSomething == false) { m->mothurOut("Your file does not contain any sequence from the .accnos file.\n");  }
		outputNames.push_back(outputFileName);  outputTypes["group"].push_back(outputFileName);
		
		m->mothurOut("Selected " + toString(selectedCount) + " sequences from your group file.\n");

		return;
	}
	catch(exception& e) {
		m->errorOut(e, "GetSeqsCommand", "readGroup");
		exit(1);
	}
}
//**********************************************************************************************************************
void GetSeqsCommand::readTax(){
	try {
		string thisOutputDir = outputdir;
		if (outputdir == "") {  thisOutputDir += util.hasPath(taxfile);  }
		map<string, string> variables; 
		variables["[filename]"] = thisOutputDir + util.getRootName(util.getSimpleName(taxfile));
        variables["[extension]"] = util.getExtension(taxfile);
		string outputFileName = getOutputFileName("taxonomy", variables);
		ofstream out;
		util.openOutputFile(outputFileName, out);
		
		ifstream in;
		util.openInputFile(taxfile, in);
		string name, tax;
		
		bool wroteSomething = false;
		int selectedCount = 0;
        
        if (m->getDebug()) { set<string> temp; sanity["tax"] = temp; }
		
        set<string> uniqueNames;
		while(!in.eof()){

			if (m->getControl_pressed()) { in.close(); out.close(); util.mothurRemove(outputFileName);  return; }

            in >> name; util.gobble(in);
            tax = util.getline(in); util.gobble(in);
            
            if (!dups) {//adjust name if needed
                map<string, string>::iterator it = uniqueMap.find(name);
                if (it != uniqueMap.end()) { name = it->second; }
            }
			
            if (names.count(name) != 0) {
                if (uniqueNames.count(name) == 0) { //this name hasn't been seen yet
                    uniqueNames.insert(name);

                    wroteSomething = true;
				
                    out << name << '\t' << tax << endl;
                    selectedCount++;
                
                    if (m->getDebug()) { sanity["tax"].insert(name); }
                }else {
                    m->mothurOut("[WARNING]: " + name + " is in your taxonomy file more than once.  Mothur requires sequence names to be unique. I will only add it once.\n");
                }
			}
		}
		in.close();
		out.close();
		
		if (wroteSomething == false) { m->mothurOut("Your file does not contain any sequence from the .accnos file.\n");  }
		outputNames.push_back(outputFileName);  outputTypes["taxonomy"].push_back(outputFileName);
		
		m->mothurOut("Selected " + toString(selectedCount) + " sequences from your taxonomy file.\n");
			
		return;

	}
	catch(exception& e) {
		m->errorOut(e, "GetSeqsCommand", "readTax");
		exit(1);
	}
}
//**********************************************************************************************************************
//alignreport file has a column header line then all other lines contain 16 columns.  we just want the first column since that contains the name
void GetSeqsCommand::readAlign(){
	try {
		string thisOutputDir = outputdir;
		if (outputdir == "") {  thisOutputDir += util.hasPath(alignfile);  }
        map<string, string> variables; 
		variables["[filename]"] = thisOutputDir + util.getRootName(util.getSimpleName(alignfile));
		string outputFileName = getOutputFileName("alignreport", variables);
		
        ofstream out; util.openOutputFile(outputFileName, out);
        ifstream in; util.openInputFile(alignfile, in);
		
        AlignReport report;
        report.readHeaders(in); util.gobble(in);
        report.printHeaders(out);
		
        bool wroteSomething = false; int selectedCount = 0;
		
        set<string> uniqueNames;
		while(!in.eof()){
		
			if (m->getControl_pressed()) { in.close(); out.close(); util.mothurRemove(outputFileName);  return; }

			report.read(in); util.gobble(in);
            string name = report.getQueryName();
            
            if (!dups) {//adjust name if needed
                map<string, string>::iterator it = uniqueMap.find(name);
                if (it != uniqueMap.end()) { name = it->second; }
            }
			
			//if this name is in the accnos file
            if (names.count(name) != 0) {
                if (uniqueNames.count(name) == 0) { //this name hasn't been seen yet
                    uniqueNames.insert(name);
                    wroteSomething = true;
                    selectedCount++;
                    
                    report.print(out);
                }else {
                    m->mothurOut("[WARNING]: " + name + " is in your alignreport file more than once.  Mothur requires sequence names to be unique. I will only add it once.\n");
                }
			}
		}
		in.close(); out.close();
		
		if (wroteSomething == false) { m->mothurOut("Your file does not contain any sequence from the .accnos file.\n");  }
		outputNames.push_back(outputFileName);  outputTypes["alignreport"].push_back(outputFileName);
		
		m->mothurOut("Selected " + toString(selectedCount) + " sequences from your alignreport file.\n");
		
		return;
	}
	catch(exception& e) {
		m->errorOut(e, "GetSeqsCommand", "readAlign");
		exit(1);
	}
}
//**********************************************************************************************************************
//contigsreport file has a column header line then all other lines contain 8 columns.  we just want the first column since that contains the name
void GetSeqsCommand::readContigs(){
    try {
        string thisOutputDir = outputdir;
        if (outputdir == "") {  thisOutputDir += util.hasPath(contigsreportfile);  }
        map<string, string> variables;
        variables["[filename]"] = thisOutputDir + util.getRootName(util.getSimpleName(contigsreportfile));
        string outputFileName = getOutputFileName("contigsreport", variables);
        ofstream out; util.openOutputFile(outputFileName, out);
        
        bool wroteSomething = false;
        int selectedCount = 0;
        
        set<string> uniqueNames;
        ifstream in; util.openInputFile(contigsreportfile, in);
        
        ContigsReport report;
        report.readHeaders(in); util.gobble(in);
        report.printHeaders(out);
        
        while(!in.eof()){
        
            if (m->getControl_pressed()) { break; }
            
            report.read(in); util.gobble(in);
            string name = report.getName();
            
            if (!dups) {//adjust name if needed
                map<string, string>::iterator it = uniqueMap.find(name);
                if (it != uniqueMap.end()) { name = it->second; }
            }
            
            if (names.count(name) != 0) {
                if (uniqueNames.count(name) == 0) { //this name hasn't been seen yet
                    uniqueNames.insert(name);
                    wroteSomething = true;  selectedCount++;
                
                    report.print(out);
                }else {
                    m->mothurOut("[WARNING]: " + name + " is in your contigsreport file more than once.  Mothur requires sequence names to be unique. I will only add it once.\n");
                }
            }
        }
        in.close();
        out.close();
        
        if (wroteSomething == false) { m->mothurOut("Your file does not contain any sequence from the .accnos file.\n");  ofstream out1; util.openOutputFile(outputFileName, out1); out1.close(); } //reopening file clears header line
        outputNames.push_back(outputFileName);  outputTypes["contigsreport"].push_back(outputFileName);
        
        m->mothurOut("Selected " + toString(selectedCount) + " sequences from your contigsreport file.\n");
        
        return;
    }
    catch(exception& e) {
        m->errorOut(e, "ListSeqsCommand", "readContigs");
        exit(1);
    }
}
//**********************************************************************************************************************
//just looking at common mistakes. 
int GetSeqsCommand::runSanityCheck(){
	try {
        string thisOutputDir = outputdir;
        if (outputdir == "") {  thisOutputDir += util.hasPath(fastafile);  }
        string filename = outputdir + "get.seqs.debug.report";
        
        ofstream out;
		util.openOutputFile(filename, out); 

       
        //compare fasta, name, qual and taxonomy if given to make sure they contain the same seqs
        if (fastafile != "") {
            if (namefile != "") { //compare with fasta
                if (sanity["fasta"] != sanity["name"]) { //create mismatch file
                    createMisMatchFile(out, fastafile, namefile, sanity["fasta"], sanity["name"]);
                }
            }
            if (qualfile != "") {
                if (sanity["fasta"] != sanity["qual"]) { //create mismatch file
                    createMisMatchFile(out, fastafile, qualfile, sanity["fasta"], sanity["qual"]);
                }
            }
            if (taxfile != "") {
                if (sanity["fasta"] != sanity["tax"]) { //create mismatch file
                    createMisMatchFile(out, fastafile, taxfile, sanity["fasta"], sanity["tax"]);
                }
            }
        }
        
        //compare dupnames, groups and list if given to make sure they match
        if (namefile != "") {
            if (groupfile != "") {
                if (sanity["dupname"] != sanity["group"]) { //create mismatch file
                    createMisMatchFile(out, namefile, groupfile, sanity["dupname"], sanity["group"]);
                } 
            }
            if (listfile != "") {
                if (sanity["dupname"] != sanity["list"]) { //create mismatch file
                    createMisMatchFile(out, namefile, listfile, sanity["dupname"], sanity["list"]);
                } 
            }
        }else{

            if ((groupfile != "") && (fastafile != "")) {
                if (sanity["fasta"] != sanity["group"]) { //create mismatch file
                    createMisMatchFile(out, fastafile, groupfile, sanity["fasta"], sanity["group"]);
                } 
            }
        }
        
        out.close();
        
        if (util.isBlank(filename)) { util.mothurRemove(filename); }
        else { m->mothurOut("\n[DEBUG]: " + filename + " contains the file mismatches.\n");outputNames.push_back(filename); outputTypes["debug"].push_back(filename); }
        
        return 0;
    }
	catch(exception& e) {
		m->errorOut(e, "GetSeqsCommand", "runSanityCheck");
		exit(1);
	}
}
//**********************************************************************************************************************
//just looking at common mistakes. 
int GetSeqsCommand::createMisMatchFile(ofstream& out, string filename1, string filename2, set<string> set1, set<string> set2){
	try {
        out << "****************************************" << endl << endl;
        out << "Names unique to " << filename1 << ":\n";
        
        //remove names in set1 that are also in set2
        for (set<string>::iterator it = set1.begin(); it != set1.end();) {
            string name = *it;
            
            if (set2.count(name) == 0)  { out << name << endl;  } //name unique to set1
            else                        { set2.erase(name);     } //you are in both so erase 
            set1.erase(it++);
        }
        
        out << "\nNames unique to " << filename2 << ":\n";
        //output results
        for (set<string>::iterator it = set2.begin(); it != set2.end(); it++) {  out << *it << endl;  }
        
        out << "****************************************" << endl << endl;
        
        return 0;
    }
	catch(exception& e) {
		m->errorOut(e, "GetSeqsCommand", "runSanityCheck");
		exit(1);
	}
}
//**********************************************************************************************************************

int GetSeqsCommand::compareAccnos(){
	try {
		
		string thisOutputDir = outputdir;
		if (outputdir == "") {  thisOutputDir += util.hasPath(accnosfile);  }
        map<string, string> variables; 
		variables["[filename]"] = thisOutputDir + util.getRootName(util.getSimpleName(accnosfile));
		string outputFileName = getOutputFileName("accnosreport", variables);
		
		ofstream out;
		util.openOutputFile(outputFileName, out);
		
		ifstream in;
		util.openInputFile(accnosfile2, in);
		string name;
		
		set<string> namesAccnos2;
		set<string> namesDups;
		set<string> namesAccnos = names;
		
		map<string, int> nameCount;
		
		if (namefile != "") {
			ifstream inName;
			util.openInputFile(namefile, inName);
			
			
			while(!inName.eof()){
				
				if (m->getControl_pressed()) { inName.close(); return 0; }
				
				string thisname, repnames;
				
				inName >> thisname;		util.gobble(inName);		//read from first column
				inName >> repnames;			//read from second column
				
				int num = util.getNumNames(repnames);
				nameCount[thisname] = num;
				
				util.gobble(inName);
			}
			inName.close();	
		}
		
		while(!in.eof()){
			in >> name;
			
			if (namesAccnos.count(name) == 0){ //name unique to accnos2
				int pos = name.find_last_of('_');
				string tempName = name;
				if (pos != string::npos) {  tempName = tempName.substr(pos+1);  }
				if (namesAccnos.count(tempName) == 0){
					namesAccnos2.insert(name);
				}else { //you are in both so erase
					namesAccnos.erase(name);
					namesDups.insert(name);
				}
			}else { //you are in both so erase
				namesAccnos.erase(name);
				namesDups.insert(name);
			}
			
			util.gobble(in);
		}
		in.close();	
		
		out << "Names in both files : " + toString(namesDups.size()) << endl;
		m->mothurOut("Names in both files : " + toString(namesDups.size())); m->mothurOutEndLine();
		
		for (set<string>::iterator it = namesDups.begin(); it != namesDups.end(); it++) {
			out << (*it);
			if (namefile != "") { out << '\t' << nameCount[(*it)]; }
			out << endl;
		}
		
		out << "Names unique to " + accnosfile + " : " + toString(namesAccnos.size()) << endl;
		m->mothurOut("Names unique to " + accnosfile + " : " + toString(namesAccnos.size())); m->mothurOutEndLine();
		
		for (set<string>::iterator it = namesAccnos.begin(); it != namesAccnos.end(); it++) {
			out << (*it);
			if (namefile != "") { out << '\t' << nameCount[(*it)]; }
			out << endl;
		}
		
		out << "Names unique to " + accnosfile2 + " : " + toString(namesAccnos2.size()) << endl;
		m->mothurOut("Names unique to " + accnosfile2 + " : " + toString(namesAccnos2.size())); m->mothurOutEndLine();
		
		for (set<string>::iterator it = namesAccnos2.begin(); it != namesAccnos2.end(); it++) {
			out << (*it);
			if (namefile != "") { out << '\t' << nameCount[(*it)]; }
			out << endl;
		}

		out.close(); 
		
		outputNames.push_back(outputFileName);  outputTypes["accnosreport"].push_back(outputFileName);
		
		return 0;
		
	}
	catch(exception& e) {
		m->errorOut(e, "GetSeqsCommand", "compareAccnos");
		exit(1);
	}
}


//**********************************************************************************************************************

