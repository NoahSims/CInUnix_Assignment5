/*
 * Filename      program5.cc
 * Date          4/19/2020
 * Author        Noah Sims
 * Email         ngs170000@utdallas.edu
 * Course        CS 3377.501 Spring 2020
 * Version       1.0
 * Copyright 2020, All Rights Reserved
 *
 * Description
 *
 *     This program ensures that the number of file backups in .versions is not more than NumVersions
 */

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <map>
#include "prog5Header.h"

using namespace std;

#define BUFFER_SIZE 1024

void versionControl(std::map<int, std::string> &optionMap, string fileName)
{
  stringstream stoi(optionMap[NUM_VERSIONS]);
  int numVersions = 0;
  stoi >> numVersions;

  FILE* dirInfo;
  char tmpBuffer[BUFFER_SIZE];
  char* line_p;
  string lsCmd = "ls " + optionMap[WATCHDIR] + "/.versions";

  dirInfo = popen(lsCmd.c_str(), "r");

  if(!dirInfo)
    return;

  int count = 0;
  string oldestFile = "";

  line_p =  fgets(tmpBuffer, BUFFER_SIZE, dirInfo);
  while(line_p != NULL)
  {
    string currentFile = string(line_p) + "\0";
    if(currentFile.substr(0, fileName.length()) == fileName)
    {
      if(count == 0)
      {
	oldestFile = currentFile.erase(currentFile.find_last_not_of("\n")+1);
      }
      count++;
    }

    line_p = fgets(tmpBuffer, BUFFER_SIZE, dirInfo);
  }

  pclose(dirInfo);

  if(count > numVersions)
  {
    string filePath = optionMap[WATCHDIR] + "/.versions/" + oldestFile;
    //    filePath.erase(filePath.find_last_not_of("\n")+1);

    remove(filePath.c_str());

    string temp = "" + oldestFile;
    removeMsg(optionMap, temp.c_str());
  }
}
