#pragma once

#include "csvxx/record.hpp"

#include <initializer_list>
#include <type_traits>
#include <algorithm>


namespace csvxx {

    class file : private std::vector<record>
    {
        using base = std::vector<record>;

    public:
        //definitions
        using base::iterator;
        using base::const_iterator;
        using base::reverse_iterator;
        using base::const_reverse_iterator;

    public:
        //default ctor
        file() = default;

        //dtor
        ~file() = default;
        
        //copy ctors
        file(const file&) = default;
        file(file&&)      = default;

        //assignment ops
        file& operator =(const file&) = default;
        file& operator =(file&&)      = default;

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

        //methods accepting initializer_list
        file(std::initializer_list<record> il);
        file& operator =(std::initializer_list<record> il);

        //ops
        record& operator [](size_t index);
        const record& operator [](size_t index) const;

        template<typename T, typename = std::enable_if_t<std::is_same<record, std::decay_t<T>>::value>>
        file& operator <<(T&& rhs);

        //misc
        void clear();

        size_t getWidth() const
        {
            return this->max_rec_width_;
        }

    private:
        size_t max_rec_width_ = 0;
    };


    file::file(std::initializer_list<record> il)
        : base(std::move(il))
    {
        auto widestRecIt = std::max_element(this->begin(),
                                            this->end(),
                                            [](const record& lhs, const record& rhs) { return lhs.size() < rhs.size(); }
                                            );
        this->max_rec_width_ = widestRecIt->size();
    }

    inline
    file& file::operator =(std::initializer_list<record> il)
    {
        this->base::operator =(std::move(il));

        auto widestRecIt = std::max_element(this->begin(),
                                            this->end(),
                                            [](const record& lhs, const record& rhs) { return lhs.size() < rhs.size(); }
                                            );
        this->max_rec_width_ = widestRecIt->size();

        return *this;
    }

    inline
    record& file::operator [](size_t index)
    {
        if (index >= this->size()) {
            this->resize(index + 1);
        }
        return this->base::operator [](index);
    }

    inline
    const record& file::operator [](size_t index) const
    {
        return this->base::at(index);
    }

    template<typename T, typename>
    inline
    file& file::operator <<(T&& /*record*/ rhs)
    {
        this->base::push_back(std::forward<T>(rhs));
        auto& newRec = this->base::back();
        this->max_rec_width_ = std::max(this->max_rec_width_, rhs.size());
        return *this;
    }

    inline
    void file::clear()
    {
        this->base::clear();
        this->max_rec_width_ = 0;
    }
}

