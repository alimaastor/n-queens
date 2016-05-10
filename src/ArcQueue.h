
#ifndef ARC_QUEUE_H
#define ARC_QUEUE_H

#include "CspConstrain.h"

#include <deque>

template <class IdType, class DataType>
class ArcQueue
{
public:
    ArcQueue()
        : m_arcMap(),
          m_arcDeque()
    {}

    using Arc = std::pair<const std::pair<IdType, IdType>, CspBinaryConstrain<IdType, DataType>>;

    bool isEmpty() const
    {
        return this->m_arcDeque.empty();
    }

    Arc popNext()
    {
        auto key = this->m_arcDeque.at(0);
        this->m_arcDeque.pop_front();

        auto it = this->m_arcMap.find(key);
        this->m_arcMap.erase(key);

        return {key, it->second};
    }

    void maybeAddArc(const Arc& arc)
    {
        if (this->m_arcMap.find(arc.first) == this->m_arcMap.end())
        {
            this->m_arcDeque.push_back(arc.first);
            this->m_arcMap[arc.first] = arc.second;
        }
    }

private:
    std::map<std::pair<IdType, IdType>, CspBinaryConstrain<IdType, DataType>> m_arcMap;
    std::deque<std::pair<IdType, IdType>> m_arcDeque;
};

#endif /* ARC_QUEUE_H */

