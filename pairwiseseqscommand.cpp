/*
 *  pairwiseseqscommand.cpp
 *  Mothur
 *
 *  Created by westcott on 10/20/10.
 *  Copyright 2010 Schloss Lab. All rights reserved.
 *
 */

#include "pairwiseseqscommand.h"

//**********************************************************************************************************************
vector<string> PairwiseSeqsCommand::setParameters(){	
	try {
		CommandParameter pfasta("fasta", "InputTypes", "", "", "none", "none", "none","phylip-column",false,true,true); parameters.push_back(pfasta);
		CommandParameter palign("align", "Multiple", "needleman-gotoh-blast-noalign", "needleman", "", "", "","",false,false); parameters.push_back(palign);
		CommandParameter pmatch("match", "Number", "", "1.0", "", "", "","",false,false); parameters.push_back(pmatch);
		CommandParameter pmismatch("mismatch", "Number", "", "-1.0", "", "", "","",false,false); parameters.push_back(pmismatch);
		CommandParameter pgapopen("gapopen", "Number", "", "-2.0", "", "", "","",false,false); parameters.push_back(pgapopen);
		CommandParameter pgapextend("gapextend", "Number", "", "-1.0", "", "", "","",false,false); parameters.push_back(pgapextend);
		CommandParameter pprocessors("processors", "Number", "", "1", "", "", "","",false,false,true); parameters.push_back(pprocessors);
		CommandParameter poutput("output", "Multiple", "column-lt-square-phylip", "column", "", "", "","phylip-column",false,false,true); parameters.push_back(poutput);
		CommandParameter pcalc("calc", "Multiple", "nogaps-eachgap-onegap", "onegap", "", "", "","",false,false); parameters.push_back(pcalc);
		CommandParameter pcountends("countends", "Boolean", "", "T", "", "", "","",false,false); parameters.push_back(pcountends);
		CommandParameter pcompress("compress", "Boolean", "", "F", "", "", "","",false,false); parameters.push_back(pcompress);
		CommandParameter pcutoff("cutoff", "Number", "", "1.0", "", "", "","",false,false,true); parameters.push_back(pcutoff);
		CommandParameter pinputdir("inputdir", "String", "", "", "", "", "","",false,false); parameters.push_back(pinputdir);
		CommandParameter poutputdir("outputdir", "String", "", "", "", "", "","",false,false); parameters.push_back(poutputdir);
		
		vector<string> myArray;
		for (int i = 0; i < parameters.size(); i++) {	myArray.push_back(parameters[i].name);		}
		return myArray;
	}
	catch(exception& e) {
		m->errorOut(e, "PairwiseSeqsCommand", "setParameters");
		exit(1);
	}
}
//**********************************************************************************************************************
string PairwiseSeqsCommand::getHelpString(){	
	try {
		string helpString = "";
		helpString += "The pairwise.seqs command reads a fasta file and creates distance matrix.\n";
		helpString += "The pairwise.seqs command parameters are fasta, align, match, mismatch, gapopen, gapextend, calc, output, cutoff and processors.\n";
		helpString += "The fasta parameter is required. You may enter multiple fasta files by separating their names with dashes. ie. fasta=abrecovery.fasta-amzon.fasta \n";
		helpString += "The align parameter allows you to specify the alignment method to use.  Your options are: gotoh, needleman, blast and noalign. The default is needleman.\n";
		helpString += "The match parameter allows you to specify the bonus for having the same base. The default is 1.0.\n";
		helpString += "The mistmatch parameter allows you to specify the penalty for having different bases.  The default is -1.0.\n";
		helpString += "The gapopen parameter allows you to specify the penalty for opening a gap in an alignment. The default is -2.0.\n";
		helpString += "The gapextend parameter allows you to specify the penalty for extending a gap in an alignment.  The default is -1.0.\n";
		helpString += "The calc parameter allows you to specify the method of calculating the distances.  Your options are: nogaps, onegap or eachgap. The default is onegap.\n";
		helpString += "The countends parameter allows you to specify whether to include terminal gaps in distance.  Your options are: T or F. The default is T.\n";
		helpString += "The cutoff parameter allows you to specify maximum distance to keep. The default is 1.0.\n";
		helpString += "The output parameter allows you to specify format of your distance matrix. Options are column, lt, and square. The default is column.\n";
		helpString += "The compress parameter allows you to indicate that you want the resulting distance file compressed.  The default is false.\n";
		helpString += "The pairwise.seqs command should be in the following format: \n";
		helpString += "pairwise.seqs(fasta=yourfastaFile, align=yourAlignmentMethod) \n";
		helpString += "Example pairwise.seqs(fasta=candidate.fasta, align=blast)\n";
		helpString += "Note: No spaces between parameter labels (i.e. fasta), '=' and parameters (i.e.yourFastaFile).\n";
		return helpString;
	}
	catch(exception& e) {
		m->errorOut(e, "PairwiseSeqsCommand", "getHelpString");
		exit(1);
	}
}
//**********************************************************************************************************************
string PairwiseSeqsCommand::getOutputPattern(string type) {
    try {
        string pattern = "";
        
        if (type == "phylip") {  pattern = "[filename],[outputtag],dist"; } 
        else if (type == "column") { pattern = "[filename],dist"; }
        else { m->mothurOut("[ERROR]: No definition for type " + type + " output pattern.\n"); m->control_pressed = true;  }
        
        return pattern;
    }
    catch(exception& e) {
        m->errorOut(e, "PairwiseSeqsCommand", "getOutputPattern");
        exit(1);
    }
}
//**********************************************************************************************************************
PairwiseSeqsCommand::PairwiseSeqsCommand(){	
	try {
		abort = true; calledHelp = true; 
		setParameters();
		vector<string> tempOutNames;
		outputTypes["phylip"] = tempOutNames;
		outputTypes["column"] = tempOutNames;
	}
	catch(exception& e) {
		m->errorOut(e, "PairwiseSeqsCommand", "PairwiseSeqsCommand");
		exit(1);
	}
}
//**********************************************************************************************************************
PairwiseSeqsCommand::PairwiseSeqsCommand(string option)  {
	try {
		abort = false; calledHelp = false;   
	
		//allow user to run help
		if(option == "help") { help(); abort = true; calledHelp = true; }
		else if(option == "citation") { citation(); abort = true; calledHelp = true;}
		
		else {
			vector<string> myArray = setParameters();
			
			OptionParser parser(option);
			map<string, string> parameters = parser.getParameters(); 
			
			ValidParameters validParameter("pairwise.seqs");
			map<string, string>::iterator it;
			
			//check to make sure all parameters are valid for command
			for (it = parameters.begin(); it != parameters.end(); it++) { 
				if (validParameter.isValidParameter(it->first, myArray, it->second) != true) {  abort = true;  }
			}
			
			//initialize outputTypes
			vector<string> tempOutNames;
			outputTypes["phylip"] = tempOutNames;
			outputTypes["column"] = tempOutNames;
			
			//if the user changes the output directory command factory will send this info to us in the output parameter 
			outputDir = validParameter.validFile(parameters, "outputdir", false);		if (outputDir == "not found"){	outputDir = "";		}
			

			//if the user changes the input directory command factory will send this info to us in the output parameter 
			string inputDir = validParameter.validFile(parameters, "inputdir", false);		
			
			if (inputDir == "not found"){	inputDir = "";		}

			fastaFileName = validParameter.validFile(parameters, "fasta", false);
			if (fastaFileName == "not found") { 				
				//if there is a current fasta file, use it
				string filename = m->getFastaFile(); 
				if (filename != "") { fastaFileNames.push_back(filename); m->mothurOut("Using " + filename + " as input file for the fasta parameter."); m->mothurOutEndLine(); }
				else { 	m->mothurOut("You have no current fastafile and the fasta parameter is required."); m->mothurOutEndLine(); abort = true; }
			}
			else { 
				m->splitAtDash(fastaFileName, fastaFileNames);
				
				//go through files and make sure they are good, if not, then disregard them
				for (int i = 0; i < fastaFileNames.size(); i++) {
					
					bool ignore = false;
					if (fastaFileNames[i] == "current") { 
						fastaFileNames[i] = m->getFastaFile(); 
						if (fastaFileNames[i] != "") {  m->mothurOut("Using " + fastaFileNames[i] + " as input file for the fasta parameter where you had given current."); m->mothurOutEndLine(); }
						else { 	
							m->mothurOut("You have no current fastafile, ignoring current."); m->mothurOutEndLine(); ignore=true; 
							//erase from file list
							fastaFileNames.erase(fastaFileNames.begin()+i);
							i--;
						}
					}
					
					if (!ignore) {
					
						if (inputDir != "") {
							string path = m->hasPath(fastaFileNames[i]);
							//if the user has not given a path then, add inputdir. else leave path alone.
							if (path == "") {	fastaFileNames[i] = inputDir + fastaFileNames[i];		}
						}
		
						int ableToOpen;
						ifstream in;

						ableToOpen = m->openInputFile(fastaFileNames[i], in, "noerror");
					
						//if you can't open it, try default location
						if (ableToOpen == 1) {
							if (m->getDefaultPath() != "") { //default path is set
								string tryPath = m->getDefaultPath() + m->getSimpleName(fastaFileNames[i]);
								m->mothurOut("Unable to open " + fastaFileNames[i] + ". Trying default " + tryPath); m->mothurOutEndLine();
								ifstream in2;
								ableToOpen = m->openInputFile(tryPath, in2, "noerror");
								in2.close();
								fastaFileNames[i] = tryPath;
							}
						}
						
						//if you can't open it, try output location
						if (ableToOpen == 1) {
							if (m->getOutputDir() != "") { //default path is set
								string tryPath = m->getOutputDir() + m->getSimpleName(fastaFileNames[i]);
								m->mothurOut("Unable to open " + fastaFileNames[i] + ". Trying output directory " + tryPath); m->mothurOutEndLine();
								ifstream in2;
								ableToOpen = m->openInputFile(tryPath, in2, "noerror");
								in2.close();
								fastaFileNames[i] = tryPath;
							}
						}
						
						in.close();					

						if (ableToOpen == 1) { 
							m->mothurOut("Unable to open " + fastaFileNames[i] + ". It will be disregarded."); m->mothurOutEndLine(); 
							//erase from file list
							fastaFileNames.erase(fastaFileNames.begin()+i);
							i--;
						}else {
							m->setFastaFile(fastaFileNames[i]);
						}
					}
				}
				
				//make sure there is at least one valid file left
				if (fastaFileNames.size() == 0) { m->mothurOut("no valid files."); m->mothurOutEndLine(); abort = true; }
			}
		
			//check for optional parameter and set defaults
			// ...at some point should added some additional type checking...
			string temp;
			temp = validParameter.validFile(parameters, "match", false);		if (temp == "not found"){	temp = "1.0";			}
			m->mothurConvert(temp, match);  
			
			temp = validParameter.validFile(parameters, "mismatch", false);		if (temp == "not found"){	temp = "-1.0";			}
			m->mothurConvert(temp, misMatch);  
            if (misMatch > 0) { m->mothurOut("[ERROR]: mismatch must be negative.\n"); abort=true; }
			
			temp = validParameter.validFile(parameters, "gapopen", false);		if (temp == "not found"){	temp = "-2.0";			}
			m->mothurConvert(temp, gapOpen);  
            if (gapOpen > 0) { m->mothurOut("[ERROR]: gapopen must be negative.\n"); abort=true; }
			
			temp = validParameter.validFile(parameters, "gapextend", false);	if (temp == "not found"){	temp = "-1.0";			}
			m->mothurConvert(temp, gapExtend); 
            if (gapExtend > 0) { m->mothurOut("[ERROR]: gapextend must be negative.\n"); abort=true; }
			
			temp = validParameter.validFile(parameters, "processors", false);	if (temp == "not found"){	temp = m->getProcessors();	}
			m->setProcessors(temp);
			m->mothurConvert(temp, processors);
			
			temp = validParameter.validFile(parameters, "cutoff", false);		if(temp == "not found"){	temp = "1.0"; }
			m->mothurConvert(temp, cutoff); 
			
			temp = validParameter.validFile(parameters, "countends", false);	if(temp == "not found"){	temp = "T";	}
			countends = m->isTrue(temp); 
			
			temp = validParameter.validFile(parameters, "compress", false);		if(temp == "not found"){  temp = "F"; }
			compress = m->isTrue(temp); 
			
			align = validParameter.validFile(parameters, "align", false);		if (align == "not found"){	align = "needleman";	}
			
			output = validParameter.validFile(parameters, "output", false);		if(output == "not found"){	output = "column"; }
            if (output=="phylip") { output = "lt"; }
			if ((output != "column") && (output != "lt") && (output != "square")) { m->mothurOut(output + " is not a valid output form. Options are column, lt and square. I will use column."); m->mothurOutEndLine(); output = "column"; }
			
			calc = validParameter.validFile(parameters, "calc", false);			
			if (calc == "not found") { calc = "onegap";  }
			else { 
				 if (calc == "default")  {  calc = "onegap";  }
			}
			m->splitAtDash(calc, Estimators);
		}
		
	}
	catch(exception& e) {
		m->errorOut(e, "PairwiseSeqsCommand", "PairwiseSeqsCommand");
		exit(1);
	}
}
//**********************************************************************************************************************

int PairwiseSeqsCommand::execute(){
	try {
		if (abort == true) { if (calledHelp) { return 0; }  return 2;	}
		
		longestBase = 2000; //will need to update this in driver if we find sequences with more bases.  hardcoded so we don't have the pre-read user fasta file.
		
		cutoff += 0.005;
		
		for (int s = 0; s < fastaFileNames.size(); s++) {
			if (m->control_pressed) { outputTypes.clear(); return 0; }
			
			m->mothurOut("Processing sequences from " + fastaFileNames[s] + " ..." ); m->mothurOutEndLine();
			
			if (outputDir == "") {  outputDir += m->hasPath(fastaFileNames[s]); }
			
			ifstream inFASTA;
			m->openInputFile(fastaFileNames[s], inFASTA);
			alignDB = SequenceDB(inFASTA); 
			inFASTA.close();
			
			int numSeqs = alignDB.getNumSeqs();
			int startTime = time(NULL);
			string outputFile = "";
			
            map<string, string> variables; 
            variables["[filename]"] = outputDir + m->getRootName(m->getSimpleName(fastaFileNames[s]));
			if (output == "lt") { //does the user want lower triangle phylip formatted file 
				variables["[outputtag]"] = "phylip";
                outputFile = getOutputFileName("phylip", variables);
				m->mothurRemove(outputFile); outputTypes["phylip"].push_back(outputFile);
			}else if (output == "column") { //user wants column format
				outputFile = getOutputFileName("column", variables);
				outputTypes["column"].push_back(outputFile);
				m->mothurRemove(outputFile);
			}else { //assume square
                variables["[outputtag]"] = "square";
                outputFile = getOutputFileName("phylip", variables);
				m->mothurRemove(outputFile);
				outputTypes["phylip"].push_back(outputFile);
			}
			
			#ifdef USE_MPI
		
			int pid, start, end; 
			int tag = 2001;
					
			MPI_Status status; 
			MPI_Comm_size(MPI_COMM_WORLD, &processors); //set processors to the number of mpi processes running
			MPI_Comm_rank(MPI_COMM_WORLD, &pid); //find out who we are
			
			//each process gets where it should start and stop in the file
			if (output != "square") {
				start = int (sqrt(float(pid)/float(processors)) * numSeqs);
				end = int (sqrt(float(pid+1)/float(processors)) * numSeqs);
			}else{
				start = int ((float(pid)/float(processors)) * numSeqs);
				end = int ((float(pid+1)/float(processors)) * numSeqs);
			}
			
			if (output == "column") {
				MPI_File outMPI;
				int amode=MPI_MODE_CREATE|MPI_MODE_WRONLY; 

			char filename[1024];
				strcpy(filename, outputFile.c_str());
				
				MPI_File_open(MPI_COMM_WORLD, filename, amode, MPI_INFO_NULL, &outMPI);

				if (pid == 0) { //you are the root process 
				
					//do your part
					string outputMyPart;
					
					driverMPI(start, end, outMPI, cutoff); 
					
					if (m->control_pressed) { outputTypes.clear(); MPI_File_close(&outMPI);  m->mothurRemove(outputFile); return 0; }
				
					//wait on chidren
					for(int i = 1; i < processors; i++) { 
						if (m->control_pressed) { outputTypes.clear();  MPI_File_close(&outMPI);   m->mothurRemove(outputFile);  return 0; }
						
						char buf[5];
						MPI_Recv(buf, 5, MPI_CHAR, i, tag, MPI_COMM_WORLD, &status); 
					}
				}else { //you are a child process
					//do your part
					driverMPI(start, end, outMPI, cutoff); 
					
					if (m->control_pressed) { outputTypes.clear();  MPI_File_close(&outMPI);  m->mothurRemove(outputFile);  return 0; }
				
					char buf[5];
					strcpy(buf, "done"); 
					//tell parent you are done.
					MPI_Send(buf, 5, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
				}
				
				MPI_File_close(&outMPI);
				
			}else { //lower triangle format
				if (pid == 0) { //you are the root process 
				
					//do your part
					string outputMyPart;
					unsigned long long mySize;
					
					if (output != "square"){ driverMPI(start, end, outputFile, mySize); }
					else { driverMPI(start, end, outputFile, mySize, output); }
		
					if (m->control_pressed) {  outputTypes.clear();   m->mothurRemove(outputFile);   return 0; }
					
					int amode=MPI_MODE_APPEND|MPI_MODE_WRONLY|MPI_MODE_CREATE; //
					MPI_File outMPI;
					MPI_File inMPI;

					char filename[1024];
					strcpy(filename, outputFile.c_str());

					MPI_File_open(MPI_COMM_SELF, filename, amode, MPI_INFO_NULL, &outMPI);

					//wait on chidren
					for(int b = 1; b < processors; b++) { 
						unsigned long long fileSize;
						
						if (m->control_pressed) { outputTypes.clear();  MPI_File_close(&outMPI);  m->mothurRemove(outputFile);   return 0; }
						
						MPI_Recv(&fileSize, 1, MPI_LONG, b, tag, MPI_COMM_WORLD, &status); 
						
						string outTemp = outputFile + toString(b) + ".temp";

						char* buf = new char[outTemp.length()];
						memcpy(buf, outTemp.c_str(), outTemp.length());
						
						MPI_File_open(MPI_COMM_SELF, buf, MPI_MODE_DELETE_ON_CLOSE|MPI_MODE_RDONLY, MPI_INFO_NULL, &inMPI);
						delete buf;

						int count = 0;
						while (count < fileSize) { 
							char buf2[1];
							MPI_File_read(inMPI, buf2, 1, MPI_CHAR, &status);
							MPI_File_write(outMPI, buf2, 1, MPI_CHAR, &status);
							count += 1;
						}
						
						MPI_File_close(&inMPI); //deleted on close
					}
					
					MPI_File_close(&outMPI);
				}else { //you are a child process
					//do your part
					unsigned long long size;
					if (output != "square"){ driverMPI(start, end, (outputFile + toString(pid) + ".temp"), size); }
					else { driverMPI(start, end, (outputFile + toString(pid) + ".temp"), size, output); }
					
					if (m->control_pressed) {  return 0; }
				
					//tell parent you are done.
					MPI_Send(&size, 1, MPI_LONG, 0, tag, MPI_COMM_WORLD);
				}
			}
			MPI_Barrier(MPI_COMM_WORLD); //make everyone wait - just in case
	#else		
					
		//#if defined (__APPLE__) || (__MACH__) || (linux) || (__linux) || (__linux__) || (__unix__) || (__unix)
			//if you don't need to fork anything
			if(processors == 1){
				if (output != "square") {  driver(0, numSeqs, outputFile, cutoff); }
				else { driver(0, numSeqs, outputFile, "square");  }
			}else{ //you have multiple processors
				
				for (int i = 0; i < processors; i++) {
					distlinePair tempLine;
					lines.push_back(tempLine);
					if (output != "square") {
						lines[i].start = int (sqrt(float(i)/float(processors)) * numSeqs);
						lines[i].end = int (sqrt(float(i+1)/float(processors)) * numSeqs);
					}else{
						lines[i].start = int ((float(i)/float(processors)) * numSeqs);
						lines[i].end = int ((float(i+1)/float(processors)) * numSeqs);
					}
				}
				
				createProcesses(outputFile); 
			}
		//#else
			//ifstream inFASTA;
			//if (output != "square") {  driver(0, numSeqs, outputFile, cutoff); }
			//else { driver(0, numSeqs, outputFile, "square");  }
		//#endif
		
	#endif
			if (m->control_pressed) { outputTypes.clear();   m->mothurRemove(outputFile); return 0; }
			
			#ifdef USE_MPI
				MPI_Comm_rank(MPI_COMM_WORLD, &pid); 
						
				if (pid == 0) { //only one process should output to screen
			#endif
			
			ifstream fileHandle;
			fileHandle.open(outputFile.c_str());
			if(fileHandle) {
				m->gobble(fileHandle);
				if (fileHandle.eof()) { m->mothurOut(outputFile + " is blank. This can result if there are no distances below your cutoff.");  m->mothurOutEndLine(); }
			}
			
			if (compress) {
				m->mothurOut("Compressing..."); m->mothurOutEndLine();
				m->mothurOut("(Replacing " + outputFile + " with " + outputFile + ".gz)"); m->mothurOutEndLine();
				system(("gzip -v " + outputFile).c_str());
				outputNames.push_back(outputFile + ".gz");
			}else { outputNames.push_back(outputFile); }
			
			#ifdef USE_MPI
				}
			#endif
			
			m->mothurOut("It took " + toString(time(NULL) - startTime) + " to calculate the distances for " + toString(numSeqs) + " sequences."); m->mothurOutEndLine();
			
			if (m->control_pressed) { outputTypes.clear(); m->mothurRemove(outputFile); return 0; }
		}
		
		//set phylip file as new current phylipfile
		string current = "";
		itTypes = outputTypes.find("phylip");
		if (itTypes != outputTypes.end()) {
			if ((itTypes->second).size() != 0) { current = (itTypes->second)[0]; m->setPhylipFile(current); }
		}
		
		//set column file as new current columnfile
		itTypes = outputTypes.find("column");
		if (itTypes != outputTypes.end()) {
			if ((itTypes->second).size() != 0) { current = (itTypes->second)[0]; m->setColumnFile(current); }
		}
		
		m->mothurOutEndLine();
		m->mothurOut("Output File Names: "); m->mothurOutEndLine();
		for (int i = 0; i < outputNames.size(); i++) {	m->mothurOut(outputNames[i]); m->mothurOutEndLine();	}
		m->mothurOutEndLine();
		

		return 0;
	}
	catch(exception& e) {
		m->errorOut(e, "PairwiseSeqsCommand", "execute");
		exit(1);
	}
}

/**************************************************************************************************/
void PairwiseSeqsCommand::createProcesses(string filename) {
	try {
        int process = 1;
		processIDS.clear();
        
#if defined (__APPLE__) || (__MACH__) || (linux) || (__linux) || (__linux__) || (__unix__) || (__unix)
		
		
		//loop through and create all the processes you want
		while (process != processors) {
			pid_t pid = fork();
			
			if (pid > 0) {
				processIDS.push_back(pid); 
				process++;
			}else if (pid == 0){
				if (output != "square") {  driver(lines[process].start, lines[process].end, filename + m->mothurGetpid(process) + ".temp", cutoff); }
				else { driver(lines[process].start, lines[process].end, filename + m->mothurGetpid(process) + ".temp", "square"); }
				exit(0);
			}else { 
				m->mothurOut("[ERROR]: unable to spawn the necessary processes."); m->mothurOutEndLine(); 
				for (int i=0;i<processIDS.size();i++) { int temp = processIDS[i]; kill (temp, SIGINT); }
				exit(0);
			}
		}
		
		//parent do my part
		if (output != "square") {  driver(lines[0].start, lines[0].end, filename, cutoff); }
		else { driver(lines[0].start, lines[0].end, filename, "square"); }

		
		//force parent to wait until all the processes are done
		for (int i=0;i<processIDS.size();i++) { 
			int temp = processIDS[i];
			wait(&temp);
		}
#else     
        //////////////////////////////////////////////////////////////////////////////////////////////////////
		//Windows version shared memory, so be careful when passing variables through the distanceData struct. 
		//Above fork() will clone, so memory is separate, but that's not the case with windows, 
		//that's why the distance calculator was moved inside of the driver to make separate copies.
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		
		vector<pairwiseData*> pDataArray; //[processors-1];
		DWORD   dwThreadIdArray[processors-1];
		HANDLE  hThreadArray[processors-1]; 
		
		//Create processor-1 worker threads.
		for( int i=0; i<processors-1; i++ ){
			string extension = toString(i) + ".temp";

			// Allocate memory for thread data.
			pairwiseData* tempDist = new pairwiseData((filename+extension), align, "square", Estimators[0], countends, output, alignDB, m, lines[i+1].start, lines[i+1].end, match, misMatch, gapOpen, gapExtend, longestBase, cutoff, i);
			pDataArray.push_back(tempDist);
			processIDS.push_back(i);
			
			if (output != "square") { hThreadArray[i] = CreateThread(NULL, 0, MyPairwiseThreadFunction, pDataArray[i], 0, &dwThreadIdArray[i]);  } 
            else { hThreadArray[i] = CreateThread(NULL, 0, MyPairwiseSquareThreadFunction, pDataArray[i], 0, &dwThreadIdArray[i]);  }
		}
		
		//do your part
		if (output != "square") {  driver(lines[0].start, lines[0].end, filename, cutoff); }
		else { driver(lines[0].start, lines[0].end, filename, "square"); }
		
		//Wait until all threads have terminated.
		WaitForMultipleObjects(processors-1, hThreadArray, TRUE, INFINITE);
		
		//Close all thread handles and free memory allocations.
		for(int i=0; i < pDataArray.size(); i++){
            if (pDataArray[i]->count != (pDataArray[i]->end-pDataArray[i]->start)) {
                m->mothurOut("[ERROR]: process " + toString(i) + " only processed " + toString(pDataArray[i]->count) + " of " + toString(pDataArray[i]->end-pDataArray[i]->start) + " sequences assigned to it, quitting. \n"); m->control_pressed = true; 
            }
			CloseHandle(hThreadArray[i]);
			delete pDataArray[i];
		}

#endif
        
        //append and remove temp files
		for (int i=0;i<processIDS.size();i++) { 
			m->appendFiles((filename + toString(processIDS[i]) + ".temp"), filename);
			m->mothurRemove((filename + toString(processIDS[i]) + ".temp"));
		}
        
	}
	catch(exception& e) {
		m->errorOut(e, "PairwiseSeqsCommand", "createProcesses");
		exit(1);
	}
}

/**************************************************************************************************/
/////// need to fix to work with calcs and sequencedb
int PairwiseSeqsCommand::driver(int startLine, int endLine, string dFileName, float cutoff){
	try {

		int startTime = time(NULL);
        
        Alignment* alignment;
        if(align == "gotoh")			{	alignment = new GotohOverlap(gapOpen, gapExtend, match, misMatch, longestBase);			}
		else if(align == "needleman")	{	alignment = new NeedlemanOverlap(gapOpen, match, misMatch, longestBase);				}
		else if(align == "blast")		{	alignment = new BlastAlignment(gapOpen, gapExtend, match, misMatch);		}
		else if(align == "noalign")		{	alignment = new NoAlign();													}
		else {
			m->mothurOut(align + " is not a valid alignment option. I will run the command using needleman.");
			m->mothurOutEndLine();
			alignment = new NeedlemanOverlap(gapOpen, match, misMatch, longestBase);
		}
        
        ValidCalculators validCalculator;
        Dist* distCalculator;
        if (countends) {
            if (validCalculator.isValidCalculator("distance", Estimators[0]) == true) { 
                if (Estimators[0] == "nogaps")			{	distCalculator = new ignoreGaps();	}
                else if (Estimators[0] == "eachgap")	{	distCalculator = new eachGapDist();	}
                else if (Estimators[0] == "onegap")		{	distCalculator = new oneGapDist();	}
            }
        }else {
            if (validCalculator.isValidCalculator("distance", Estimators[0]) == true) { 
                if (Estimators[0] == "nogaps")		{	distCalculator = new ignoreGaps();					}
                else if (Estimators[0] == "eachgap"){	distCalculator = new eachGapIgnoreTermGapDist();	}
                else if (Estimators[0] == "onegap")	{	distCalculator = new oneGapIgnoreTermGapDist();		}
            }
        }
		
		//column file
		ofstream outFile(dFileName.c_str(), ios::trunc);
		outFile.setf(ios::fixed, ios::showpoint);
		outFile << setprecision(4);
		
		if((output == "lt") && startLine == 0){	outFile << alignDB.getNumSeqs() << endl;	}
		
		for(int i=startLine;i<endLine;i++){
			if(output == "lt")	{	
				string name = alignDB.get(i).getName();
				if (name.length() < 10) { //pad with spaces to make compatible
					while (name.length() < 10) {  name += " ";  }
				}
				outFile << name << '\t';	
			}
			
			for(int j=0;j<i;j++){
				
				if (m->control_pressed) { outFile.close(); delete alignment; delete distCalculator; return 0;  }
				
				if (alignDB.get(i).getUnaligned().length() > alignment->getnRows()) {
					alignment->resize(alignDB.get(i).getUnaligned().length()+1);
				}
				
				if (alignDB.get(j).getUnaligned().length() > alignment->getnRows()) {
					alignment->resize(alignDB.get(j).getUnaligned().length()+1);
				}
				
				Sequence seqI(alignDB.get(i).getName(), alignDB.get(i).getAligned());
				Sequence seqJ(alignDB.get(j).getName(), alignDB.get(j).getAligned());
				
				alignment->align(seqI.getUnaligned(), seqJ.getUnaligned());
				seqI.setAligned(alignment->getSeqAAln());
				seqJ.setAligned(alignment->getSeqBAln());
                
				distCalculator->calcDist(seqI, seqJ);
				double dist = distCalculator->getDist();
                
                if (m->debug) { m->mothurOut("[DEBUG]: " + seqI.getName() + '\t' +  alignment->getSeqAAln() + '\n' + seqJ.getName() + alignment->getSeqBAln() + '\n' + "distance = " + toString(dist) + "\n"); }
				                
				if(dist <= cutoff){
					if (output == "column") { outFile << alignDB.get(i).getName() << ' ' << alignDB.get(j).getName() << ' ' << dist << endl; }
				}
				if (output == "lt") {  outFile << dist << '\t'; }
			}
			
			if (output == "lt") { outFile << endl; }
			
			if(i % 100 == 0){
				m->mothurOutJustToScreen(toString(i) + "\t" + toString(time(NULL) - startTime)+"\n");
			}
			
		}
		m->mothurOutJustToScreen(toString(endLine-1) + "\t" + toString(time(NULL) - startTime)+"\n");
		
		outFile.close();
        delete alignment;
        delete distCalculator;
		
		return 1;
	}
	catch(exception& e) {
		m->errorOut(e, "PairwiseSeqsCommand", "driver");
		exit(1);
	}
}
/**************************************************************************************************/
/////// need to fix to work with calcs and sequencedb
int PairwiseSeqsCommand::driver(int startLine, int endLine, string dFileName, string square){
	try {

		int startTime = time(NULL);
        
        Alignment* alignment;
        if(align == "gotoh")			{	alignment = new GotohOverlap(gapOpen, gapExtend, match, misMatch, longestBase);			}
		else if(align == "needleman")	{	alignment = new NeedlemanOverlap(gapOpen, match, misMatch, longestBase);				}
		else if(align == "blast")		{	alignment = new BlastAlignment(gapOpen, gapExtend, match, misMatch);		}
		else if(align == "noalign")		{	alignment = new NoAlign();													}
		else {
			m->mothurOut(align + " is not a valid alignment option. I will run the command using needleman.");
			m->mothurOutEndLine();
			alignment = new NeedlemanOverlap(gapOpen, match, misMatch, longestBase);
		}
		
        ValidCalculators validCalculator;
        Dist* distCalculator;
        if (countends) {
            if (validCalculator.isValidCalculator("distance", Estimators[0]) == true) { 
                if (Estimators[0] == "nogaps")			{	distCalculator = new ignoreGaps();	}
                else if (Estimators[0] == "eachgap")	{	distCalculator = new eachGapDist();	}
                else if (Estimators[0] == "onegap")		{	distCalculator = new oneGapDist();	}
            }
        }else {
            if (validCalculator.isValidCalculator("distance", Estimators[0]) == true) { 
                if (Estimators[0] == "nogaps")		{	distCalculator = new ignoreGaps();					}
                else if (Estimators[0] == "eachgap"){	distCalculator = new eachGapIgnoreTermGapDist();	}
                else if (Estimators[0] == "onegap")	{	distCalculator = new oneGapIgnoreTermGapDist();		}
            }
        }

		//column file
		ofstream outFile(dFileName.c_str(), ios::trunc);
		outFile.setf(ios::fixed, ios::showpoint);
		outFile << setprecision(4);
		
		if(startLine == 0){	outFile << alignDB.getNumSeqs() << endl;	}
		
		for(int i=startLine;i<endLine;i++){
				
			string name = alignDB.get(i).getName();
			//pad with spaces to make compatible
			if (name.length() < 10) { while (name.length() < 10) {  name += " ";  } }
				
			outFile << name << '\t';	
			
			for(int j=0;j<alignDB.getNumSeqs();j++){
				
				if (m->control_pressed) { outFile.close(); delete alignment; delete distCalculator; return 0;  }
				
				if (alignDB.get(i).getUnaligned().length() > alignment->getnRows()) {
					alignment->resize(alignDB.get(i).getUnaligned().length()+1);
				}
				
				if (alignDB.get(j).getUnaligned().length() > alignment->getnRows()) {
					alignment->resize(alignDB.get(j).getUnaligned().length()+1);
				}
				
				Sequence seqI(alignDB.get(i).getName(), alignDB.get(i).getAligned());
				Sequence seqJ(alignDB.get(j).getName(), alignDB.get(j).getAligned());
				
				alignment->align(seqI.getUnaligned(), seqJ.getUnaligned());
				seqI.setAligned(alignment->getSeqAAln());
				seqJ.setAligned(alignment->getSeqBAln());
				
				distCalculator->calcDist(seqI, seqJ);
				double dist = distCalculator->getDist();
								
				outFile << dist << '\t';
                
                if (m->debug) { m->mothurOut("[DEBUG]: " + seqI.getName() + '\t' +  alignment->getSeqAAln() + '\n' + seqJ.getName() + alignment->getSeqBAln() + '\n' + "distance = " + toString(dist) + "\n"); }
			}
			
			outFile << endl; 
			
			if(i % 100 == 0){
				m->mothurOutJustToScreen(toString(i) + "\t" + toString(time(NULL) - startTime)+"\n"); 
			}
			
		}
		m->mothurOutJustToScreen(toString(endLine-1) + "\t" + toString(time(NULL) - startTime)+"\n");
		
		outFile.close();
        delete alignment;
        delete distCalculator;
		
		return 1;
	}
	catch(exception& e) {
		m->errorOut(e, "PairwiseSeqsCommand", "driver");
		exit(1);
	}
}
#ifdef USE_MPI
/**************************************************************************************************/
/////// need to fix to work with calcs and sequencedb
int PairwiseSeqsCommand::driverMPI(int startLine, int endLine, MPI_File& outMPI, float cutoff){
	try {
		MPI_Status status;
		int startTime = time(NULL);
        
        Alignment* alignment;
        if(align == "gotoh")			{	alignment = new GotohOverlap(gapOpen, gapExtend, match, misMatch, longestBase);			}
		else if(align == "needleman")	{	alignment = new NeedlemanOverlap(gapOpen, match, misMatch, longestBase);				}
		else if(align == "blast")		{	alignment = new BlastAlignment(gapOpen, gapExtend, match, misMatch);		}
		else if(align == "noalign")		{	alignment = new NoAlign();													}
		else {
			m->mothurOut(align + " is not a valid alignment option. I will run the command using needleman.");
			m->mothurOutEndLine();
			alignment = new NeedlemanOverlap(gapOpen, match, misMatch, longestBase);
		}
		
        ValidCalculators validCalculator;
        Dist* distCalculator;
        if (countends) {
            if (validCalculator.isValidCalculator("distance", Estimators[0]) == true) { 
                if (Estimators[0] == "nogaps")			{	distCalculator = new ignoreGaps();	}
                else if (Estimators[0] == "eachgap")	{	distCalculator = new eachGapDist();	}
                else if (Estimators[0] == "onegap")		{	distCalculator = new oneGapDist();	}
            }
        }else {
            if (validCalculator.isValidCalculator("distance", Estimators[0]) == true) { 
                if (Estimators[0] == "nogaps")		{	distCalculator = new ignoreGaps();					}
                else if (Estimators[0] == "eachgap"){	distCalculator = new eachGapIgnoreTermGapDist();	}
                else if (Estimators[0] == "onegap")	{	distCalculator = new oneGapIgnoreTermGapDist();		}
            }
        }

		string outputString = "";
		
		for(int i=startLine;i<endLine;i++){
	
			for(int j=0;j<i;j++){
				
				if (m->control_pressed) { delete alignment; delete distCalculator; return 0;  }
				
				if (alignDB.get(i).getUnaligned().length() > alignment->getnRows()) {
					alignment->resize(alignDB.get(i).getUnaligned().length()+1);
				}
				
				if (alignDB.get(j).getUnaligned().length() > alignment->getnRows()) {
					alignment->resize(alignDB.get(j).getUnaligned().length()+1);
				}
				
				Sequence seqI(alignDB.get(i).getName(), alignDB.get(i).getAligned());
				Sequence seqJ(alignDB.get(j).getName(), alignDB.get(j).getAligned());
				
				alignment->align(seqI.getUnaligned(), seqJ.getUnaligned());
				seqI.setAligned(alignment->getSeqAAln());
				seqJ.setAligned(alignment->getSeqBAln());
				
				distCalculator->calcDist(seqI, seqJ);
				double dist = distCalculator->getDist();
                
                if (m->debug) { cout << ("[DEBUG]: " + seqI.getName() + '\t' +  alignment->getSeqAAln() + '\n' + seqJ.getName() + alignment->getSeqBAln() + '\n' + "distance = " + toString(dist) + "\n"); }
				
				if(dist <= cutoff){
					 outputString += (alignDB.get(i).getName() + ' ' + alignDB.get(j).getName() + ' ' + toString(dist) + '\n'); 
				}
			}
			
			if(i % 100 == 0){
				//m->mothurOut(toString(i) + "\t" + toString(time(NULL) - startTime)); m->mothurOutEndLine();
				cout << i << '\t' << (time(NULL) - startTime) << endl;
			}
			
			 
			//send results to parent
			int length = outputString.length();

			char* buf = new char[length];
			memcpy(buf, outputString.c_str(), length);
			
			MPI_File_write_shared(outMPI, buf, length, MPI_CHAR, &status);
			outputString = "";
			delete buf;
			
		}
		delete alignment;
        delete distCalculator;
		return 1;
	}
	catch(exception& e) {
		m->errorOut(e, "PairwiseSeqsCommand", "driverMPI");
		exit(1);
	}
}
/**************************************************************************************************/
/////// need to fix to work with calcs and sequencedb
int PairwiseSeqsCommand::driverMPI(int startLine, int endLine, string file, unsigned long long& size){
	try {
		MPI_Status status;
		
		MPI_File outMPI;
		int amode=MPI_MODE_CREATE|MPI_MODE_WRONLY; 

		char filename[1024];
		strcpy(filename, file.c_str());

		MPI_File_open(MPI_COMM_SELF, filename, amode, MPI_INFO_NULL, &outMPI);

		Alignment* alignment;
        if(align == "gotoh")			{	alignment = new GotohOverlap(gapOpen, gapExtend, match, misMatch, longestBase);			}
		else if(align == "needleman")	{	alignment = new NeedlemanOverlap(gapOpen, match, misMatch, longestBase);				}
		else if(align == "blast")		{	alignment = new BlastAlignment(gapOpen, gapExtend, match, misMatch);		}
		else if(align == "noalign")		{	alignment = new NoAlign();													}
		else {
			m->mothurOut(align + " is not a valid alignment option. I will run the command using needleman.");
			m->mothurOutEndLine();
			alignment = new NeedlemanOverlap(gapOpen, match, misMatch, longestBase);
		}
        
        ValidCalculators validCalculator;
        Dist* distCalculator;
        if (countends) {
            if (validCalculator.isValidCalculator("distance", Estimators[0]) == true) { 
                if (Estimators[0] == "nogaps")			{	distCalculator = new ignoreGaps();	}
                else if (Estimators[0] == "eachgap")	{	distCalculator = new eachGapDist();	}
                else if (Estimators[0] == "onegap")		{	distCalculator = new oneGapDist();	}
            }
        }else {
            if (validCalculator.isValidCalculator("distance", Estimators[0]) == true) { 
                if (Estimators[0] == "nogaps")		{	distCalculator = new ignoreGaps();					}
                else if (Estimators[0] == "eachgap"){	distCalculator = new eachGapIgnoreTermGapDist();	}
                else if (Estimators[0] == "onegap")	{	distCalculator = new oneGapIgnoreTermGapDist();		}
            }
        }

		
		string outputString = "";
		size = 0;
		
		if(startLine == 0){	outputString += toString(alignDB.getNumSeqs()) + "\n";	}
		
		for(int i=startLine;i<endLine;i++){
				
			string name = alignDB.get(i).getName();
			if (name.length() < 10) { //pad with spaces to make compatible
				while (name.length() < 10) {  name += " ";  }
			}
			outputString += name + "\t";	
			
			for(int j=0;j<i;j++){
				
				if (m->control_pressed) { delete alignment; delete distCalculator; return 0;  }
				
				if (alignDB.get(i).getUnaligned().length() > alignment->getnRows()) {
					alignment->resize(alignDB.get(i).getUnaligned().length()+1);
				}
				
				if (alignDB.get(j).getUnaligned().length() > alignment->getnRows()) {
					alignment->resize(alignDB.get(j).getUnaligned().length()+1);
				}
				
				Sequence seqI(alignDB.get(i).getName(), alignDB.get(i).getAligned());
				Sequence seqJ(alignDB.get(j).getName(), alignDB.get(j).getAligned());
				
				alignment->align(seqI.getUnaligned(), seqJ.getUnaligned());
				seqI.setAligned(alignment->getSeqAAln());
				seqJ.setAligned(alignment->getSeqBAln());
				
				distCalculator->calcDist(seqI, seqJ);
				double dist = distCalculator->getDist();
                
                if (m->debug) { cout << ("[DEBUG]: " + seqI.getName() + '\t' +  alignment->getSeqAAln() + '\n' + seqJ.getName() + alignment->getSeqBAln() + '\n' + "distance = " + toString(dist) + "\n"); }
				
				outputString += toString(dist) + "\t"; 
			}
			
			outputString += "\n"; 
			
			//send results to parent
			int length = outputString.length();
			char* buf = new char[length];
			memcpy(buf, outputString.c_str(), length);
			
			MPI_File_write(outMPI, buf, length, MPI_CHAR, &status);
			size += outputString.length();
			outputString = "";
			delete buf;
		}
		
		MPI_File_close(&outMPI);
        delete alignment;
        delete distCalculator;
		
		return 1;
	}
	catch(exception& e) {
		m->errorOut(e, "PairwiseSeqsCommand", "driverMPI");
		exit(1);
	}
}
/**************************************************************************************************/
/////// need to fix to work with calcs and sequencedb
int PairwiseSeqsCommand::driverMPI(int startLine, int endLine, string file, unsigned long long& size, string square){
	try {
		MPI_Status status;
		
		MPI_File outMPI;
		int amode=MPI_MODE_CREATE|MPI_MODE_WRONLY; 

		char filename[1024];
		strcpy(filename, file.c_str());

		MPI_File_open(MPI_COMM_SELF, filename, amode, MPI_INFO_NULL, &outMPI);
		
		Alignment* alignment;
        if(align == "gotoh")			{	alignment = new GotohOverlap(gapOpen, gapExtend, match, misMatch, longestBase);			}
		else if(align == "needleman")	{	alignment = new NeedlemanOverlap(gapOpen, match, misMatch, longestBase);				}
		else if(align == "blast")		{	alignment = new BlastAlignment(gapOpen, gapExtend, match, misMatch);		}
		else if(align == "noalign")		{	alignment = new NoAlign();													}
		else {
			m->mothurOut(align + " is not a valid alignment option. I will run the command using needleman.");
			m->mothurOutEndLine();
			alignment = new NeedlemanOverlap(gapOpen, match, misMatch, longestBase);
		}
		
        ValidCalculators validCalculator;
        Dist* distCalculator;
        if (countends) {
            if (validCalculator.isValidCalculator("distance", Estimators[0]) == true) { 
                if (Estimators[0] == "nogaps")			{	distCalculator = new ignoreGaps();	}
                else if (Estimators[0] == "eachgap")	{	distCalculator = new eachGapDist();	}
                else if (Estimators[0] == "onegap")		{	distCalculator = new oneGapDist();	}
            }
        }else {
            if (validCalculator.isValidCalculator("distance", Estimators[0]) == true) { 
                if (Estimators[0] == "nogaps")		{	distCalculator = new ignoreGaps();					}
                else if (Estimators[0] == "eachgap"){	distCalculator = new eachGapIgnoreTermGapDist();	}
                else if (Estimators[0] == "onegap")	{	distCalculator = new oneGapIgnoreTermGapDist();		}
            }
        }
        
		string outputString = "";
		size = 0;
		
		if(startLine == 0){	outputString += toString(alignDB.getNumSeqs()) + "\n";	}
		
		for(int i=startLine;i<endLine;i++){
				
			string name = alignDB.get(i).getName();
			if (name.length() < 10) { //pad with spaces to make compatible
				while (name.length() < 10) {  name += " ";  }
			}
			outputString += name + "\t";	
			
			for(int j=0;j<alignDB.getNumSeqs();j++){
				
				if (m->control_pressed) {  delete alignment; return 0;  }
				
				if (alignDB.get(i).getUnaligned().length() > alignment->getnRows()) {
					alignment->resize(alignDB.get(i).getUnaligned().length()+1);
				}
				
				if (alignDB.get(j).getUnaligned().length() > alignment->getnRows()) {
					alignment->resize(alignDB.get(j).getUnaligned().length()+1);
				}
				
				Sequence seqI(alignDB.get(i).getName(), alignDB.get(i).getAligned());
				Sequence seqJ(alignDB.get(j).getName(), alignDB.get(j).getAligned());
				
				alignment->align(seqI.getUnaligned(), seqJ.getUnaligned());
				seqI.setAligned(alignment->getSeqAAln());
				seqJ.setAligned(alignment->getSeqBAln());
				
				distCalculator->calcDist(seqI, seqJ);
				double dist = distCalculator->getDist();
				
				outputString += toString(dist) + "\t";
                
                if (m->debug) { cout << ("[DEBUG]: " + seqI.getName() + '\t' +  alignment->getSeqAAln() + '\n' + seqJ.getName() + alignment->getSeqBAln() + '\n' + "distance = " + toString(dist) + "\n"); }
			}
			
			outputString += "\n"; 

			//send results to parent
			int length = outputString.length();
			char* buf = new char[length];
			memcpy(buf, outputString.c_str(), length);
			
			MPI_File_write(outMPI, buf, length, MPI_CHAR, &status);
			size += outputString.length();
			outputString = "";
			delete buf;
		}
		
		MPI_File_close(&outMPI);
		
        delete alignment;
		return 1;
	}
	catch(exception& e) {
		m->errorOut(e, "PairwiseSeqsCommand", "driverMPI");
		exit(1);
	}
}
#endif
/**************************************************************************************************/

