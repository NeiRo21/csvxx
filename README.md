# csvxx
csvxx is a C++14 header-only library for reading/writing [RFC 4180](https://tools.ietf.org/html/rfc4180) compliant CSV data.

## TODO
* comments
* implement consistent conversion behaviour: throw an exception if conversion can't be performed etc.
* escaping support
* `std::to_string()` works badly for floating point operations
* improve boolean values translation: currently only text representation is recognized (using current locale)
* use `constexpr` when appropriate
