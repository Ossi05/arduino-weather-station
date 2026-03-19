#include "Screen.h"
#include "Config.h"

Screen::Screen(Config::ScreenConfig config)
  : lcd{ config.rs, config.e, config.d4, config.d5, config.d6, config.d7 }, cols{ config.cols }, rows{ config.rows } {
  lcd.begin(cols, rows);
}

void Screen::clear() {
  lcd.clear();
}

void Screen::printLine(const String& msg, int startRow) {
  // 1. Check that we aren't out of bounds
  if (startRow < 0 || startRow >= rows) return;

  // 2. Move the cursor to the beginning of the target row
  lcd.setCursor(0, startRow);

  // 3. Print the message up to the maximum number of columns
  String lineText = msg.substring(0, cols);
  lcd.print(lineText);

  // 4. Fill rest of the cols with empty spaces
  for (unsigned int i = lineText.length(); i < (unsigned int)cols; i++) {
    lcd.print(" ");
  }
}

void Screen::printWrapped(const String& message, int startRow) {
  // 1. Check that we aren't out of bounds
  if (startRow < 0 || startRow >= rows) return;

  // 2. Calculate how many rows are available for printing
  int availableRows = rows - startRow;

  // 3. Loop through the message and print it in chunks that fit the screen
  for (int i = 0; i < availableRows; i++) {
    int currentRow = startRow + i;
    unsigned int startIdx = i * cols;

    // 4. Print the current chunk of text
    if (startIdx < message.length()) {
      printLine(message.substring(startIdx), currentRow);
      continue;
    }

    // If we've run out of text, clear the remaining lines
    printLine("", currentRow);
  }
}