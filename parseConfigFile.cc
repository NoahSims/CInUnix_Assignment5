/*
 * Filename      parseConfigFile.cc
 * Date          4/19/2020
 * Author        Noah Sims
 * Email         ngs170000@utdallas.edu
 * Course        CS 3377.501 Spring 2020
 * Version       1.0
 * Copyright 2020, All Rights Reserved
 *
 * Description
 *
 *     This program utilizes the rudeconfig library to parse the config file for program5
 */

#include <iostream>
#include <string>
#include <map>
#include <rude/config.h>
#include "prog5Header.h"

using namespace std;

int parseConfigFile(std::map<int, std::string> &optionMap)
{
  rude::Config config;

  string configFile = optionMap[CONFIG_FILE];

  if(config.load(configFile.c_str()))
  {
    config.setSection("Parameters");

    string param = "Verbose";
    if(config.exists(param.c_str()))
    {
      optionMap[VERBOSE] = config.getStringValue(param.c_str());
    }
    else
    {
      cout << "Error, config file missing parameter: " << param << endl;
      return 2;
    }

    param = "LogFile";
    if(config.exists(param.c_str()))
    {
      optionMap[LOG_FILE] = config.getStringValue(param.c_str());
    }
    else
    {
      cout << "Error, config file missing parameter: " << param << endl;
      return 2;
    }

    param = "Password";
    if(config.exists(param.c_str()))
    {
      optionMap[PASSWORD] = config.getStringValue(param.c_str());
    }
    else
    {
      cout << "Error, config file missing parameter: " << param << endl;
      return 2;
    }

    param = "NumVersions";
    if(config.exists(param.c_str()))
    {
      optionMap[NUM_VERSIONS] = config.getStringValue(param.c_str());
    }
    else
    {
      cout << "Error, config file missing parameter: " << param << endl;
      return 2;
    }

    param = "WatchDir";
    if(config.exists(param.c_str()))
    {
      optionMap[WATCHDIR] = config.getStringValue(param.c_str());
    }
    else
      {
	cout << "Error, config file missing parameter: " << param << endl;
	return 2;
      }

    return 0;

  }
  else
  {
    cout << "Error opening config file: " << config.getError() << endl;
    return 1;
  }
}
