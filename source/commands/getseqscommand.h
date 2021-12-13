#ifndef GETSEQSCOMMAND_H
#define GETSEQSCOMMAND_H

/*
 *  getseqscommand.h
 *  Mothur
 *
 *  Created by Sarah Westcott on 7/8/09.
 *  Copyright 2009 Schloss Lab UMASS Amherst. All rights reserved.
 *
 */
 
#include "command.hpp"
#include "sequencedb.h"

//**********************************************************************************************************************


class GetSeqsCommand : public Command {
	
	public:
	
		GetSeqsCommand(string);
        GetSeqsCommand(set<string>, string fasta, string list, string dupsFile, string dupsFileType, string output);
		~GetSeqsCommand(){}
	
		vector<string> setParameters();
		string getCommandName()			{ return "get.seqs";				}
		string getCommandCategory()		{ return "Sequence Processing";		}
		
	string getHelpString();	
    string getOutputPattern(string);
    string getCommonQuestions();
		string getCitation() { return "http://www.mothur.org/wiki/Get.seqs"; }
		string getDescription()		{ return "gets sequences from a list, fasta, count, name, group, alignreport, quality, fastq, contigsreport or taxonomy file"; }

		int execute(); 
		void help() { m->mothurOut(getHelpString()); }	
	
	
	private:
		set<string> names;
        vector<string> fastafiles, namefiles, groupfiles, countfiles, alignfiles, listfiles, taxfiles, fastqfiles, contigsreportfiles, qualityfiles, outputNames;
		string accnosfile, accnosfile2, format, inputFileName;
		bool abort, dups;
        map<string, string> uniqueMap;
        map<string, set<string> > sanity; //for debug //maps file type to names chosen for file. something like "fasta" -> vector<string>. If running in debug mode this is filled and we check to make sure all the files have the same names. If they don't we output the differences for the user.
		
        void readFasta(string);
        void readGZFastq(string);
        void readFastq(string);
        void readName(string);
        void readGroup(string);
        void readCount(string);
        void readAlign(string);
        void readList(string);
        void readTax(string);
        void readQual(string);
        void readContigs(string);
		int compareAccnos(string);
        int runSanityCheck(string, string, string, string, string, string);
        int createMisMatchFile(ofstream&, string, string, set<string>, set<string>);

		
};
//**********************************************************************************************************************

#endif

