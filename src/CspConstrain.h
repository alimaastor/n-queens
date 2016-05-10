
#ifndef CSP_CONSTRAIN_H
#define CSP_CONSTRAIN_H

#include "CspVar.h"
#include "CspState.h"

#include <functional>
#include <algorithm>

template <class IdType, class DataType>
using CspConstrainFunction = std::function<bool (const CspState<IdType, DataType>&)>;

template <class IdType, class DataType>
class CspConstrainBase
{
public:
    CspConstrainBase(const CspConstrainFunction<IdType, DataType>& f)
        : m_func(f)
    {}

    CspConstrainBase()
        : m_func()
    {}

    virtual bool isValid(const CspState<IdType, DataType>& state) const final
    {
        return this->m_func(state);
    }

private:
    CspConstrainFunction<IdType, DataType> m_func;
};

template <class IdType, class DataType>
class CspBinaryConstrain : public CspConstrainBase<IdType, DataType>
{
public:
    CspBinaryConstrain(IdType idFirst, IdType idSecond, const CspConstrainFunction<IdType, DataType>& f)
        : CspConstrainBase<IdType, DataType>(f),
          m_idFirst(idFirst),
          m_idSecond(idSecond)
    {}

    CspBinaryConstrain(const CspBinaryConstrain& other)
        : CspConstrainBase<IdType, DataType>(other),
          m_idFirst(other.m_idFirst),
          m_idSecond(other.m_idSecond)
    {}

    CspBinaryConstrain()
        : CspConstrainBase<IdType, DataType>(),
          m_idFirst(),
          m_idSecond()
    {}

    CspBinaryConstrain& operator=(CspBinaryConstrain other)
    {
        CspConstrainBase<IdType, DataType>::operator=(other);
        this->m_idFirst = other.m_idFirst;
        this->m_idSecond = other.m_idSecond;
        return *this;
    }

    IdType m_idFirst;
    IdType m_idSecond;
};

#endif /* CSP_CONSTRAIN_H */

