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
        // default ctor
        field() = default;

        // dtor
        ~field() = default;

        // copy ctors
        field(const field&) = default;
        field(field&&)      = default;

        // converting ctors
        field(const std::string&);
        field(std::string&&);
        field(const char* const);
        field(bool);

        template<typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
        field(T);

        // assignment operators
        field& operator =(const field&) = default;
        field& operator =(field&&)      = default;

        field& operator =(const std::string&);
        field& operator =(std::string&&);
        field& operator =(const char* const);
        field& operator =(bool);

        template<typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
        field& operator =(T);

        // aux methods
        void clear();

        // state getters
        bool empty() const;
        bool escaped() const;

        // typed getters
        const std::string& as_string() const;
        std::int64_t as_signed() const;
        std::uint64_t as_unsigned() const;
        double as_double() const;
        bool as_bool() const;

        // conversions
        explicit operator const std::string&() const;
        explicit operator std::string() const;
        explicit operator std::int64_t() const;
        explicit operator std::uint64_t() const;
        explicit operator double() const;
        explicit operator bool() const;

    private:
        std::string m_data;
        bool        m_escaped = false;
    };


    inline
    field::field(const std::string& value)
        : m_data(value)
        , m_escaped(/*TODO*/false)
    {
    }

    inline
    field::field(std::string&& value)
        : m_data(std::move(value))
        , m_escaped(/*TODO*/false)
    {
    }

    inline
    field::field(const char* const value)
        : m_data(value)
        , m_escaped(/*TODO*/false)
    {
    }

    inline
    field::field(bool value)
    {
        std::locale loc;
        auto&& f = std::use_facet<std::numpunct<std::string::value_type>>(loc);
        m_data = (value) ? f.truename() : f.falsename();
    }

    template<typename T, typename>
    inline
    field::field(T value)
        : m_data(std::to_string(value))
    {
    }

    inline
    field& field::operator =(const std::string& value)
    {
        m_data = value;
        m_escaped = false; //TODO
        return *this;
    }

    inline
    field& field::operator =(std::string&& value)
    {
        m_data = std::move(value);
        m_escaped = false; //TODO
        return *this;
    }

    inline
    field& field::operator =(const char* const value)
    {
        m_data = value;
        m_escaped = false; //TODO
        return *this;
    }

    inline
    field& field::operator =(bool value)
    {
        std::locale loc;
        auto&& f = std::use_facet<std::numpunct<std::string::value_type>>(loc);
        m_data = (value) ? f.truename() : f.falsename();
        m_escaped = false;
        return *this;
    }

    template<typename T, typename>
    inline
    field& field::operator =(T value)
    {
        m_data = std::to_string(value);
        m_escaped = false;
        return *this;
    }

    inline
    void field::clear()
    {
        m_data.clear();
        m_escaped = false;
    }

    inline
    bool field::empty() const
    {
        return m_data.empty();
    }

    inline
    bool field::escaped() const
    {
        return m_escaped;
    }

    inline
    const std::string& field::as_string() const
    {
        return m_data;
    }

    inline
    std::int64_t field::as_signed() const
    {
        return std::stoll(m_data);
    }

    inline
    std::uint64_t field::as_unsigned() const
    {
        return std::stoull(m_data);
    }

    inline
    double field::as_double() const
    {
        return std::stod(m_data);
    }

    inline
    bool field::as_bool() const
    {
        bool res = false;
        std::istringstream ss(m_data);
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

