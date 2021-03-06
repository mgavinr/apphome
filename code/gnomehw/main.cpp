// cpp
// theirs
#include <lidebug.h>
// mine
#include "myGnomeApplication.h"
#include "myGnomeException.h"

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
  try {
    throw mygnome::myGnomeException("What");
  } catch (const std::exception& e) {
    DBLOGE("EX: %s" , e.what());
  } catch (...) {
    DBLOGE("EX: dear me");
  }
  DBRETURN(rv);
  return rv;
}
