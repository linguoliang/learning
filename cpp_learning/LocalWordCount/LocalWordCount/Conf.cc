#include "Conf.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "json/json.hpp"
#include "Util.h"

using std::cout;
using std::ctime;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;

using json = nlohmann::json;

Conf::Conf(std::string confPath) {
  if (confPath.size() <= 0) {
    cout << "conf path isn't set" << endl;
    return;
  }

  ifstream ifs;
  ifs.open(confPath, ifstream::in);

  json j;
  ifs >> j;

  //string fetchedFolder = j["fetched folder"];
  fetchedPath_ =
    "D:\\Documents\\GitHub\\learning\\cpp_learning\\LocalWordCount\\RunningData\\fetched\\CrawlerData_2016-01-30_13-22-32.txt";

  string logFolder = trimTail(j["log folder"], "\\");
  time_t t = time(nullptr);
  stringstream buffer;
  buffer << std::put_time(localtime(&t), "\\WordCountLog_%F_%H-%M-%S");
  logPath_ = logFolder + buffer.str() + ".txt";

  string dictFolder = trimTail(j["dict folder"], "\\");
  dictPath_ = dictFolder + "\\jieba.dict.utf8";
  modelPath_ = dictFolder + "hmm_model.utf8";
  userDictPath_ = dictFolder + "user.dict.utf8";
}