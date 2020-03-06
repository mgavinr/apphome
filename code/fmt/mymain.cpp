#include <iostream>
#include <sstream>
#include <chrono>
#include "myformat.h"
#include <format>

void many_mix_args() {
  std::string name = "Gavin";
  std::string surname = "Rogers";
  int age = 3;
  std::string name1 = "Gavin1";
  std::string surname1 = "Rogers1";
  int age1 = 31;
  std::cerr << fmt::format("Hello name {} surname {} the {} Hello name {} surname {} the {}", name, surname, age, name1, surname1, age1);
}

void many_mix_noargs_quick() {
  std::cerr << fmt::format("Hello name Gavin surname Rogers the 3 Hello name Gavin surname Rogers the 3");
}

void many_mix_noargs() {
  std::string name = "Gavin";
  std::string surname = "Rogers";
  int age = 3;
  std::string name1 = "Gavin1";
  std::string surname1 = "Rogers1";
  int age1 = 31;
  std::stringstream a;
  a << "Hello name " << name << " surname " << surname << "the " << std::to_string(age) << "Hello name " << name1 << " surname " << surname1 << "the " << std::to_string(age1);
  std::cerr << fmt::format(a.str());
}

void many_s_args() {
  std::string name = "Gavin";
  std::string surname = "Rogers";
  std::string age = "3";
  std::string name1 = "Gavin1";
  std::string surname1 = "Rogers1";
  std::string age1 = "31";
  std::cerr << fmt::format("Hello name {} surname {} the {} Hello name {} surname {} the {} Hello name {} surname {} the {} Hello name {} surname {} the {}", name, surname, age, name1, surname1, age1, name, surname, age, name1, surname1, age1);
}

void many_s_noargs_quick() {
  std::cerr << fmt::format("Hello name Gavin surname Rogers the 3 Hello name Gavin surname Rogers the 3");
}

void many_s_noargs() {
  std::stringstream a;
  std::string name = "Gavin";
  std::string surname = "Rogers";
  std::string age = "3";
  std::string name1 = "Gavin1";
  std::string surname1 = "Rogers1";
  std::string age1 = "31";
  a << "Hello name " << name << " surname " << surname << "the " << age << "Hello name " << name1 << " surname " << surname1 << "the " << age1 << "Hello name " << name << " surname " << surname << "the " << age << "Hello name " << name1 << " surname " << surname1 << "the " << age1;
  std::cerr << fmt::format(a.str());
}

void three_mix_args() {
  std::string name = "Gavin";
  std::string surname = "Rogers";
  int age = 3;
  std::cerr << fmt::format("Hello name {} surname {} the {}", name, surname, age);
}

void three_mix_noargs_quick() {
  std::cerr << fmt::format("Hello name Gavin surname Rogers the 3");
}

void three_mix_noargs() {
  std::string name = "Gavin";
  std::string surname = "Rogers";
  int age = 3;
  std::stringstream a;
  a << "Hello name " << name << " surname " << surname << "the " << std::to_string(age);
  std::cerr << fmt::format(a.str());
}

void three_s_args() {
  std::string name = "Gavin";
  std::string surname = "Rogers";
  std::string age = "3";
  std::cerr << fmt::format("Hello name {} surname {} the {}", name, surname, age);
}

void three_s_noargs_quick() {
  std::cerr << fmt::format("Hello name Gavin surname Rogers the 3");
}

void three_s_noargs() {
  std::string name = "Gavin";
  std::string surname = "Rogers";
  std::string age = "3";
  std::stringstream a;
  a << "Hello name " << name << " surname " << surname << "the " << age;
  std::cerr << fmt::format(a.str());
}

int main(void) {
  
  std::chrono::duration<double> elapsed;
  auto start = std::chrono::high_resolution_clock::now();
  auto finish = std::chrono::high_resolution_clock::now();

  ///////////////////////////////////////////////////////////////////////////
  std::cout << "MIX OF INTS AND STRS\n";
  // A......
  start = std::chrono::high_resolution_clock::now();
  for(auto i=0; i < 1000000; i++) {
    three_mix_args();
  }
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "A=" << elapsed.count() << " .... {} format replace)\n";

  // B......
  start = std::chrono::high_resolution_clock::now();
  for(auto i=0; i < 1000000; i++) {
    three_mix_noargs_quick();
  }
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "B=" << elapsed.count() << "\n";

  // C......
  start = std::chrono::high_resolution_clock::now();
  for(auto i=0; i < 1000000; i++) {
    three_mix_noargs();
  }
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "C=" << elapsed.count() << " .... << individual params\n";

  // A......
  start = std::chrono::high_resolution_clock::now();
  for(auto i=0; i < 1000000; i++) {
    three_mix_args();
  }
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "A=" << elapsed.count() << " .... {} format replace)\n";

  ///////////////////////////////////////////////////////////////////////////
  std::cout << "STRS only\n";

  // A......
  start = std::chrono::high_resolution_clock::now();
  for(auto i=0; i < 1000000; i++) {
    three_s_args();
  }
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "A=" << elapsed.count() << " .... {} format replace)\n";

  // B......
  start = std::chrono::high_resolution_clock::now();
  for(auto i=0; i < 1000000; i++) {
    three_s_noargs_quick();
  }
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "B=" << elapsed.count() << "\n";

  // C......
  start = std::chrono::high_resolution_clock::now();
  for(auto i=0; i < 1000000; i++) {
    three_s_noargs();
  }
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "C=" << elapsed.count() << " .... << individual params\n";

  // A......
  start = std::chrono::high_resolution_clock::now();
  for(auto i=0; i < 1000000; i++) {
    three_s_args();
  }
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "A=" << elapsed.count() << " .... {} format replace)\n";
  
  ///////////////////////////////////////////////////////////////////////////
  std::cout << "MANY mix values only\n";

  // A......
  start = std::chrono::high_resolution_clock::now();
  for(auto i=0; i < 1000000; i++) {
    many_mix_args();
  }
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "A=" << elapsed.count() << " .... {} format replace)\n";

  // B......
  start = std::chrono::high_resolution_clock::now();
  for(auto i=0; i < 1000000; i++) {
    many_mix_noargs_quick();
  }
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "B=" << elapsed.count() << "\n";

  // C......
  start = std::chrono::high_resolution_clock::now();
  for(auto i=0; i < 1000000; i++) {
    many_mix_noargs();
  }
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "C=" << elapsed.count() << " .... << individual params\n";

  // A......
  start = std::chrono::high_resolution_clock::now();
  for(auto i=0; i < 1000000; i++) {
    many_mix_args();
  }
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "A=" << elapsed.count() << " .... {} format replace)\n";
  //
  ///////////////////////////////////////////////////////////////////////////
  std::cout << "MANY strings only\n";

  // A......
  start = std::chrono::high_resolution_clock::now();
  for(auto i=0; i < 1000000; i++) {
    many_s_args();
  }
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "A=" << elapsed.count() << " .... {} format replace)\n";

  // B......
  start = std::chrono::high_resolution_clock::now();
  for(auto i=0; i < 1000000; i++) {
    many_s_noargs_quick();
  }
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "B=" << elapsed.count() << "\n";

  // C......
  start = std::chrono::high_resolution_clock::now();
  for(auto i=0; i < 1000000; i++) {
    many_s_noargs();
  }
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "C=" << elapsed.count() << " .... << individual params\n";

  // A......
  start = std::chrono::high_resolution_clock::now();
  for(auto i=0; i < 1000000; i++) {
    many_s_args();
  }
  finish = std::chrono::high_resolution_clock::now();
  elapsed = finish - start;
  std::cout << "A=" << elapsed.count() << " .... {} format replace)\n";

  return 0;
}

/*
int main(void) {
  std::cout << fmt::format("Hello name {} surname {} the {}", "Gavin", "Rogers", 3);
  std::cout << "\nEND\n";
  std::cout << fmt::format("Hello name {} surname", "Gavin", "Rogers", 3);
  std::cout << "\nEND\n";
  std::cout << fmt::format("Hello name {} surname");
  std::cout << "\nEND\n";
  std::cout << fmt::format("Hello name {} surname {}");
  std::cout << "\nEND\n";
  std::cout << fmt::format("Hello name {} surname {}", 1);
  std::cout << "\nEND\n";
  std::cout << fmt::format("Hello name {} surname {}", 1, 2);
  std::cout << "\nEND\n";
  std::cout << fmt::format("Hello");
  std::cout << "\nEND\n";
  std::cout << fmt::format(1);
  std::cout << "\nEND\n";
  return 0;
}
*/
