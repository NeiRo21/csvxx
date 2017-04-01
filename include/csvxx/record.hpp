#pragma once

#include "csvxx/field.hpp"

#include <vector>


namespace csvxx {

    class record : private std::vector<field>
    {
        using base = std::vector<field>;

    public:
        //definitions
        using base::iterator;
        using base::const_iterator;
        using base::reverse_iterator;
        using base::const_reverse_iterator;

    public:
        //default ctor
        record() = default;

        //dtor
        ~record() = default;
        
        //copy ctors
        record(const record&) = default;
        record(record&&)      = default;

        //assignment ops
        record& operator =(const record&) = default;
        record& operator =(record&&)      = default;

        //inherited from base
        using base::begin;
        using base::cbegin;
        using base::rbegin;
        using base::crbegin;
        using base::end;
        using base::cend;
        using base::rend;
        using base::crend;

        using base::front;
        using base::back;
        using base::size;
        using base::empty;
        
        using base::clear;
        using base::resize;
        using base::swap;

        //ops
        field& operator [](size_t index);
        const field& operator [](size_t index) const;
        
        template<typename T>
        record& operator <<(T&& t);

        record& operator +=(const record& rhs);

        friend record operator +(record lhs, const record& rhs);
    };


    inline
    field& record::operator [](size_t index)
    {
        if (index >= this->size()) {
            this->resize(index + 1);
        }
        return this->base::operator [](index);
    }

    inline
    const field& record::operator [](size_t index) const
    {
        return this->base::at(index);
    }

    template<typename T>
    inline
    record& record::operator <<(T&& t)
    {
        this->base::emplace_back(std::forward<T>(t));
        return *this;
    }

    inline
    record& record::operator +=(const record& rhs)
    {
        this->base::reserve(this->size() + rhs.size());
        this->base::insert(this->end(), rhs.begin(), rhs.end());
        return *this;
    }

    inline
    record operator +(record lhs, const record& rhs)
    {
        lhs += rhs;
        return lhs;
    }

}

