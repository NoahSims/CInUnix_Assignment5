/*
 * Filename      logFunctions.cc
 * Date          4/19/2020
 * Author        Noah Sims
 * Email         ngs170000@utdallas.edu
 * Course        CS 3377.501 Spring 2020
 * Version       1.0
 * Copyright 2020, All Rights Reserved
 *
 * Description
 *
 *     This program logs the changes noted by the program5 daemon program
 */

#include <iostream>
#include <string>
#include <ctime>
#include <stdio.h>
#include <fstream>
#include <map>
#include "prog5Header.h"

using namespace std;

// converts an int to a string
string iToS(int num)
{
  char buffer[50];
  int n = sprintf(buffer, "%d", num);
  return buffer;
}

// creates the timestamped file extensions
string timeFileExtension()
{
  time_t rawtime;
  struct tm* now;
  time(&rawtime);
  now = localtime(&rawtime);
  //result = .<year>.<month>.<date>-<hour>:<minute>:<seconds>
  string result = "." + iToS(now->tm_year + 1900) + "." + iToS(now->tm_mon + 1) + "." + iToS(now->tm_mday) + "-" + iToS(now->tm_hour) + ":" + iToS(now->tm_min) + ":" + iToS(now->tm_sec);
  return result;
}

// creates the log message for the logMsg function
string createLogMsg(string verbose, string file)
{
  time_t rawtime;
  struct tm* now;
  time(&rawtime);
  now = localtime(&rawtime);

  string result;
  if(verbose == "true")
  {
    result = "The file " + file + " was modified at time: " + iToS(now->tm_year + 1900) + "/" + iToS(now->tm_mon + 1) + "/" + iToS(now->tm_mday) + " - " + iToS(now->tm_hour) + ":" + iToS(now->tm_min) + ". Creating backup.";
  }
  else
  {
    result = file + " was modified.";
  }

  return result;
}

// logs messages for program5
void logMsg(map<int, string> &optionMap, string file)
{
  ofstream logFile;
  logFile.open(optionMap[LOG_FILE].c_str(), ios_base::app);

  logFile << createLogMsg(optionMap[VERBOSE], file) << endl;

  logFile.close();
}

void removeMsg(map<int, string> &optionMap, string file)
{
  ofstream logFile;
  logFile.open(optionMap[LOG_FILE].c_str(), ios_base::app);

  if(optionMap[VERBOSE] == "true")
    logFile << "NumVersions exceded, removing " << file << endl;
  else
    logFile << file << " removed" << endl;

  logFile.close();
}
