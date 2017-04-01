#pragma once 

#include <string>
#include <stdexcept>
#include <cstdint>
#include <locale>
#include <sstream>
#include <type_traits>


namespace csvxx {

    class field
    {
    public:
        //default ctor
        field() = default;

        //dtor
        ~field() = default;

        //copy ctors
        field(const field&) = default;
        field(field&&)      = default;

        //converting ctors
        field(const std::string&);
        field(std::string&&);
        field(const char* const);
        field(bool);

        template<typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
        field(T);

        //assignment ops
        field& operator =(const field&) = default;
        field& operator =(field&&)      = default;

        field& operator =(const std::string&);
        field& operator =(std::string&&);
        field& operator =(const char* const);
        field& operator =(bool);

        template<typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
        field& operator =(T);

        //aux methods
        void clear();

        //state getters
        bool empty() const;
        bool escaped() const;

        //typed getters
        const std::string& as_string() const;
        std::int64_t as_signed() const;
        std::uint64_t as_unsigned() const;
        double as_double() const;
        bool as_bool() const;

        //conversions
        explicit operator const std::string&() const;
        explicit operator std::string() const;
        explicit operator std::int64_t() const;
        explicit operator std::uint64_t() const;
        explicit operator double() const;
        explicit operator bool() const;

    private:
        std::string str_data_;
        bool        escaped_ = false;
    };


    inline
    field::field(const std::string& value)
        : str_data_(value)
        , escaped_(/*TODO*/false)
    {
    }

    inline
    field::field(std::string&& value)
        : str_data_(std::move(value))
        , escaped_(/*TODO*/false)
    {
    }

    inline
    field::field(const char* const value)
        : str_data_(value)
        , escaped_(/*TODO*/false)
    {
    }

    inline
    field::field(bool value)
    {
        std::locale loc;
        auto&& f = std::use_facet<std::numpunct<std::string::value_type>>(loc);
        this->str_data_ = (value) ? f.truename() : f.falsename();
    }

    template<typename T, typename>
    inline
    field::field(T value)
        : str_data_(std::to_string(value))
    {
    }

    inline
    field& field::operator =(const std::string& value)
    {
        this->str_data_ = value;
        this->escaped_ = false; //TODO
        return *this;
    }

    inline
    field& field::operator =(std::string&& value)
    {
        this->str_data_ = std::move(value);
        this->escaped_ = false; //TODO
        return *this;
    }

    inline
    field& field::operator =(const char* const value)
    {
        this->str_data_ = value;
        this->escaped_ = false; //TODO
        return *this;
    }

    inline
    field& field::operator =(bool value)
    {
        std::locale loc;
        auto&& f = std::use_facet<std::numpunct<std::string::value_type>>(loc);
        this->str_data_ = (value) ? f.truename() : f.falsename();
        this->escaped_ = false;
        return *this;
    }

    template<typename T, typename>
    inline
    field& field::operator =(T value)
    {
        this->str_data_ = std::to_string(value);
        this->escaped_ = false;
        return *this;
    }

    inline
    void field::clear()
    {
        this->str_data_.clear();
        this->escaped_ = false;
    }

    inline
    bool field::empty() const
    {
        return this->str_data_.empty();
    }

    inline
    bool field::escaped() const
    {
        return this->escaped_;
    }

    inline
    const std::string& field::as_string() const
    {
        return this->str_data_;
    }

    inline
    std::int64_t field::as_signed() const
    {
        return std::stoll(this->str_data_);
    }

    inline
    std::uint64_t field::as_unsigned() const
    {
        return std::stoull(this->str_data_);
    }

    inline
    double field::as_double() const
    {
        return std::stod(this->str_data_);
    }

    inline
    bool field::as_bool() const
    {
        bool res = false;
        std::istringstream ss(this->str_data_);
        ss >> std::boolalpha >> res;
        return res;
    }

    inline
    field::operator const std::string&() const
    {
        return this->as_string();
    }

    inline
    field::operator std::string() const
    {
        return this->as_string();
    }

    inline
    field::operator std::int64_t() const
    {
        return this->as_signed();
    }

    inline
    field::operator std::uint64_t() const
    {
        return this->as_unsigned();
    }

    inline
    field::operator double() const
    {
        return this->as_double();
    }

    inline
    field::operator bool() const
    {
        return this->as_bool();
    }

}

