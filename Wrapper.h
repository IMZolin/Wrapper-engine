#pragma once
#ifndef WRAPPER_ENGINE_WRAPPER_H
#define WRAPPER_ENGINE_WRAPPER_H
#include <vector>
#include <string>
#include <utility>
#include <functional>
#include <map>
#include <stdexcept>

template<typename T>
using argType = std::map<std::string, T>;
template<typename T>
using commandsType = std::function<T(std::vector<T>&)>;

template<typename T>
class Wrapper{
public:
    template<typename Obj, typename... Args>
    Wrapper(Obj *object, T(Obj::*func)(Args...), std::vector<std::pair<std::string, T>> const & args) {
        for (auto& arg : args) {
            _args.insert(arg);
        }
        if (args.size() != _args.size())
        {
            throw std::runtime_error("Params name should be unique");
        }
        _command = [this, object, func](std::vector<T>& argsForFunc) {
            return executeFunc(object, func, argsForFunc, std::make_index_sequence<sizeof...(Args)>{});
        };
    }

    template<typename Obj, typename FuncName, size_t... I>
    T executeFunc(Obj *object, FuncName funcName, std::vector<T>& args, std::index_sequence<I...>) {
        return ((object->*funcName)(args[I]...));
    }

    bool isExist(std::string name) {
        for (auto& arg : _args) {
            std::string n = arg.first;
            if (n.compare(name) == 0)
                return true;
        }
        return false;
    }

    T execute(std::map<std::string, T> const& args) {
        std::vector<T> argsVec;
        for (auto& arg : args) {
            if (!isExist(arg.first))
                throw std::runtime_error("WRAPPER: This command is not init");

            argsVec.push_back(arg.second);
        }
        return _command(argsVec);
    }

    Wrapper(Wrapper const&) = delete;
    Wrapper& operator=(Wrapper const&) = delete;
    Wrapper(Wrapper&&) = default;
    Wrapper& operator=(Wrapper&&) = default;
    ~Wrapper() = default;

private:
    commandsType<T> _command;
    std::map<std::string, T> _args;
};
#endif //WRAPPER_ENGINE_WRAPPER_H