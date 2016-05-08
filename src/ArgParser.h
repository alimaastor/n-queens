/* This simple arg parser has been copied from:
 * http://stackoverflow.com/a/868894/2235928
 */

#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <string>

char* getCmdOption(char** begin, char** end, const std::string& option);

bool cmdOptionExists(char** begin, char** end, const std::string& option);

#endif /* ARG_PARSER_H */

