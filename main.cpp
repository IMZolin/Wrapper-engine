#include <iostream>
#include "Wrapper.h"
#include "Engine.h"

class Subject
{
public:
    template<typename T>
    T f3(T a, T b)
    {
        return a + b;
    }
};
int main() {
    try
    {
        Subject subj;
        Wrapper<int> wrapper1(&subj, &Subject::f3<int>, {{"arg1", 0},{"arg2", 0}});
        Engine engine;
        engine.register_command<int>(&wrapper1, "command1");
        std::cout << "4 + 5 = " << engine.execute<int>("command1", {{"arg1", 4}, {"arg2", 5}}) << std::endl;

        Wrapper<double> wrapper2(&subj, &Subject::f3<double>, { {"arg1", 0.0}, {"arg2", 0.0} });
        engine.register_command<double>(&wrapper2, "command2");
        std::cout << "16.5 + 0.5 = " << engine.execute<double>("command2", { {"arg1", 16.5}, {"arg2", 0.5} }) << std::endl;
    }
    catch (std::exception& error)
    {
        std::cout << error.what() << std::endl;
    }
    return 0;
}
