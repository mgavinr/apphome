// cpp
// theirs
#include <lidebug.h>
// mine
#include "myGnomeApplication.h"

int main(int argc, char* argv[]) {
  auto rv = 0;
  li_debug_init((char*)"debug.out", argv[0], false);
  DBENTER("main()");
  DBLOG("This is log");
  DBLOGE("This is log error");
  DBLOGS("This is a logs with threads");
  DBLOGSE("This is log error with threads");
  DBTRACEE("This is an error trace statement");
  auto app = mygnome::myGnomeApplication(argc, argv);
  DBRETURN(rv);
  return rv;
}