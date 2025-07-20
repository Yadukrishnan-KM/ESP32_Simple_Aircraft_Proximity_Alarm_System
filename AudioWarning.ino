// Audio playing function from .h file using internal DAC
void AudioWarning(const uint8_t* data, size_t len, int rate) {
  int delayMicros = 1000000 / rate;

  for (size_t i = 0; i < len; i++) {
    dacWrite(dacPin, data[i]);
    delayMicroseconds(delayMicros);
  }

  dacWrite(dacPin, 0); // mute
}
