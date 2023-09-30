
#ifndef LIBDSX_VEC_EXCEPTIONS
#define LIBDSX_VEC_EXCEPTIONS
#include <exception>

namespace dsx::structs::exceptions {
class NegativeIndexExecption : public std::exception {
public:

  const char * what () const throw ()
    {
    return "NegativeIndexExecption: index became negative";
    }
};
}
#endif
