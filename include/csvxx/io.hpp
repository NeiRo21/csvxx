#pragma once

#include <istream>
#include <ostream>

namespace csvxx {

    //output
    struct _put_file
    {
        const file& f;
        bool force_escaping;
    };

    inline
    _put_file put_file(const file& f, bool force_escaping = false)
    {
        return {f, force_escaping};
    }

    inline
    std::ostream& operator <<(std::ostream& os, _put_file pf)
    {
        const char* const field_sep    = ",";
        const char escaping            = '"';
        const char* const esc_escaping = "\"\"";
        const char* const record_sep   = "\r\n";

        for (auto& rec: pf.f) {
            auto first_field = true;
            for (auto& fld: rec) {
                if (first_field) {
                    first_field = false;
                }
                else {
                    os << field_sep;
                }

                auto& str = fld.as_string();
                if (pf.force_escaping || fld.escaped()) {
                    //TODO implement
                    os << escaping << str << escaping;
                }
                else {
                    os << str;
                }
            }

            os << record_sep;
        }

        return os;
    }

    //input
    struct _get_file
    {
        file& f;
    };

    inline
    _get_file(file& f)
    {
        return {f};
    }

    inline
    std::istream& operator >>(std::istream& is, _get_file gf)
    {
        if (false) {
            is.setstate(std::ios::failbit);
        }
        return is;
    }
}

