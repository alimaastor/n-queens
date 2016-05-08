
#include "Csp.h"

#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
    const int size = 5;
    Csp<int, int> csp;
    for (int i = 0; i < size; i++)
    {
        csp.addVar(i);
    }

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            auto constrain = CspBinaryConstrain<int, int>(i, j,
                    [i, j](const CspVarMap<int, int>& all_vars)->bool
                    {
                        auto var1 = all_vars.find(i)->second;
                        auto var2 = all_vars.find(j)->second;

                        // A constrain cannot be violated if the variables
                        // have not been set yet.
                        if (!var1.isAssigned() || !var2.isAssigned())
                        {
                            return true;
                        }

                        // We check that both values (positions of the queen)
                        // are not in the same diagonal.
                        //
                        //      1  2  3  4
                        //     -------------
                        // Q1  |  |QQ|  |  |
                        //     -------------
                        // Q2  |  |  |  |  |
                        //     -------------
                        // Q3  |  |  |  |QQ|
                        //     -------------
                        // Q4  |  |  |  |  |
                        //     -------------
                        //
                        // |Q1 - Q3| = |1 - 3| = 2, so if the difference of the values
                        // of those rows are equal to 2, the queens are threathening
                        // each other. In this case:
                        // |2 - 4| = 2 -> constrain violated.
                        if (abs(var1.getValue() - var2.getValue()) == abs(i - j))
                        {
                            return false;
                        }

                        return true;
                    });
            csp.addBinaryConstrain(constrain);
        }
    }

    std::cout << "a" << std::endl;

    std::cout << "consistent " << csp.isConsistent() << std::endl;
    std::cout << "isComplete " << csp.isComplete() << std::endl;
    std::cout << "unassigned var: " << csp.getUnassignedVar() << std::endl;
    csp.setVar(0,2);
    std::cout << "unassigned var: " << csp.getUnassignedVar() << std::endl;
    csp.setVar(1,0);
    std::cout << "unassigned var: " << csp.getUnassignedVar() << std::endl;
    csp.setVar(2,3);
    std::cout << "unassigned var: " << csp.getUnassignedVar() << std::endl;
    csp.setVar(3,1);
    std::cout << "unassigned var: " << csp.getUnassignedVar() << std::endl;
    csp.setVar(4,4);
    std::cout << "unassigned var: " << csp.getUnassignedVar() << std::endl;
    std::cout << "consistent " << csp.isConsistent() << std::endl;
    std::cout << "isComplete " << csp.isComplete() << std::endl;




}

