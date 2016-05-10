
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
            arcQueue.addArc({std::make_pair(constrain.m_idFirst, constrain.m_idSecond), constrain});
        }

        return arcQueue;
    }

    Arc<IdType, DataType> getArcsForHead(IdType idHead)
    {

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

                    return constrain.isValid(state);
                });
    }

private:
    std::vector<CspBinaryConstrain<IdType, DataType>> m_binaryConstrains;
};

#endif /* CSP_CONSTRAINS_H */

