#include "commandinterpreter.h" 
#include <sstream>
#include <iostream>
using namespace std;


CommandInterpreter::CommandInterpreter(map<string, string> cmds): cmds{cmds} {} 


size_t CommandInterpreter::parseTimes(string s){
    stringstream streams;     
    streams << s;
    int num;

    if (streams >> num && num > 0) return num;
    else return 1; 
}

string CommandInterpreter::parseCommands(string s, int t){
    if (t > 1) {
        for (int i = t ; i > 0; i /= 10) s.erase(0,1);
    } else if (t == 1) {
        if (s.at(0) == '1') s.erase(0,1);
    }

    int matchedCommands = 0;
    string mCommand;


    for(auto const& entry : cmds) {
        if (s.length() == 1) {
            if (removeCase(entry.second) == removeCase(s)) {
                matchedCommands += 1;
                mCommand = entry.first;
            }
        } else if ((entry.second).length() >= s.length()) {
            if (removeCase((entry.second).substr(0, s.length())) == removeCase(s)) {

                matchedCommands += 1;
                mCommand = entry.first;
            }
        }
    }
    
    if(matchedCommands == 1) return mCommand;
    else return "invalid";
}

void CommandInterpreter::rename (string old_cmd, string new_cmd){
    
    int already_match = 0;
     for(auto const& entry : cmds) if (entry.second == new_cmd) already_match += 1;

     if (already_match != 1) {
        for(auto & entry : cmds) if (entry.second == old_cmd) entry.second = new_cmd;
    }
}

string CommandInterpreter::removeCase (string cmd) {
    for (unsigned int count = 0; count < cmd.length(); count++) cmd[count] = tolower(cmd[count]);
    return cmd;
}

void CommandInterpreter::printCommands () {
    cout << "List of possible commands:" << endl;
    for(auto const& entry : cmds) 
        cout << "Enter '" << entry.second << "' to use '" << entry.first << "'" << endl;
}


