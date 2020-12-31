//
// Created by gavinr on 31/12/2020.
//

#ifndef GNOMEHW_MYGNOMEWINDOW_H
#define GNOMEHW_MYGNOMEWINDOW_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
//
//

namespace mygnome {
  class myGnomeWindow : public Gtk::Window {
  public:
    myGnomeWindow();
    ~myGnomeWindow() override;

  protected:  // private
    void on_button_clicked();
    Gtk::Button m_button;
  };
}

#endif //GNOMEHW_MYGNOMEWINDOW_H