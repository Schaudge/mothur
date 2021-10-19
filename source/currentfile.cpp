//
//  currentfile.cpp
//  Mothur
//
//  Created by Sarah Westcott on 11/9/17.
//  Copyright © 2017 Schloss Lab. All rights reserved.
//

#include "currentfile.h"

/*********************************************************************************************/
set<string> CurrentFile::getCurrentTypes()  {
    try {
        
        set<string> types;
        types.insert("fasta");
        types.insert("summary");
        types.insert("file");
        types.insert("accnos");
        types.insert("column");
        types.insert("design");
        types.insert("group");
        types.insert("list");
        types.insert("name");
        types.insert("oligos");
        types.insert("order");
        types.insert("ordergroup");
        types.insert("phylip");
        types.insert("qfile");
        types.insert("relabund");
        types.insert("clr");
        types.insert("sabund");
        types.insert("rabund");
        types.insert("sff");
        types.insert("shared");
        types.insert("taxonomy");
        types.insert("constaxonomy");
        types.insert("contigsreport");
        types.insert("tree");
        types.insert("flow");
        types.insert("biom");
        types.insert("count");
        types.insert("processors");
        types.insert("sample");
        
        return types;
    }
    catch(exception& e) {
        m->errorOut(e, "CurrentFile", "getCurrentTypes");
        exit(1);
    }
}
/*********************************************************************************************/
void CurrentFile::printCurrentFiles(string filename)  {
    try {
        lock_guard<std::mutex> guard(currentProtector);
        
        if (filename != "") {
            ofstream out;
            util.openOutputFile(filename, out);
            
            if (accnosfile != "")		{  m->mothurOut("accnos=" + accnosfile, out); m->mothurOutEndLine(out);           }
            if (columnfile != "")		{  m->mothurOut("column=" + columnfile, out); m->mothurOutEndLine(out);			}
            if (designfile != "")		{  m->mothurOut("design=" + designfile, out); m->mothurOutEndLine(out);			}
            if (fastafile != "")		{  m->mothurOut("fasta=" + fastafile, out); m->mothurOutEndLine(out);				}
            if (groupfile != "")		{  m->mothurOut("group=" + groupfile, out); m->mothurOutEndLine(out);				}
            if (listfile != "")			{  m->mothurOut("list=" + listfile, out); m->mothurOutEndLine(out);				}
            if (namefile != "")			{  m->mothurOut("name=" + namefile, out); m->mothurOutEndLine(out);				}
            if (oligosfile != "")		{  m->mothurOut("oligos=" + oligosfile, out); m->mothurOutEndLine(out);			}
            if (orderfile != "")		{  m->mothurOut("order=" + orderfile, out); m->mothurOutEndLine(out);				}
            if (ordergroupfile != "")	{  m->mothurOut("ordergroup=" + ordergroupfile, out); m->mothurOutEndLine(out);	}
            if (phylipfile != "")		{  m->mothurOut("phylip=" + phylipfile, out); m->mothurOutEndLine(out);			}
            if (qualfile != "")			{  m->mothurOut("qfile=" + qualfile, out); m->mothurOutEndLine(out);				}
            if (rabundfile != "")		{  m->mothurOut("rabund=" + rabundfile, out); m->mothurOutEndLine(out);			}
            if (relabundfile != "")		{  m->mothurOut("relabund=" + relabundfile, out); m->mothurOutEndLine(out);		}
            if (clrfile != "")          {  m->mothurOut("clr=" + clrfile, out); m->mothurOutEndLine(out);               }
            if (sabundfile != "")		{  m->mothurOut("sabund=" + sabundfile, out); m->mothurOutEndLine(out);			}
            if (sfffile != "")			{  m->mothurOut("sff=" + sfffile, out); m->mothurOutEndLine(out);					}
            if (sharedfile != "")		{  m->mothurOut("shared=" + sharedfile, out); m->mothurOutEndLine(out);			}
            if (taxonomyfile != "")		{  m->mothurOut("taxonomy=" + taxonomyfile, out); m->mothurOutEndLine(out);		}
            if (constaxonomyfile != "")	{  m->mothurOut("constaxonomy=" + constaxonomyfile, out); m->mothurOutEndLine(out);}
            if (contigsreportfile != ""){  m->mothurOut("contigsreport=" + contigsreportfile, out); m->mothurOutEndLine(out);}
            if (treefile != "")			{  m->mothurOut("tree=" + treefile, out); m->mothurOutEndLine(out);				}
            if (flowfile != "")			{  m->mothurOut("flow=" + flowfile, out); m->mothurOutEndLine(out);				}
            if (biomfile != "")			{  m->mothurOut("biom=" + biomfile, out); m->mothurOutEndLine(out);				}
            if (countfile != "")        {  m->mothurOut("count=" + countfile, out); m->mothurOutEndLine(out);        }
            if (processors != "1")		{  m->mothurOut("processors=" + processors, out); m->mothurOutEndLine(out);		}
            if (summaryfile != "")		{  m->mothurOut("summary=" + summaryfile, out); m->mothurOutEndLine(out);         }
            if (filefile != "")         {  m->mothurOut("file=" + filefile, out); m->mothurOutEndLine(out);               }
            if (samplefile != "")       {  m->mothurOut("sample=" + samplefile, out); m->mothurOutEndLine(out);               }
            
            out.close();
            
        }else {
            if (accnosfile != "")		{  m->mothurOut("accnos=" + accnosfile); m->mothurOutEndLine();			}
            if (columnfile != "")		{  m->mothurOut("column=" + columnfile); m->mothurOutEndLine();			}
            if (designfile != "")		{  m->mothurOut("design=" + designfile); m->mothurOutEndLine();			}
            if (fastafile != "")		{  m->mothurOut("fasta=" + fastafile); m->mothurOutEndLine();				}
            if (groupfile != "")		{  m->mothurOut("group=" + groupfile); m->mothurOutEndLine();				}
            if (listfile != "")			{  m->mothurOut("list=" + listfile); m->mothurOutEndLine();				}
            if (namefile != "")			{  m->mothurOut("name=" + namefile); m->mothurOutEndLine();				}
            if (oligosfile != "")		{  m->mothurOut("oligos=" + oligosfile); m->mothurOutEndLine();			}
            if (orderfile != "")		{  m->mothurOut("order=" + orderfile); m->mothurOutEndLine();				}
            if (ordergroupfile != "")	{  m->mothurOut("ordergroup=" + ordergroupfile); m->mothurOutEndLine();	}
            if (phylipfile != "")		{  m->mothurOut("phylip=" + phylipfile); m->mothurOutEndLine();			}
            if (qualfile != "")			{  m->mothurOut("qfile=" + qualfile); m->mothurOutEndLine();				}
            if (rabundfile != "")		{  m->mothurOut("rabund=" + rabundfile); m->mothurOutEndLine();			}
            if (relabundfile != "")		{  m->mothurOut("relabund=" + relabundfile); m->mothurOutEndLine();		}
            if (clrfile != "")          {  m->mothurOut("clr=" + clrfile); m->mothurOutEndLine();               }
            if (sabundfile != "")		{  m->mothurOut("sabund=" + sabundfile); m->mothurOutEndLine();			}
            if (sfffile != "")			{  m->mothurOut("sff=" + sfffile); m->mothurOutEndLine();					}
            if (sharedfile != "")		{  m->mothurOut("shared=" + sharedfile); m->mothurOutEndLine();			}
            if (taxonomyfile != "")		{  m->mothurOut("taxonomy=" + taxonomyfile); m->mothurOutEndLine();		}
            if (constaxonomyfile != "")	{  m->mothurOut("constaxonomy=" + constaxonomyfile); m->mothurOutEndLine();}
            if (contigsreportfile != ""){  m->mothurOut("contigsreport=" + contigsreportfile); m->mothurOutEndLine();}
            if (treefile != "")			{  m->mothurOut("tree=" + treefile); m->mothurOutEndLine();				}
            if (flowfile != "")			{  m->mothurOut("flow=" + flowfile); m->mothurOutEndLine();				}
            if (biomfile != "")			{  m->mothurOut("biom=" + biomfile); m->mothurOutEndLine();				}
            if (countfile != "")        {  m->mothurOut("count=" + countfile); m->mothurOutEndLine();        }
            if (processors != "1")		{  m->mothurOut("processors=" + processors); m->mothurOutEndLine();		}
            if (summaryfile != "")		{  m->mothurOut("summary=" + summaryfile); m->mothurOutEndLine();         }
            if (filefile != "")         {  m->mothurOut("file=" + filefile); m->mothurOutEndLine();               }
            if (samplefile != "")       {  m->mothurOut("sample=" + samplefile); m->mothurOutEndLine();               }
        }
        
    }
    catch(exception& e) {
        m->errorOut(e, "CurrentFile", "printCurrentFiles");
        exit(1);
    }
}
/*********************************************************************************************/
bool CurrentFile::hasCurrentFiles()  {
    try {
        lock_guard<std::mutex> guard(currentProtector);
        
        bool hasCurrent = false;
        
        if (accnosfile != "")		{  return true;			}
        if (columnfile != "")		{  return true;			}
        if (designfile != "")		{  return true;			}
        if (fastafile != "")		{  return true;			}
        if (groupfile != "")		{  return true;			}
        if (listfile != "")			{  return true;			}
        if (namefile != "")			{  return true;			}
        if (oligosfile != "")		{  return true;			}
        if (orderfile != "")		{  return true;			}
        if (ordergroupfile != "")	{  return true;			}
        if (phylipfile != "")		{  return true;			}
        if (qualfile != "")			{  return true;			}
        if (rabundfile != "")		{  return true;			}
        if (relabundfile != "")		{  return true;			}
        if (clrfile != "")          {  return true;         }
        if (sabundfile != "")		{  return true;			}
        if (sfffile != "")			{  return true;			}
        if (sharedfile != "")		{  return true;			}
        if (taxonomyfile != "")		{  return true;			}
        if (constaxonomyfile != "")	{  return true;			}
        if (contigsreportfile != ""){  return true;			}
        if (treefile != "")			{  return true;			}
        if (flowfile != "")			{  return true;			}
        if (biomfile != "")			{  return true;			}
        if (countfile != "")        {  return true;			}
        if (summaryfile != "")      {  return true;			}
        if (filefile != "")         {  return true;			}
        if (samplefile != "")       {  return true;         }
        if (processors != "1")		{  return true;			}
        
        return hasCurrent;
        
    }
    catch(exception& e) {
        m->errorOut(e, "CurrentFile", "hasCurrentFiles");
        exit(1);
    }
}

/*********************************************************************************************/
void CurrentFile::clearCurrentFiles()  {
    try {
        lock_guard<std::mutex> guard(currentProtector);
        
        phylipfile = "";
        filefile = "";
        columnfile = "";
        listfile = "";
        rabundfile = "";
        sabundfile = "";
        namefile = "";
        groupfile = "";
        designfile = "";
        orderfile = "";
        treefile = "";
        sharedfile = "";
        ordergroupfile = "";
        contigsreportfile = "";
        constaxonomyfile = "";
        relabundfile = "";
        clrfile = "";
        fastafile = "";
        qualfile = "";
        sfffile = "";
        oligosfile = "";
        accnosfile = "";
        taxonomyfile = "";
        flowfile = "";
        biomfile = "";
        countfile = "";
        summaryfile = "";
        samplefile = "";
        unsigned concurentThreadsSupported = std::thread::hardware_concurrency();
        if (concurentThreadsSupported < 1) { concurentThreadsSupported = 1; } //in case thread errors
        processors = toString(concurentThreadsSupported);
    }
    catch(exception& e) {
        m->errorOut(e, "CurrentFile", "clearCurrentFiles");
        exit(1);
    }
}
/*********************************************************************************************/
int CurrentFile::setProcessors(string p)  {
    try {
        lock_guard<std::mutex> guard(currentProtector);
        
        if (!util.isInteger(p)) {
            unsigned concurentThreadsSupported = std::thread::hardware_concurrency();
            if (concurentThreadsSupported < 1) { concurentThreadsSupported = 1; } //in case thread errors
            processors = toString(concurentThreadsSupported);
            m->mothurOut("[ERROR]: " + p + " is not an integer. Setting processors to " + toString(processors) + "\n");
        }else { processors = p;  m->mothurOut("\nUsing " + toString(processors) + " processors.\n"); }
        int numProcessors = 1;
        util.mothurConvert(p, numProcessors);
        return numProcessors;
    }
    catch(exception& e) {
        m->errorOut(e, "CurrentFile", "clearCurrentFiles");
        exit(1);
    }
}
/*********************************************************************************************/
void CurrentFile::setDefaultPath(vector<string> pathnames)  {
    try {
        lock_guard<std::mutex> guard(currentProtector);
        
        defaultPath.clear();
        for (int i = 0; i < pathnames.size(); i++) {
            string pathname = pathnames[i];
            if (pathname != "") { //add / to name if needed
                string lastChar = pathname.substr(pathname.length()-1);
                if (lastChar != PATH_SEPARATOR) { pathname += PATH_SEPARATOR; }
            }
            defaultPath.push_back(util.getFullPathName(pathname));
        }
    }
    catch(exception& e) {
        m->errorOut(e, "CurrentFile", "setDefaultPath");
        exit(1);
    }
}
/*********************************************************************************************/
void CurrentFile::setTestFilePath(string pathname)  {
    try {
        lock_guard<std::mutex> guard(currentProtector);
        
        if (pathname != "") {
            //add / to name if needed
            string lastChar = pathname.substr(pathname.length()-1);
            if (lastChar != PATH_SEPARATOR) { pathname += PATH_SEPARATOR; }
        }
        
        testFilePath = util.getFullPathName(pathname);
        
    }
    catch(exception& e) {
        m->errorOut(e, "CurrentFile", "setTestFilePath");
        exit(1);
    }
}
/*********************************************************************************************/
void CurrentFile::setBlastPath(string pathname)  {
    try {
        lock_guard<std::mutex> guard(currentProtector);
        
        if (pathname != "") {
            //add / to name if needed
            string lastChar = pathname.substr(pathname.length()-1);
            if (lastChar != PATH_SEPARATOR) { pathname += PATH_SEPARATOR; }
        }
        blastPath = util.getFullPathName(pathname);
        
    }
    catch(exception& e) {
        m->errorOut(e, "CurrentFile", "setBlastPath");
        exit(1);
    }
}
/*********************************************************************************************/
void CurrentFile::setHomePath(string pathname)  {
    try {
        lock_guard<std::mutex> guard(currentProtector);
        
        if (pathname != "") {
            //add / to name if needed
            string lastChar = pathname.substr(pathname.length()-1);
            if (lastChar != PATH_SEPARATOR) { pathname += PATH_SEPARATOR; }
        }
        homePath = util.getFullPathName(pathname);
        m->setHomePath(homePath);
        
    }
    catch(exception& e) {
        m->errorOut(e, "CurrentFile", "setHomePath");
        exit(1);
    }
}
/*********************************************************************************************/
void CurrentFile::setPaths(vector<string> pathVariables)  {
    try {
        lock_guard<std::mutex> guard(currentProtector);
        
        for (int i = 0; i < pathVariables.size(); i++) {
            string pathname = pathVariables[i];
            if (pathname != "") {
                //add / to name if needed
                string lastChar = pathname.substr(pathname.length()-1);
                if (lastChar != PATH_SEPARATOR) { pathname += PATH_SEPARATOR; }
            }
            pathVariables[i] = util.getFullPathName(pathname);
        }
        
        paths = pathVariables;
        m->setPaths(paths);
    }
    catch(exception& e) {
        m->errorOut(e, "CurrentFile", "setPaths");
        exit(1);
    }
}
/*********************************************************************************************/
void CurrentFile::setToolsPath(vector<string> pathnames)  {
    try {
        lock_guard<std::mutex> guard(currentProtector);
        
    
        toolsPath.clear();
        for (int i = 0; i < pathnames.size(); i++) {
            string pathname = pathnames[i];
            if (pathname != "") { //add / to name if needed
                string lastChar = pathname.substr(pathname.length()-1);
                if (lastChar != PATH_SEPARATOR) { pathname += PATH_SEPARATOR; }
            }
            toolsPath.push_back(util.getFullPathName(pathname));
        }
        
    }
    catch(exception& e) {
        m->errorOut(e, "CurrentFile", "setToolsPath");
        exit(1);
    }
}
/*********************************************************************************************/
//locations[0] = inputdir paths, locations[1] = outputdirPaths, locations[2] = mothur's exe path, locations[3] = mothur tools paths, locations[4] = mothur_files paths
vector< vector<string> > CurrentFile::getLocations()  {
    try {
        lock_guard<std::mutex> guard(currentProtector);
        
        vector< vector<string> > locations;
        
        vector<string> inputDirs; inputDirs.push_back(inputDir);
        locations.push_back(inputDirs);
        
        vector<string> outputDirs; outputDirs.push_back(outputDir);
        locations.push_back(outputDirs);
        
        vector<string> mothurHome; mothurHome.push_back(mothurProgramPath);
        locations.push_back(mothurHome);
        
        //MOTHUR_TOOLS
        locations.push_back(toolsPath);
        
        //MOTHUR_FILES
        locations.push_back(defaultPath);
        
        
        return locations;
        
    }
    catch(exception& e) {
        m->errorOut(e, "CurrentFile", "setToolsPath");
        exit(1);
    }
}
//{  }
/*********************************************************************************************/
