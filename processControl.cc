/*
 * Filename      processControl.cc
 * Date          4/19/2020
 * Author        Noah Sims
 * Email         ngs170000@utdallas.edu
 * Course        CS 3377.501 Spring 2020
 * Version       1.0
 * Copyright 2020, All Rights Reserved
 *
 * Description
 *
 *     This program provides the summonDaemon() and checkPid() functions for program5, which fork the program so it can run as a daemon, and checks if a daemon process
 *     is already running
 */

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

// forks the program to run in the background as a daemon
int summonDaemon()
{
  pid_t forkValue;
  forkValue = fork();

  if(forkValue == -1)
  {
    perror("There was an error in the fork. No child was created.");
    return -1;
  }
  else if(forkValue == 0)
  {
    cout << "Daemon active" << endl;
    return 1;
  }
  else
  {
    cout << "Daemon program created with pid: " << forkValue << endl;
    return 0;
  }
}

// checks if the .pid file already exists, preventing the program from running two versions of itself at the same time
int checkPid()
{
  struct stat buffer;
  int status;

  status = stat("/home/011/n/ng/ngs170000/CS3377/assignments/hw5/cs3377dirmond.pid", &buffer);
  if(status == 0)
  {
    cout << "Error: cs3377dirmond.pid already exists. Exiting program" << endl;
    return -1;
  }

  ofstream pidFile;
  pidFile.open("cs3377dirmond.pid", ios::out);

  pid_t mypid = getpid();
  pidFile << "PID = " << mypid << endl;

  pidFile.close();

  return 1;
}
