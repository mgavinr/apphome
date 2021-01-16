//
// Created by gavinr on 31/12/2020.
//

// cpp
// theirs
#include <lidebug.h>
// mine
#include "myGnomeWindowTree.h"

using namespace mygnome;

myGnomeWindowTree::myGnomeWindowTree() :
m_button("Hello World"),
m_VBox(Gtk::Orientation::VERTICAL),
m_Button_Quit("Quit")
{
  // create
  set_title("Gtk::TreeView (ListStore) example");
  set_default_size(400, 200);
  m_refTreeModel = Gtk::ListStore::create(col);
  auto cell = Gtk::make_managed<Gtk::CellRendererProgress>();
  m_VBox.set_margin(5);
  set_child(m_VBox);
  m_VBox.append(m_ScrolledWindow);
  m_VBox.append(m_ButtonBox);
  m_button.signal_clicked().connect(sigc::mem_fun(*this, &myGnomeWindowTree::on_button_clicked));
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this, &myGnomeWindowTree::on_button_quit));

  // elements
  m_ScrolledWindow.set_child(m_TreeView);
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();
  m_TreeView.set_model(m_refTreeModel);
  {
    m_TreeView.append_column(col.ID, col.id);
    m_TreeView.append_column(col.AMIGA_HOSTNAME, col.amiga_hostname);
    m_TreeView.append_column(col.AMIGA_DIRECTORY, col.amiga_directory);
    m_TreeView.append_column(col.AMIGA_LOGIN_USER, col.amiga_login_user);
    m_TreeView.append_column(col.AMIGA_LOGIN_PASSWORD, col.amiga_login_password);
    m_TreeView.append_column(col.UNIX_DIRECTORY, col.unix_directory);
    m_TreeView.append_column(col.CONNECTED, col.connected);
    m_TreeView.append_column(col.CONNECTED_DURATION, col.connected_duration);
    m_TreeView.append_column(col.CONNECTED_BYTES, col.connected_bytes);
    m_TreeView.append_column(col.BACKUP_BUTTON, col.backup_button);
    //m_TreeView.append_column(col.BACKUP_PERCENTAGE, col.backup_percentage);
    //m_TreeView.append_column_numeric("Formatted number", col.m_col_number, "%010d" /* 10 digits, using leading zeroes. */);
  }
  {
    //Fill the TreeView's model
    // I am tempted to implement my own re-ordering 
    auto row = *(m_refTreeModel->append());
    row[col.id] = 1;
    row[col.amiga_hostname] = "AMIGAGREY";
    row[col.amiga_directory] = "RAM:";
    row[col.amiga_login_user] = "whoami";
    row[col.amiga_login_password] = "whoami";
    row[col.unix_directory] = "/home/whoami/network/AMIGAGREY/RAM";
    row[col.connected] = 0;
    row[col.connected_duration] = 0;
    row[col.connected_bytes] = 0;
    row[col.backup_button] = 0;
    row[col.backup_percentage] = 0;

    auto row2 = m_refTreeModel->append();
    row = *row2;
    row[col.id] = 2;
    row[col.amiga_hostname] = "AMIGAGREY";
    row[col.amiga_directory] = "SYS:";
    row[col.amiga_login_user] = "whoami";
    row[col.amiga_login_password] = "whoami";
    row[col.unix_directory] = "/home/whoami/network/AMIGAGREY/SYS";
    row[col.connected] = 0;
    row[col.connected_duration] = 0;
    row[col.connected_bytes] = 0;
    row[col.backup_button] = 0;
    row[col.backup_percentage] = 0;

    row = *(m_refTreeModel->append());
    row[col.id] = 3;
    row[col.amiga_hostname] = "AMIGAGREY";
    row[col.amiga_directory] = "SYS:";
    row[col.amiga_login_user] = "whoami";
    row[col.amiga_login_password] = "whoami";
    row[col.unix_directory] = "/home/whoami/network/AMIGAGREY/SYS";
    row[col.connected] = 0;
    row[col.connected_duration] = 0;
    row[col.connected_bytes] = 0;
    row[col.backup_button] = 0;
    row[col.backup_percentage] = 0;

    m_refTreeModel->erase(row2);
  }
  {
    int cols_count = m_TreeView.append_column(col.BACKUP_PERCENTAGE, *cell);
    auto pColumn = m_TreeView.get_column(cols_count - 1);
    if(pColumn)
    {
      pColumn->add_attribute(cell->property_value(), col.backup_percentage);
    }

    //Make all the columns reorderable:
    //This is not necessary, but it's nice to show the feature.
    //You can use TreeView::set_column_drag_function() to more
    //finely control column drag and drop.
    for(guint i = 0; i < 2; i++)
    {
      auto column = m_TreeView.get_column(i);
      column->set_reorderable();
      column->set_sort_indicator(true);
    }
  }

  // elements
  m_button.set_margin(10);

  // elements
  m_ButtonBox.set_margin(5);
  m_ButtonBox.append(m_Button_Quit);
  m_Button_Quit.set_hexpand(true);
  m_Button_Quit.set_halign(Gtk::Align::END);
}

myGnomeWindowTree::~myGnomeWindowTree() {

}

void myGnomeWindowTree::on_button_clicked() {
  DBLOG("Button pressed");
}

void myGnomeWindowTree::on_button_quit() {
  DBLOG("Button quit pressed");
  hide();
}
