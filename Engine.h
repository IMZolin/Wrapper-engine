#pragma once
#ifndef WRAPPER_ENGINE_ENGINE_H
#define WRAPPER_ENGINE_ENGINE_H
#include "Wrapper.h"
class Engine{
public:
    Engine() = default;
    Engine(Engine const&) = delete;
    Engine& operator =(Engine const&) = delete;
    Engine(Engine&&) = default;
    Engine& operator =(Engine&&) = default;
    ~Engine() = default;
    template<typename T>
    void register_command(Wrapper<T>* wrapper, std::string const& command)
    {
        if (commands.find(command) != commands.end())
        {
            std::string error = "command " + command + " already registered";
            throw std::runtime_error(error.c_str());
        }
        commands.insert({ command, wrapper });
    }
    template<typename T>
    T execute(const std::string &command, std::map<std::string, T> const & args) {
        auto it = commands.find(command);
        if (it == commands.end())
        {
            std::string error = "Command " + command + " has not been registered";
            throw std::runtime_error(error.c_str());
        }

        Wrapper<T>* wrapper = static_cast<Wrapper<T>*>(it->second);
        return wrapper->execute(args);
        /*Wrapper<T>* wrapper = static_cast<Wrapper<T>*>(it->second);
        return wrapper->execute(args);*/
    }
private:
    std::map<std::string, void*> commands;
};
#endif //WRAPPER_ENGINE_ENGINE_H