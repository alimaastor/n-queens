
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

    virtual bool isValid(const CspState<IdType, DataType>& state) const final
    {
        return this->m_func(state);
    }

private:
    const CspConstrainFunction<IdType, DataType> m_func;
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

    CspBinaryConstrain()
        : CspConstrainBase<IdType, DataType>(),
          m_idFirst(),
          m_idSecond()
    {}

    const IdType m_idFirst;
    const IdType m_idSecond;
};

#endif /* CSP_CONSTRAIN_H */

