#include "App.h"

App app{};

void setup() {
  Serial.begin(9600);
  app.setup();
}

void loop() {
    app.loop();
}