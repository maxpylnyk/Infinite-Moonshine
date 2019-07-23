#ifndef IM_FILE_H
#define IM_FILE_H

#include "SdFat.h"

class IMFile : public SdFile {
  private:

  public:
    IMFile() : SdFile() {}
    IMFile(const char * path, oflag_t oflag) : SdFile(path, oflag) {}

    uint32_t getSize();
    uint32_t getSessionName();
    uint32_t getStartDate();
    uint32_t getEndDate();
    bool isLog();

};

#endif
