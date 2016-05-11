
#ifndef BACKTRACKING_SEARCH_H
#define BACKTRACKING_SEARCH_H

#include "CspState.h"
#include "CspConstrains.h"
#include "ArcConsistency.h"

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
//    auto state = unfilteredState;
//    state = ArcConsistency(state, constrains);
//
//    if (!constrains.isConsistent(state) || constrains.isComplete(state))
//    {
//        return state;
//    }

    IdType varId = state.getIdUnassignedVar();
    //IdType varId = state.getIdVarMaxRemainingValues();
    //IdType varId = state.getIdVarMinRemainingValues();
    for (const auto& value : state.getVarDomain(varId).getValues())
    {
        auto newState = state;
        newState.setVar(varId,  value);
        if (constrains.isConsistent(newState))
        {
            auto solution = RecursiveBacktracking(newState, constrains);
            if (constrains.isComplete(solution))
            {
                return solution;
            }
        }
    }

    return state;
}

#endif /*  BACKTRACKING_SEARCH_H */

