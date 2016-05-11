
#ifndef ARC_CONSISTENCY_H
#define ARC_CONSISTENCY_H

template <class IdType, class DataType>
CspState<IdType, DataType> ArcConsistency(CspState<IdType, DataType>& state,
                                          const CspConstrains<IdType, DataType>& constrains)
{
    auto arcQueue = constrains.getArcQueue();

    while (!arcQueue.isEmpty())
    {
        auto arc = arcQueue.popNext();

        IdType idTail = arc.first.first;
        IdType idHead = arc.first.second;

        if (state.isVarAssigned(idTail) && state.isVarAssigned(idHead))
        {
            continue;
        }

        auto constrain = arc.second;

        if (RemoveInconsistentValues(idTail, idHead, state, constrain))
        {
            auto arcs = constrains.getArcsForHead(idTail);
            for (const auto& arc : arcs)
            {
                arcQueue.maybeAddArc(arc);
            }
        }
    }

    return state;
}

template <class IdType, class DataType>
bool RemoveInconsistentValues(const IdType& idTail, const IdType& idHead,
                              CspState<IdType, DataType>& state,
                              const CspBinaryConstrain<IdType, DataType>& constrain)
{
    bool removed = false;
    
    auto tailDomain = state.getVarDomain(idTail);
    auto headDomain = state.getVarDomain(idHead);

    for (const auto& tailValue : tailDomain.getValues())
    {
        bool removeValueFromTail = true;
        for (const auto& headValue : headDomain.getValues())
        {
            auto newState = state;

            newState.setVar(idTail, tailValue);
            newState.setVar(idHead, headValue);

            if (constrain.isValid(newState))
            {
                removeValueFromTail = false;
                break;
            }
        }

        if (removeValueFromTail)
        {
            removed = true;
            state.removeValueFromDomain(idTail, tailValue);
        }
    }

    return removed;
}

#endif /* ARC_CONSISTENCY_H */

