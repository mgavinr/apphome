//
// Created by gavinr on 02/01/2021.
//

#ifndef GNOMEHW_MYGNOMEEXCEPTION_H
#define GNOMEHW_MYGNOMEEXCEPTION_H

// cpp
#include <stdexcept>
#include <string>
// theirs
// mine

namespace mygnome {
  class myGnomeException : public std::runtime_error {
    public:
        myGnomeException(const std::string& m=std::string("myGnomeException")) :
            std::runtime_error(m)
        {
        };
  };
}

#endif //GNOMEHW_MYGNOMEEXCEPTION_H
