//
// Created by gavinr on 02/01/2021.
//

#ifndef GNOMEHW_MYGNOMEAPPLICATION_H
#define GNOMEHW_MYGNOMEAPPLICATION_H

#include <gtkmm.h>
#include <gtkmm/application.h>

namespace mygnome {
  class myGnomeApplication : public Gtk::Application {
  public:
    // Class
    virtual ~myGnomeApplication();
    myGnomeApplication() = delete;
    myGnomeApplication(int argc, char *argv[]);
    // Methods theirs
    void on_startup() override;
    void on_activate() override;
    // Methods mine
    void create_window();
    void on_window_hide(Gtk::Window* window);
    void on_menu_file_new_generic();
    void on_menu_file_quit();
    void on_menu_help_about();
    // Fields
    //Glib::RefPtr<Gtk::Application> m_app;
    Glib::RefPtr<Gtk::Builder> m_builder;
  };
}

#endif //GNOMEHW_MYGNOMEAPPLICATION_H
