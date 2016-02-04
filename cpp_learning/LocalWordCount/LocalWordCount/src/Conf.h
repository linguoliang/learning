#ifndef CONF_H_
#define CONF_H_

#include <string>

class Conf {
 public:
  Conf(std::string confPath);
  ~Conf() {}

  // private:
  std::string fetchedPath_;
  std::string logPath_;
  std::string resPath_;
  std::string dictPath_;
  std::string modelPath_;
  std::string userDictPath_;
  std::string idfPath_;
  std::string stopWordPath_;
};

#endif /* ifndef CONF_H_ */
