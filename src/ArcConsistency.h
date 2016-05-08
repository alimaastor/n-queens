
#ifndef ARC_CONSISTENCY_H
#define ARC_CONSISTENCY_H

template <class IdType, class DataType>
CspState<IdType, DataType> ArcConsistency(const CspState<IdType, DataType>& state,
                                          const CspConstrains<IdType, DataType>& constrains)
{
    auto arcDeque = constrains.getConstrainsDeque();

    while (!arcDeque.empty())
    {
        auto arc = arcDeque.front();
        arcDeque.pop_front();

        IdType idTail = arc.first.first;
        IdType idHead = arc.first.second;
        auto constrain = arc.second;

        if (removeInconsistentValues(idTail, idHead, state, constrain))
        {
            auto arcs = constrains.getArcsForHead(idTail);
            for (const auto& arc : arcs)
            {
                arcDeque.push_back(arc);
            }
        }
    }
}

template <class IdType, class DataType>
bool RemoveInconsistentValues(const IdType& idTail, const IdType& idHead,
                              CspState<IdType, DataType>& state,
                              const CspConstrain<IdType, DataType>& constrain)
{
    bool removed = false;
    
    auto tailDomain = state.getVarDomain(idTail);
    auto headDomain = state.getVarDomain(idHead);

    for (const auto& tailValue : tailDomain.getValues())
    {
        for (const auto& headValue : headDomain.getValues())
        {
            auto newState = state;
            newState.setVar(idTail, tailValue);
            newstate.setVar(idHead, headValue);
 
        }
    }

    return removed;
}

#endif /* ARC_CONSISTENCY_H */

