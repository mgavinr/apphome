#include <iostream>
//
#include <gtkmm/application.h>
//
#include "myGnomeWindow.h"

int main(int argc, char* argv[]) {
  std::cout << "Hello, World!" << std::endl;
  auto app = Gtk::Application::create("org.gtkmm.example");
  return app->make_window_and_run<mygnome::myGnomeWindow>(argc, argv);
}