#include "IMLogger.h"

IMLogger::IMLogger() {
  filePath = "";
  Serial.println("log constructed");
}

IMLogger::IMLogger(String fileName) {
  setFileName(fileName);
}

void IMLogger::setAvgSizeMB(float size) {
  avgLogSize = size;
}

float IMLogger::getAvgSizeMB() {
  return avgLogSize;
}

bool IMLogger::init() {
  float averageSize;
  /* 
  if (!sd.begin(SD_CS_PIN, SPI_FULL_SPEED)) {//"SdInfo.h"
    errors->add(IMError::NO_SD_CARD);
    return false;
  }
  
  if (!enoughSpace()) {
    errors->add(IMError::NO_SD_SPACE);
    return false;
  }
  */
  //init file
  //searchFS();
  //calculate avg size
  //setAvgSizeMB(averageSize);
  setAvgSizeMB(1);
  return true;
}
/* 
bool IMLogger::enoughSpace() {
  uint32_t freeClusters = sd.vol()->freeClusterCount() / 2;
  float freeSpaceMB = (megabyteMultiplier * freeClusters) * sd.vol()->blocksPerCluster();
  return freeSpaceMB > (10 * getAvgSizeMB());
}
*/
void IMLogger::writeHeader() {

}
/*
void IMLogger::searchFS() {
  IMFile logDir = IMFile(logDirPath, (oflag_t) O_CREAT);
  IMFile file;

  if (!logDir.isDir() || logDir.getError()) {
    Serial.println("accessing log dir error code "+String(logDir.getError()));
    errors->add(IMError::NO_LOG_DIR);
    return;
  }
  logDir.rewind();

  //search and create a chart of defined number of last sessions

  while (file.openNext(&logDir)) {
    if (!file.isHidden()) {
      dir_t* dir = file.cacheDirEntry(FatCache::CACHE_FOR_READ);

      if (!dir) {
        return;//error
      }
      int i = 0;
      char name[8];
      char ext[3];//read data if ext == log
      
      uint32_t sizeB = dir->fileSize;
      float sizeMB = sizeB * megabyteMultiplier;

      uint32_t beginDate = FAT_YEAR(dir->creationDate) * 10000;
      beginDate += FAT_MONTH(dir->creationDate) * 100;
      beginDate += FAT_DAY(dir->creationDate);

      uint32_t finishDate = FAT_YEAR(dir->lastWriteDate) * 10000;
      finishDate += FAT_MONTH(dir->lastWriteDate) * 100;
      finishDate += FAT_DAY(dir->lastWriteDate);

      for (; i < 8; i++) {
        name[i] = dir->name[i];
      }
      for (int j = 0; i < 11; i++, j++) {
        ext[j] = dir->name[i];
      }

      Serial.print(name);
      Serial.print('.');
      Serial.print(ext);
      Serial.print("  ");
      Serial.print(sizeMB);
      Serial.print(" MB  ");
      Serial.print(beginDate);
      Serial.print("  ");
      Serial.println(finishDate);
    }
    file.close();
  }
}
*/
bool IMLogger::println(String line) {
  uint8_t whitespaceCount = lineLen - line.length() - 1;
  char buffer[whitespaceCount];
  //IMFile logFile;

  for (uint8_t i = 0; i < whitespaceCount; i++) {
    buffer[i] = ' ';
  }
  line += String(buffer);
  line += "/n";
  /* 
  if (logFile.open(filePath, (oflag_t) O_WRONLY)) {//errors? // O_APPEND?
    int bytesWritten = logFile.write((char*)line.c_str(), lineLen);
    bool closed = logFile.close();
    return (bytesWritten == lineLen) && closed;
  }
  */
  return false;
}

void IMLogger::setFileName(String name) {
  String str = String(logDirPath) + name;
  filePath = (char*) str.c_str();
}

void IMLogger::setErrorList(IMErrors * list) {
  errors = list;
}
