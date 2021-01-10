//
// Created by gavinr on 10/01/2021.
//

#ifndef GNOMEHW_MYGNOMEMENUAPPLICATION_H
#define GNOMEHW_MYGNOMEMENUAPPLICATION_H

// cpp
// theirs
// mine
#include "myGnomeApplication.h"

namespace mygnome {

  class myGnomeMenuApplication {
  public:
    // class
    myGnomeMenuApplication()=delete;
    myGnomeMenuApplication(myGnomeApplication&);
    // methods
    void on_menu_file_new_generic();
    void on_menu_file_quit();
    void on_menu_help_about();
    // fields
    myGnomeApplication& m_app;
  };

}

#endif //GNOMEHW_MYGNOMEMENUAPPLICATION_H
