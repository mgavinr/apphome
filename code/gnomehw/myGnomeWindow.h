//
// Created by gavinr on 31/12/2020.
//

#ifndef GNOMEHW_MYGNOMEWINDOW_H
#define GNOMEHW_MYGNOMEWINDOW_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/applicationwindow.h>

//
//

namespace mygnome {
  class myGnomeWindow : public Gtk::ApplicationWindow {
  public:
    // Class
    myGnomeWindow();
    ~myGnomeWindow() override;
    // Methods theirs
    // Methods mine
    void on_button_clicked();
    // Fields
    Gtk::Button m_button;
  };
}

#endif //GNOMEHW_MYGNOMEWINDOW_H
