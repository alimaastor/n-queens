
#ifndef CSP_CONSTRAINS_H
#define CSP_CONSTRAINS_H

#include "CspConstrain.h"
#include "CspState.h"
#include "ArcQueue.h"

#include <vector>

template <class IdType, class DataType>
class CspConstrains
{
public:
    CspConstrains()
    {}

    bool isComplete(const CspState<IdType, DataType>& state) const
    {
        return ((state.getNumberOfUnassignedVar() == 0) && (this->isConsistent(state)));
    }

    void addBinaryConstrain(const CspBinaryConstrain<IdType, DataType>& constrain)
    {
        this->m_binaryConstrains.push_back(constrain);
    }

    ArcQueue<IdType, DataType> getArcQueue() const
    {
        ArcQueue<IdType, DataType> arcQueue;

        for (auto constrain : this->m_binaryConstrains)
        {
            arcQueue.maybeAddArc({std::make_pair(constrain.m_idFirst, constrain.m_idSecond), constrain});
            arcQueue.maybeAddArc({std::make_pair(constrain.m_idSecond, constrain.m_idFirst), constrain});
        }

        return arcQueue;
    }

    std::vector<Arc<IdType, DataType>> getArcsForHead(const IdType& idHead) const
    {
        std::vector<Arc<IdType, DataType>> arcs;

        for (auto constrain : this->m_binaryConstrains)
        {
            if (idHead == constrain.m_idFirst)
            {
                arcs.push_back({{constrain.m_idFirst, idHead}, constrain});
            }
            else if (idHead == constrain.m_idSecond)
            {
                arcs.push_back({{constrain.m_idSecond, idHead}, constrain});
            }
        }

        return arcs;
    }

    bool isConsistent(const CspState<IdType, DataType>& state) const
    {
        return std::all_of(this->m_binaryConstrains.cbegin(), this->m_binaryConstrains.cend(),
                [&](const CspBinaryConstrain<IdType, DataType>& constrain)->bool{
                    auto var1 = constrain.m_idFirst;
                    auto var2 = constrain.m_idSecond;

                    // A constrain cannot be violated if the variables
                    // have not been set yet.
                    if (!state.isVarAssigned(var1) || !state.isVarAssigned(var2))
                    {
                        return true;
                    }

                    // A constrain cannot valid if the variables
                    // have no values in their domains.
                    if (state.isDomainEmpty(var1) || state.isDomainEmpty(var2))
                    {
                        return false;
                    }


                    return constrain.isValid(state);
                });
    }

private:
    std::vector<CspBinaryConstrain<IdType, DataType>> m_binaryConstrains;
};

#endif /* CSP_CONSTRAINS_H */

