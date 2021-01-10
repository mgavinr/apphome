//
// Created by gavinr on 02/01/2021.
//

#include <iostream>
//
#include <gtkmm/application.h>
#include <glibmm.h>
//
#include "myGnomeApplication.h"
#include "myGnomeMenuApplication.h"
#include "myGnomeWindow.h"

using namespace mygnome;

myGnomeApplication::~myGnomeApplication() {
}

myGnomeApplication::myGnomeApplication(int argc, char **argv) {
  Glib::set_application_name("Main Menu Example");
  const int status = run(argc, argv);
  std::cout << "Exit Status " << status;
}

void myGnomeApplication::on_startup()
{
  Gtk::Application::on_startup();
  m_builder = Gtk::Builder::create();
  m_menu = std::make_shared<myGnomeMenuApplication>(*this);

  //Get the menubar and the app menu, and add them to the application:
  auto object = m_builder->get_object("menu-example");
  auto gmenu = std::dynamic_pointer_cast<Gio::Menu>(object);
  if (!gmenu)
  {
    g_warning("GMenu not found");
  }
  else
  {
    set_menubar(gmenu);
  }
}

void myGnomeApplication::on_activate()
{
  //std::cout << "debug1: " << G_STRFUNC << std::endl;
  // The application has been started, so let's show a window.
  // A real application might want to reuse this window in on_open(),
  // when asked to open a file, if no changes have been made yet.
  create_window();
}

void myGnomeApplication::create_window()
{
  auto win = new myGnomeWindow();

  //Make sure that the application runs for as long this window is still open:
  add_window(*win);

  //Delete the window when it is hidden.
  //That's enough for this simple example.
  win->signal_hide().connect(sigc::bind(
      sigc::mem_fun(*this, &myGnomeApplication::on_window_hide), win));

  win->set_show_menubar();
  win->show();
}

void myGnomeApplication::on_window_hide(Gtk::Window* window)
{
  delete window;
}

void myGnomeApplication::app_quit()
{
  std::cout << G_STRFUNC << std::endl;
  quit(); // Not really necessary, when Gtk::Widget::hide() is called.

  // Gio::Application::quit() will make Gio::Application::run() return,
  // but it's a crude way of ending the program. The window is not removed
  // from the application. Neither the window's nor the application's
  // destructors will be called, because there will be remaining reference
  // counts in both of them. If we want the destructors to be called, we
  // must remove the window from the application. One way of doing this
  // is to hide the window.
  std::vector<Gtk::Window*> windows = get_windows();
  if (windows.size() > 0)
    windows[0]->hide(); // In this simple case, we know there is only one window.
}
