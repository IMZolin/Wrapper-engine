#include <iostream>
#include "Wrapper.h"
class Subject
{
public:
    int f3(int a, int b)
    {
        return a - b;
    }
};
int main() {
    try
    {
        Subject subj;
        Wrapper wrapper(&subj, &Subject::f3, {{"arg1", 0},
                                              {"arg2", 0}});
    }
    catch (std::exception& er)
    {
        std::cout << er.what() << std::endl;
    }
    return 0;
}
