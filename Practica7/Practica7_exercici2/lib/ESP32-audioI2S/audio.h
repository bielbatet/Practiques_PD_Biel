
#ifndef AUDIO_H
#define AUDIO_H

#include <Arduino.h>
#include <FS.h>

class Audio {
public:
  Audio() {}
  void setPinout(uint8_t bclk, uint8_t lrc, uint8_t dout) {}
  void setVolume(uint8_t vol) {}
  void connecttoFS(fs::FS &fs, const char *path) {}
  void loop() {}
};

#endif
