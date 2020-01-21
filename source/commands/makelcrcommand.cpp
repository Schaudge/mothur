//
//  makelcrcommand.cpp
//  Mothur
//
//  Created by Sarah Westcott on 1/20/20.
//  Copyright © 2020 Schloss Lab. All rights reserved.
//

#include "makelcrcommand.hpp"

//**********************************************************************************************************************
vector<string> MakeLCRCommand::setParameters(){
    try {
        CommandParameter pshared("shared", "InputTypes", "", "", "LRSS", "LRSS", "none","lcr",false,false,true); parameters.push_back(pshared);
        CommandParameter pgroups("groups", "String", "", "", "", "", "","",false,false); parameters.push_back(pgroups);
        CommandParameter pzero("zero", "Number", "", "0.1", "", "", "","",false,false); parameters.push_back(pzero);
        CommandParameter plabel("label", "String", "", "", "", "", "","",false,false); parameters.push_back(plabel);
        CommandParameter pseed("seed", "Number", "", "0", "", "", "","",false,false); parameters.push_back(pseed);
        CommandParameter pinputdir("inputdir", "String", "", "", "", "", "","",false,false); parameters.push_back(pinputdir);
        CommandParameter poutputdir("outputdir", "String", "", "", "", "", "","",false,false); parameters.push_back(poutputdir);
        
        vector<string> myArray;
        for (int i = 0; i < parameters.size(); i++) {    myArray.push_back(parameters[i].name);        }
        return myArray;
    }
    catch(exception& e) {
        m->errorOut(e, "MakeLCRCommand", "setParameters");
        exit(1);
    }
}
//**********************************************************************************************************************
string MakeLCRCommand::getHelpString(){
    try {
        string helpString = "";
        helpString += "The make.lcr command parameters are shared, groups, zero and label. The shared file is required, unless you have a valid current file.\n";
        helpString += "The groups parameter allows you to specify which of the groups in your sharedfile you would like included. The group names are separated by dashes.\n";
        helpString += "The label parameter allows you to select what distance levels you would like, and are also separated by dashes.\n";
        helpString += "The zero parameter allows you to set an value for zero OTUs. Default is 0.1.\n";
        helpString += "The make.lcr command should be in the following format: make.lcr(shared=yourSharedFile).\n";
        helpString += "Example make.lcr(shared=final.opti_mcc.shared, zero=0.25).\n";
        helpString += "The default value for groups is all the groups in your sharedfile, and all labels in your inputfile will be used.\n";
        helpString += "The make.lcr command outputs a .lcr file.\n";
        
        return helpString;
    }
    catch(exception& e) {
        m->errorOut(e, "MakeLCRCommand", "MakeLCRCommand");
        exit(1);
    }
}
//**********************************************************************************************************************
string MakeLCRCommand::getOutputPattern(string type) {
    try {
        string pattern = "";
        
        if (type == "lcr") {  pattern = "[filename],[distance],lcr-[filename],lcr"; }
        else { m->mothurOut("[ERROR]: No definition for type " + type + " output pattern.\n"); m->setControl_pressed(true);  }
        
        return pattern;
    }
    catch(exception& e) {
        m->errorOut(e, "MakeLCRCommand", "getOutputPattern");
        exit(1);
    }
}
//**********************************************************************************************************************
MakeLCRCommand::MakeLCRCommand(){
    try {
        abort = true; calledHelp = true;
        setParameters();
        vector<string> tempOutNames;
        outputTypes["lcr"] = tempOutNames;
    }
    catch(exception& e) {
        m->errorOut(e, "MakeLCRCommand", "MakeLCRCommand");
        exit(1);
    }
}
//**********************************************************************************************************************

MakeLCRCommand::MakeLCRCommand(string option) {
    try {
        abort = false; calledHelp = false; allLines = true;
        
        //allow user to run help
        if(option == "help") { help(); abort = true; calledHelp = true; }
        else if(option == "citation") { citation(); abort = true; calledHelp = true;}
        
        else {
            vector<string> myArray = setParameters();
            
            OptionParser parser(option);
            map<string,string> parameters = parser.getParameters();
            map<string,string>::iterator it;
            
            ValidParameters validParameter;
            
            //check to make sure all parameters are valid for command
            for (it = parameters.begin(); it != parameters.end(); it++) {
                if (!validParameter.isValidParameter(it->first, myArray, it->second)) {  abort = true;  }
            }
            
            //initialize outputTypes
            vector<string> tempOutNames;
            outputTypes["lcr"] = tempOutNames;
            
            //if the user changes the input directory command factory will send this info to us in the output parameter
            string inputDir = validParameter.valid(parameters, "inputdir");
            if (inputDir == "not found"){    inputDir = "";        }
            else {
                string path;
                it = parameters.find("shared");
                //user has given a template file
                if(it != parameters.end()){
                    path = util.hasPath(it->second);
                    //if the user has not given a path then, add inputdir. else leave path alone.
                    if (path == "") {    parameters["shared"] = inputDir + it->second;        }
                }
            }
            
            sharedfile = validParameter.validFile(parameters, "shared");
            if (sharedfile == "not open") { sharedfile = ""; abort = true; }
            else if (sharedfile == "not found") {
                sharedfile = current->getSharedFile();
                if (sharedfile != "") {  m->mothurOut("Using " + sharedfile + " as input file for the shared parameter.\n"); }
                else { m->mothurOut("[ERROR]: No valid current shared file. You must provide a shared file, quitting.\n"); abort = true; }
            }else {  current->setSharedFile(sharedfile); }
            
            //if the user changes the output directory command factory will send this info to us in the output parameter
            outputDir = validParameter.valid(parameters, "outputdir");        if (outputDir == "not found"){    outputDir = util.hasPath(sharedfile);        }
            
            //check for optional parameter and set defaults
            // ...at some point should added some additional type checking...
            label = validParameter.valid(parameters, "label");
            if (label == "not found") { label = ""; }
            else {
                if(label != "all") {  util.splitAtDash(label, labels);  allLines = false;  }
                else { allLines = true;  }
            }
            
            groups = validParameter.valid(parameters, "groups");
            if (groups == "not found") { groups = "";  }
            else {
                util.splitAtDash(groups, Groups);
                if (Groups.size() != 0) { if (Groups[0]== "all") { Groups.clear(); } }
            }
            
            string temp = validParameter.valid(parameters, "zero"); if (temp == "not found") { temp = "0.1";  }
            util.mothurConvert(temp, zeroReplacementValue);
        }

    }
    catch(exception& e) {
        m->errorOut(e, "MakeLCRCommand", "MakeLCRCommand");
        exit(1);
    }
}
//**********************************************************************************************************************

int MakeLCRCommand::execute(){
    try {
    
        if (abort) { if (calledHelp) { return 0; }  return 2;    }
        
        InputData input(sharedfile, "sharedfile", Groups);
        set<string> processedLabels;
        set<string> userLabels = labels;
        string lastLabel = "";
        
        SharedRAbundVectors* lookup = util.getNextShared(input, allLines, userLabels, processedLabels, lastLabel);
        
        while (lookup != NULL) {
            
            if (m->getControl_pressed()) { break; }
            
            process(lookup); delete lookup;
            
            lookup = util.getNextShared(input, allLines, userLabels, processedLabels, lastLabel);
        }
            
        if (m->getControl_pressed()) { for (int i = 0; i < outputNames.size(); i++) {    util.mothurRemove(outputNames[i]);    } outputTypes.clear(); return 0;}
        
        m->mothurOut("\nOutput File Names: \n");
        for (int i = 0; i < outputNames.size(); i++) {    m->mothurOut(outputNames[i] +"\n");     } m->mothurOutEndLine();
        
        return 0;
    }
    catch(exception& e) {
        m->errorOut(e, "MakeLCRCommand", "execute");
        exit(1);
    }
}
//**********************************************************************************************************************
// compute geometric mean through formula
// antilog(((log(1) + log(2) + . . . + log(n))/n)


//x <- c(10, 5, 3, 1,0)
//> x[x==0] <- 0.1
//> log2(x / prod(x)^(1/4))
//[1]  2.3452054  1.3452054  0.6082399 -0.9767226 -4.2986507
void MakeLCRCommand::process(SharedRAbundVectors*& thisLookUp){
    try {
        vector<string> lookupGroups = thisLookUp->getNamesGroups();
        map<string, string> variables;
        variables["[filename]"] = outputDir + util.getRootName(util.getSimpleName(sharedfile));
        variables["[distance]"] = thisLookUp->getLabel();
        string outputFileName = getOutputFileName("lcr",variables);
        
        ofstream out;
        util.openOutputFile(outputFileName, out);
        outputNames.push_back(outputFileName); outputTypes["lcr"].push_back(outputFileName);
                
        vector<SharedRAbundFloatVector*> lookup = thisLookUp->getSharedRAbundFloatVectors();
        vector<string> otuNames = thisLookUp->getOTUNames();
        
        out << "label\tGroup\tnumOtus\t" << util.getStringFromVector(otuNames, "\t") << endl;
        
        for (int i = 0; i < lookup.size(); i++) {
            
            if (m->getControl_pressed()) { break; }
            
            vector<float> abunds = lookup[i]->get();
            
            double geoMean = util.geometricMean(abunds, zeroReplacementValue);
            
            for (int j = 0; j < abunds.size(); j++) { lookup[i]->set(j, log2(abunds[j]/geoMean)); }
            
            lookup[i]->print(out);
            
            delete lookup[i];
        }
        out.close();
    }
    catch(exception& e) {
        m->errorOut(e, "MakeLCRCommand", "process");
        exit(1);
    }
}
//**********************************************************************************************************************

