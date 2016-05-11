
#ifndef ARC_QUEUE_H
#define ARC_QUEUE_H

#include "CspConstrain.h"

#include <deque>

template <class IdType, class DataType>
using Arc = std::pair<const std::pair<IdType, IdType>, CspBinaryConstrain<IdType, DataType>>;

template <class IdType, class DataType>
class ArcQueue
{
public:
    ArcQueue()
        : m_constrainDeque(),
          m_arcDeque()
    {}

    bool isEmpty() const
    {
        return this->m_arcDeque.empty();
    }

    Arc<IdType, IdType> popNext()
    {
        auto arc = this->m_arcDeque.at(0);
        this->m_arcDeque.pop_front();

        auto constrain = this->m_constrainDeque.at(0);
        this->m_constrainDeque.pop_front();

        return {arc, constrain};
    }

    void maybeAddArc(const Arc<IdType, IdType>& newArc)
    {
        for (const auto& arc : this->m_arcDeque)
        {
            if (arc.first == newArc.first.first && arc.second == newArc.first.second)
            {
                return;
            }
        }

        this->m_arcDeque.push_back(newArc.first);
        this->m_constrainDeque.push_back(newArc.second);
    }

private:
    std::deque<CspBinaryConstrain<IdType, DataType>> m_constrainDeque;
    std::deque<std::pair<IdType, IdType>> m_arcDeque;
};

#endif /* ARC_QUEUE_H */

