
#ifndef CSP_CONSTRAIN_H
#define CSP_CONSTRAIN_H

#include "CspVar.h"

#include <functional>

template <class IdType, class DataType>
using CspConstrainFunction = std::function<bool (const CspVarMap<IdType, DataType>&)>;

template <class IdType, class DataType>
class CspConstrainBase
{
    CspConstrainBase(const CspConstrainFunction<IdType, DataType>& f)
        : m_func(f)
    {}

    virtual bool check(const CspVarMap<IdType, DataType>& varMap) const final
    {
        return this->m_func(varMap);
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

    const IdType m_idFirst;
    const IdType m_idSecond;
};

#endif /* CSP_CONSTRAIN_H */

