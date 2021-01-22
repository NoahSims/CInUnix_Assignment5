/*
 * Filename      signalHandling.cc
 * Date          4/19/2020
 * Author        Noah Sims
 * Email         ngs170000@utdallas.edu
 * Course        CS 3377.501 Spring 2020
 * Version       1.0
 * Copyright 2020, All Rights Reserved
 *
 * Description
 *
 *     This program provides the signal handling functions for program5
 */

#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include "prog5Header.h"

using namespace std;

extern map<int, string> optionMap;

void exitHandler(int signum)
{
  remove("cs3377dirmond.pid");
  cout << "Exiting program" << endl;
  exit(EXIT_SUCCESS);
}

void reconfigure(int signum)
{
  map<int, string> remap;
  remap[CONFIG_FILE] = optionMap[CONFIG_FILE];

  int rudeValue = parseConfigFile(remap);
  if(rudeValue != 0)
  {
    cout << "Error code: " << rudeValue << endl;
    exitHandler(2);
  }

  if(optionMap[PASSWORD] != remap[PASSWORD] || optionMap[WATCHDIR] != remap[WATCHDIR])
  {
    perror("Error: variables Password and WatchDir can not be changed in the conf file during runtime.\n");
    exitHandler(2);
  }
  else
  {
    optionMap[VERBOSE] = remap[VERBOSE];
    optionMap[LOG_FILE] = remap[LOG_FILE];
    optionMap[NUM_VERSIONS] = remap[NUM_VERSIONS];
  }
}

void signalHandler()
{
  struct sigaction exitAction;
  exitAction.sa_handler = exitHandler;
  sigemptyset(&exitAction.sa_mask);
  exitAction.sa_flags = SA_RESTART;
  sigaction(SIGINT, &exitAction, 0);
  sigaction(SIGTERM, &exitAction, 0);

  struct sigaction reconfig;
  reconfig.sa_handler = reconfigure;
  sigemptyset(&reconfig.sa_mask);
  reconfig.sa_flags = SA_RESTART;
  sigaction(SIGHUP, &reconfig, 0);
}
