//
// Created by gavinr on 31/12/2020.
//

#ifndef GNOMEHW_MYGNOMEWINDOWTREE_H
#define GNOMEHW_MYGNOMEWINDOWTREE_H

// cpp
// theirs
#include <gtkmm.h>
// mine

namespace mygnome {
  class myGnomeWindowTree : public Gtk::ApplicationWindow {
  public:
    // Class
    myGnomeWindowTree();
    ~myGnomeWindowTree() override;
    //Tree model columns:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord
    {
      public:
        ModelColumns() { 
          add(id); 
          add(amiga_hostname); 
          add(amiga_directory); 
          add(amiga_login_user);
          add(amiga_login_password);
          add(unix_directory);
          add(connected);
          add(connected_duration);
          add(connected_bytes);
          add(backup_button);
          add(backup_percentage);
        }

        Gtk::TreeModelColumn<unsigned int> id;
        Gtk::TreeModelColumn<Glib::ustring> amiga_hostname;
        Gtk::TreeModelColumn<Glib::ustring> amiga_directory;
        Gtk::TreeModelColumn<Glib::ustring> amiga_login_user;
        Gtk::TreeModelColumn<Glib::ustring> amiga_login_password;
        Gtk::TreeModelColumn<Glib::ustring> unix_directory;
        Gtk::TreeModelColumn<unsigned int> connected;
        Gtk::TreeModelColumn<unsigned int> connected_duration;
        Gtk::TreeModelColumn<unsigned int> connected_bytes;
        Gtk::TreeModelColumn<unsigned int> backup_button;
        Gtk::TreeModelColumn<unsigned int> backup_percentage;

        inline static const std::string ID="ID";
        inline static const std::string AMIGA_HOSTNAME="Amiga Hostname";
        inline static const std::string AMIGA_DIRECTORY="Amiga Dir";
        inline static const std::string AMIGA_LOGIN_USER="Amiga Username";
        inline static const std::string AMIGA_LOGIN_PASSWORD="Amiga Password";
        inline static const std::string UNIX_DIRECTORY="Unix Dir";
        inline static const std::string CONNECTED="Connected";
        inline static const std::string CONNECTED_DURATION="Duration";
        inline static const std::string CONNECTED_BYTES="Bytes";
        inline static const std::string BACKUP_BUTTON="Backup";
        inline static const std::string BACKUP_PERCENTAGE="Backup %%";
    };

    // Methods theirs
    // Methods mine
    void on_button_clicked();
    void on_button_quit();
    // Fields
    ModelColumns col;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
    Gtk::Box m_VBox;
    Gtk::ScrolledWindow m_ScrolledWindow;
    Gtk::TreeView m_TreeView;
    Gtk::Box m_ButtonBox;
    Gtk::Button m_Button_Quit;
    Gtk::Button m_button;
  };
}

#endif //GNOMEHW_MYGNOMEWINDOWTREE_H
