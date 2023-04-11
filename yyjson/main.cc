#include <unistd.h>
#include <yyjson.h>

#include <chrono>
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
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
      starttime >> vsize >> rss; // don't care about the rest

  stat_stream.close();

  long page_size_kb =
      sysconf(_SC_PAGE_SIZE) / 1024; // for x86-64 is configured  to use 2MB
                                     // pages vm_usage = vsize / 1024.0;
  resident_set = rss * page_size_kb;
}

void parse_json_file(const std::string &path) {
  // read document
  auto doc = yyjson_read_file(path.c_str(), 0, NULL, NULL);

  if (doc != nullptr) {
    // get root
    auto root = yyjson_doc_get_root(doc);
    auto type = yyjson_obj_get(root, "type");

    std::cout << "Data type = " << yyjson_get_str(type) << std::endl;

    // Free the doc
    yyjson_doc_free(doc);
  }
}

void parse_device_list(const std::string &path) {
  // read document
  auto doc = yyjson_read_file(path.c_str(), 0, NULL, NULL);

  if (doc != nullptr) {
    // init data
    // std::map<std::string, yyjson_val *> attributes;

    // get root
    auto root = yyjson_doc_get_root(doc);
    auto data = yyjson_obj_get(root, "data");
    auto home_id = yyjson_obj_get(root, "home_id");

    if (yyjson_is_str(home_id)) {
      std::cout << "Home id = " << yyjson_get_str(home_id) << std::endl;
    }

    if (yyjson_is_ctn(data)) {
      // get device list
      auto device_list = yyjson_obj_get(data, "device_list");

      if (yyjson_is_ctn(device_list)) {
        // print device count
        std::cout << "Total device = " << yyjson_get_len(device_list)
                  << std::endl;
      }

      // yyjson_val *val;
      // yyjson_arr_iter iter;
      // yyjson_arr_iter_init(device_list, &iter);
      // while ((val = yyjson_arr_iter_next(&iter))) {
      //   auto profile = yyjson_obj_get(val, "device_profile");
      //   auto device_id = yyjson_obj_get(profile, "device_id");
      //   attributes.emplace(yyjson_get_str(device_id), val);
      // }

      // for (const auto &att : attributes) {
      //   auto out = yyjson_mut_doc_new(NULL);
      //   auto device = yyjson_val_mut_copy(out, att.second);
      //   yyjson_mut_doc_set_root(out, device);

      //   auto json = yyjson_mut_write(out, 0, NULL);

      //   std::cout << att.first << " = " << json << std::endl;

      //   free(json);
      //   yyjson_mut_doc_free(out);
      // }
    }

    auto json = yyjson_write(doc, 0, NULL);

    std::cout << json << std::endl;

    free(json);

    // Free the doc
    yyjson_doc_free(doc);
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
    std::cout << "Start to run with yyjson version = 0.6.0" << std::endl;

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