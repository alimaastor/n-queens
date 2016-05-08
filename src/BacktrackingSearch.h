
#ifndef BACKTRACKING_SEARCH_H
#define BACKTRACKING_SEARCH_H

#include "CspState.h"
#include "CspConstrains.h"

#include <vector>

#include <iostream>

template <class IdType, class DataType>
std::vector<std::pair<IdType, DataType>> BacktrackingSearch(const CspState<IdType, DataType>& state, const CspConstrains<IdType, DataType>& constrains)
{
    CspState<IdType, DataType> solution = RecursiveBacktracking(state, constrains);
    return solution.getRaw();
}

template <class IdType, class DataType>
CspState<IdType, DataType>
RecursiveBacktracking(const CspState<IdType, DataType>& state,
                      const CspConstrains<IdType, DataType>& constrains)
{
    if (constrains.isComplete(state))
    {
        return state;
    }

    IdType varId = state.getIdUnassignedVar();
    for (auto value : state.getVarDomain(varId).getValues())
    {
        auto newState = state;
        newState.setVar(varId,  value);
        if (constrains.isConsistent(newState))
        {
            return RecursiveBacktracking(newState, constrains);
        }
    }

    return state;
}

#endif /*  BACKTRACKING_SEARCH_H */

