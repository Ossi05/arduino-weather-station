#include "App.h"

App app{};

void setup() {
  Serial.begin(9600);
}

void loop() {
    app.update();
}