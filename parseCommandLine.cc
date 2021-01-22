/*
 * Filename      parseCommandLine.cc
 * Date          4/19/2020
 * Author        Noah Sims
 * Email         ngs170000@utdallas.edu
 * Course        CS 3377.501 Spring 2020
 * Version       1.0
 * Copyright 2020, All Rights Reserved
 *
 * Description
 *
 *     This program utilizes tclap to parse the command line for program5
 */

#include <iostream>
#include <map>
#include <tclap/CmdLine.h>
#include "prog5Header.h"

using namespace std;

void parseCommandLine(std::map<int, std::string> &optionMap, int argc, char** argv)
{
  TCLAP::CmdLine cmd("cs3377dirmond Directory Monitor Daemon.", ' ', "1.0");

  TCLAP::SwitchArg daemonSwitch("d", "daemon", "Run in daemon mode (forks to run as daemon).", cmd, false);

  TCLAP::UnlabeledValueArg<std::string> configFileArg("configFile", "The name of the configuration file. Defaults to cs3377dirmond.conf.", false, "cs3377dirmond.conf", "config filename", false);
  cmd.add(configFileArg);

  cmd.parse(argc, argv);
  if(daemonSwitch.getValue())
    optionMap[DAEMON_MODE] = "true";
  else
    optionMap[DAEMON_MODE] = "false";

  optionMap[CONFIG_FILE] = configFileArg.getValue();
}
