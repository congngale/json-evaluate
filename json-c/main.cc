#include <json.h>
#include <unistd.h>

#include <chrono>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

// define data
constexpr auto kCanadaData = "../data/canada.json";

void mem_usage(double &vm_usage, double &resident_set) {
  using namespace std;
  vm_usage = 0.0;
  resident_set = 0.0;
  ifstream stat_stream("/proc/self/stat",
                       ios_base::in); // get info from proc directory

  // create some variables to get info
  string pid, comm, state, ppid, pgrp, session, tty_nr;
  string tpgid, flags, minflt, cminflt, majflt, cmajflt;
  string utime, stime, cutime, cstime, priority, nice;
  string O, itrealvalue, starttime;
  long rss;
  unsigned long vsize;

  stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr >>
      tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt >> utime >>
      stime >> cutime >> cstime >> priority >> nice >> O >> itrealvalue >>
      starttime >> vsize >> rss; // don't care about the rest

  stat_stream.close();

  long page_size_kb =
      sysconf(_SC_PAGE_SIZE) / 1024; // for x86-64 is configured  to use 2MB
                                     // pages vm_usage = vsize / 1024.0;
  resident_set = rss * page_size_kb;
}

void parse_json_file(const std::string &path) {
  // init data
  json_object *data;

  // parse json with file
  auto object = json_object_from_file(path.c_str());

  // check type
  if (json_object_object_get_ex(object, "type", &data)) {
    // print type
    std::cout << "Data type = " << json_object_get_string(data) << std::endl;
  }

  // clear mem
  json_object_put(object);
}

// main function
int main() {
  size_t count = 5;

  while (count > 0) {
    // down
    count--;

    // init data
    double vm, rss;

    // start time
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "#######################################" << std::endl;

    // print version
    std::cout << "Start to run with json-c version = " << json_c_version()
              << std::endl;

    // parse json with file
    parse_json_file(kCanadaData);

    // read mem
    mem_usage(vm, rss);

    // get duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start);

    std::cout << "Virtual Memory: " << vm << std::endl;
    std::cout << "Resident set size: " << rss << std::endl;
    std::cout << "Process run time: " << duration.count() << "ms" << std::endl;

    // sleep
    sleep(1);
  }

  return 0;
}