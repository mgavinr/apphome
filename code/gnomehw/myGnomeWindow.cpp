//
// Created by gavinr on 31/12/2020.
//

#include <iostream>
//
//
#include "myGnomeWindow.h"

using namespace mygnome;

myGnomeWindow::myGnomeWindow() :
m_button("Hello World")
{
  m_button.set_margin(10);
  m_button.signal_clicked().connect(
      sigc::mem_fun(*this, &myGnomeWindow::on_button_clicked));
  set_child(m_button);
}

myGnomeWindow::~myGnomeWindow() {

}

void myGnomeWindow::on_button_clicked() {
  std::cout << "Button pressed\n";
}
