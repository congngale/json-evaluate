#include "rapidjson/writer.h"
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <unistd.h>

#include <chrono>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

// define data
constexpr auto kCanadaData = "../data/canada.json";
constexpr auto kDeviceList = "../data/device_list.json";

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
      starttime >> vsize >>
      rss; // don't care about the rest stat_stream.close();

  long page_size_kb =
      sysconf(_SC_PAGE_SIZE) / 1024; // for x86-64 is configured  to use 2MB
                                     // pages vm_usage = vsize / 1024.0;
  resident_set = rss * page_size_kb;
}

void parse_json_file(const std::string &path) {
  // open file
  std::ifstream file(path.c_str());

  if (file.is_open()) {
    // parse json with file
    rapidjson::Document document;
    rapidjson::IStreamWrapper stream{file};

    // parse stream
    document.ParseStream(stream);

    // check type
    if (document.HasMember("type")) {
      // print type
      std::cout << "Data type = " << document["type"].GetString() << std::endl;
    }
  }
}

void parse_device_list(const std::string &path) {
  // open file
  std::ifstream file(path.c_str());

  if (file.is_open()) {
    // parse json with file
    rapidjson::Document document;
    rapidjson::IStreamWrapper stream{file};

    // parse stream
    document.ParseStream(stream);

    // check home id
    if (document.HasMember("home_id")) {
      // print home id
      std::cout << "Home id = " << document["home_id"].GetString() << std::endl;
    }

    // check data
    if (document.HasMember("data")) {
      // get data
      auto data = document["data"].GetObject();

      // check device list
      if (data.HasMember("device_list") && data["device_list"].IsArray()) {

        // print device count
        std::cout << "Total device = " << data["device_list"].Size()
                  << std::endl;
      }
    }

    rapidjson::StringBuffer sb;
    rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
    document.Accept(writer);

    std::cout << sb.GetString() << std::endl;
  }
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
    std::cout << "Start to run with rapidjson v1.1.0" << std::endl;

    // parse json with file
    // parse_json_file(kCanadaData);
    parse_device_list(kDeviceList);

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