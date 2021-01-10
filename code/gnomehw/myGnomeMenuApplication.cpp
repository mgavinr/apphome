//
// Created by gavinr on 10/01/2021.
//

// cpp
#include <iostream>
// theirs
#include <lidebug.h>
// mine
#include "myGnomeMenuApplication.h"
#include "myGnomeApplication.h"

using namespace mygnome;

mygnome::myGnomeMenuApplication::myGnomeMenuApplication(mygnome::myGnomeApplication& app) :
 m_app(app)
 {
  //We can use add_action() because Gtk::Application derives from Gio::ActionMap.
  //File|New sub menu:
  m_app.add_action("newstandard", sigc::mem_fun(*this, &myGnomeMenuApplication::on_menu_file_new_generic));
  m_app.add_action("newfoo", sigc::mem_fun(*this, &myGnomeMenuApplication::on_menu_file_new_generic));
  m_app.add_action("newgoo", sigc::mem_fun(*this, &myGnomeMenuApplication::on_menu_file_new_generic));
  //File menu:
  m_app.add_action("quit", sigc::mem_fun(*this, &myGnomeMenuApplication::on_menu_file_quit));
  //Help menu:
  m_app.add_action("about", sigc::mem_fun(*this, &myGnomeMenuApplication::on_menu_help_about));

  //Layout the actions in a menubar and a menu:
  Glib::ustring ui_info =
      "<interface>"
      "  <!-- menubar -->"
      "  <menu id='menu-example'>"
      "    <submenu>"
      "      <attribute name='label' translatable='yes'>_File</attribute>"
      "      <section>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>New _Standard</attribute>"
      "          <attribute name='action'>app.newstandard</attribute>"
      "          <attribute name='accel'>&lt;Primary&gt;n</attribute>"
      "        </item>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>New _Foo</attribute>"
      "          <attribute name='action'>app.newfoo</attribute>"
      "        </item>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>New _Goo</attribute>"
      "          <attribute name='action'>app.newgoo</attribute>"
      "        </item>"
      "      </section>"
      "      <section>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>_Quit</attribute>"
      "          <attribute name='action'>app.quit</attribute>"
      "          <attribute name='accel'>&lt;Primary&gt;q</attribute>"
      "        </item>"
      "      </section>"
      "    </submenu>"
      "    <submenu>"
      "      <attribute name='label' translatable='yes'>_Edit</attribute>"
      "      <section>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>_Copy</attribute>"
      "          <attribute name='action'>win.copy</attribute>"
      "          <attribute name='accel'>&lt;Primary&gt;c</attribute>"
      "        </item>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>_Paste</attribute>"
      "          <attribute name='action'>win.paste</attribute>"
      "          <attribute name='accel'>&lt;Primary&gt;v</attribute>"
      "        </item>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>_Something</attribute>"
      "          <attribute name='action'>win.something</attribute>"
      "        </item>"
      "      </section>"
      "    </submenu>"
      "    <submenu>"
      "      <attribute name='label' translatable='yes'>_Choices</attribute>"
      "      <section>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>Choice _A</attribute>"
      "          <attribute name='action'>win.choice</attribute>"
      "          <attribute name='target'>a</attribute>"
      "        </item>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>Choice _B</attribute>"
      "          <attribute name='action'>win.choice</attribute>"
      "          <attribute name='target'>b</attribute>"
      "        </item>"
      "      </section>"
      "    </submenu>"
      "    <submenu>"
      "      <attribute name='label' translatable='yes'>_Other Choices</attribute>"
      "      <section>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>Choice 1</attribute>"
      "          <attribute name='action'>win.choiceother</attribute>"
      "          <attribute name='target' type='i'>1</attribute>"
      "        </item>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>Choice 2</attribute>"
      "          <attribute name='action'>win.choiceother</attribute>"
      "          <attribute name='target' type='i'>2</attribute>"
      "        </item>"
      "      </section>"
      "      <section>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>Some Toggle</attribute>"
      "          <attribute name='action'>win.sometoggle</attribute>"
      "        </item>"
      "      </section>"
      "    </submenu>"
      "    <submenu>"
      "      <attribute name='label' translatable='yes'>_Help</attribute>"
      "      <section>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>_About Window</attribute>"
      "          <attribute name='action'>win.about</attribute>"
      "        </item>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>_About App</attribute>"
      "          <attribute name='action'>app.about</attribute>"
      "        </item>"
      "      </section>"
      "    </submenu>"
      "  </menu>"
      "</interface>";

  try
  {
    m_app.m_builder->add_from_string(ui_info);
  }
  catch (const Glib::Error& ex)
  {
    std::cerr << "Building menus failed: " << ex.what();
  }

}
void myGnomeMenuApplication::on_menu_file_new_generic()
{
  std::cout << "A File|New menu item was selected." << std::endl;
}

void myGnomeMenuApplication::on_menu_file_quit()
{
  m_app.app_quit();
}

void myGnomeMenuApplication::on_menu_help_about()
{
  std::cout << "Help|About App was selected." << std::endl;
}