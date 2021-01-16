// cpp
// theirs
#include <lidebug.h>
// mine
#include "myGnomeApplication.h"

int main(int argc, char* argv[]) {
  auto rv = 0;
  li_debug_init((char*)"debug.out", argv[0], false);
  DBENTER("main()");
  DBLOGP("This is log, stdout file");
  DBLOGPE("This is log error, stdout stderr file");
  DBLOG("This is a logs with threads, stdout file with indents");
  DBLOGE("This is log error with threads, stdout stderr file with indents");
  DBTRACEE("This is an error trace statement");
  auto app = mygnome::myGnomeApplication(argc, argv);
  DBRETURN(rv);
  return rv;
}
