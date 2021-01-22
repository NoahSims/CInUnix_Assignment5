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
 *     This program utilizes the tclap and rudeconfig libraries to create a daemon process that watches a directory, specified in the .conf file, and creates a backup any time
 *     any time a file is changed.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <map>
#include <sys/inotify.h>
#include <limits.h>              // needed for PATH_MAX
#include <stdlib.h>              // needed for malloc
#include <unistd.h>              // needed for read
#include <sys/types.h>           // needed for mkdir
#include <sys/stat.h>            // needed for mkdir
#include "prog5Header.h"

using namespace std;

map<int, string> optionMap;

int main(int argc, char** argv)
{
  parseCommandLine(optionMap, argc, argv);

  // cout << "daemon = " << optionMap[DAEMON_MODE] << "; Config file = " << optionMap[CONFIG_FILE] << endl;

  int rudeValue = parseConfigFile(optionMap);
  if(rudeValue != 0)
  {
    cout << "Error code: " << rudeValue << endl;
    return 1;
  }

  if(optionMap[DAEMON_MODE] == "true")
  {
    if(summonDaemon() != 1)
      return 0;
  }

  if(checkPid() != 1)
    return -1;
  
  signalHandler();

  //create .versions
  string versionsPath = optionMap[WATCHDIR] + "/.versions";
  int status = mkdir(versionsPath.c_str(), S_IRWXU | S_IXGRP | S_IXOTH);
  FILE* fileCopier;

  //inotify stuff
  const int EVENT_SIZE = sizeof(struct inotify_event);
  size_t bufsiz = EVENT_SIZE + PATH_MAX + 1;
  struct inotify_event* event = (struct inotify_event*) malloc(bufsiz);

  int fd = inotify_init();
  if(fd < 0)
  {
    perror("Error: inotify_init failed\n");
    return -1;
  }

  int wd = inotify_add_watch(fd, optionMap[WATCHDIR].c_str(), IN_MODIFY);

  while(1)
  {
    int length = read(fd, event, bufsiz);

    if(length > 0)
    {
      if(event->mask & IN_MODIFY)
      {
	// log message
	logMsg(optionMap, event->name);

	//cp <source> <destination>
	string cpCmd = "cp " + optionMap[WATCHDIR] + "/" + event->name + " " + optionMap[WATCHDIR] + "/.versions/" + event->name + timeFileExtension();
	fileCopier = popen(cpCmd.c_str(), "r");
	pclose(fileCopier);

	// EXTRA CREDIT
	// check num versions
        versionControl(optionMap, event->name);
      }
    }
  }

  inotify_rm_watch(fd, wd);
  close(fd);
}
