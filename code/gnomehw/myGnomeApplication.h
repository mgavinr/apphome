//
// Created by gavinr on 02/01/2021.
//

#ifndef GNOMEHW_MYGNOMEAPPLICATION_H
#define GNOMEHW_MYGNOMEAPPLICATION_H

// cpp
// theirs
#include <gtkmm.h>
#include <gtkmm/application.h>
// mine

namespace mygnome {
  class myGnomeMenuApplication;
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
    void app_quit();
    // Fields
    //Glib::RefPtr<Gtk::Application> m_app;
    Glib::RefPtr<Gtk::Builder> m_builder;
    std::shared_ptr<myGnomeMenuApplication> m_menu;
  };
}

#endif //GNOMEHW_MYGNOMEAPPLICATION_H
