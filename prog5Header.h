/*
 * Filename      prog5Header.h
 * Date          4/19/2020
 * Author        Noah Sims
 * Email         ngs170000@utdallas.edu
 * Course        CS 3377.501 Spring 2020
 * Version       1.0
 * Copyright 2020, All Rights Reserved
 *
 * Description
 *
 *     The header file for program5
 */

// constants
enum cmdFlags{DAEMON_MODE, CONFIG_FILE, VERBOSE, LOG_FILE, PASSWORD, NUM_VERSIONS, WATCHDIR};

// function protoypes
void parseCommandLine(std::map<int, std::string> &optionMap, int argc, char** argv);

int parseConfigFile(std::map<int, std::string> &optionMap);

int checkPid(void);
int summonDaemon(void);

void signalHandler(void);

std::string timeFileExtension(void);
void logMsg(std::map<int, std::string> &optionMap, std::string file);
void removeMsg(std::map<int, std::string> &optionMap, std::string file);

void versionControl(std::map<int, std::string> &optionMap, std::string);
