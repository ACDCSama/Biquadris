#ifndef COMMANDINTERPRET_H
#define COMMANDINTERPRET_H
#include <string>
#include <vector>
#include <map>

class CommandInterpreter{
    private:
        std::map<std::string, std::string> cmds;
    
    public:
        CommandInterpreter(std::map<std::string, std::string> cmds); 
        size_t parseTimes(std::string s); 
        std::string parseCommands(std::string s, int t);
        void rename (std::string old_cmd, std::string new_cmd);
        std::string removeCase (std::string cmd);
        void printCommands();
};
#endif




