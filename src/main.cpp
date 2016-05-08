
#include "CspConstrains.h"
#include "CspState.h"
#include "CspDomain.h"

#include "BacktrackingSearch.h"

#include <iostream>
#include <cstdlib>

template <class IdType, class DataType>
void BuildNQueensCsp(CspState<IdType, DataType>& cspState,
                     CspConstrains<IdType, DataType>& cspConstrains,
                     const size_t& size)
{
    // Create domain for all variables.
    std::vector<DataType> domainValues(size);
    std::iota(std::begin(domainValues), std::end(domainValues), 0);
    CspDomain<DataType> cspDomain(domainValues);

    // Create variables of the CSP problem.
    for (IdType i = 0; i < size; i++)
    {
        cspState.addVar(i, cspDomain);
    }

    // Create constrains.
    for (IdType i = 0; i < size - 1; i++)
    {
        for (IdType j = i + 1; j < size; j++)
        {
            // Diagonal constrain.
            auto constrain = CspBinaryConstrain<IdType, DataType>(i, j,
                    [i, j](const CspState<IdType, DataType>& state)->bool
                    {
                        auto value1 = state.getValue(i);
                        auto value2 = state.getValue(j);

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
                        bool diagonal = (abs(value1 - value2) != abs(i - j));

                        // If both values are the same, they are in the same row and therefore
                        // they are threathening each other.
                        bool vertical = (value1 != value2);

                        return diagonal && vertical;
                    });
            cspConstrains.addBinaryConstrain(constrain);
        }
    }
}

int main(int argc, char *argv[])
{
    const size_t size = 5;
    CspConstrains<size_t, size_t> constrains;
    CspState<size_t, size_t> state;
    BuildNQueensCsp(state, constrains, size);

    auto solution = BacktrackingSearch(state, constrains);

    for (auto pos : solution)
    {
        size_t x = pos.first;
        size_t y = pos.second;
        std::cout << "x=" << x << ", y=" << y << std::endl;
    }
    
//    std::cout << "a" << std::endl;
//
//    std::cout << "consistent " << constrains.isConsistent(state) << std::endl;
//    std::cout << "isComplete " << constrains.isComplete(state) << std::endl;
//    std::cout << "unassigned var: " << state.getIdUnassignedVar() << std::endl;
//    state.setVar(0,2);
//    std::cout << "unassigned var: " << state.getIdUnassignedVar() << std::endl;
//    state.setVar(1,0);
//    std::cout << "unassigned var: " << state.getIdUnassignedVar() << std::endl;
//    state.setVar(2,3);
//    std::cout << "unassigned var: " << state.getIdUnassignedVar() << std::endl;
//    state.setVar(3,1);
//    std::cout << "unassigned var: " << state.getIdUnassignedVar() << std::endl;
//    state.setVar(4,4);
//    std::cout << "unassigned var: " << state.getIdUnassignedVar() << std::endl;
//    std::cout << "consistent " << constrains.isConsistent(state) << std::endl;
//    std::cout << "isComplete " << constrains.isComplete(state) << std::endl;




}

