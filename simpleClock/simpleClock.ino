#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>
#include <VFDTube.h>

#define TUBE_COUNT 6

VFDTube tube(7, 6, 5, 4, TUBE_COUNT);

void setup() {
  Wire.begin();
  tube.setBrightness(0xff);
  Serial.begin(9600);
  tube.setBackgroundColor(White);
  tube.printf(" hello");
  tube.display();
  delay(3000);
}

void loop() {
  tmElements_t tm;

  //Colors = { White, Yellow, Magenta, Red, Cyan, Green, Blue, Black }
  tube.setBackgroundColor(0, Blue);
  tube.setBackgroundColor(1, Blue);
  tube.setBackgroundColor(2, Blue);
  tube.setBackgroundColor(3, Blue);
  tube.setBackgroundColor(4, Red);
  tube.setBackgroundColor(5, Red);

  if (RTC.read(tm)) {

    if (tm.Hour > 12) {
      tm.Hour -= 12;
    }

    tube.printf("%02d.%02d.%02d", tm.Hour, tm.Minute, tm.Second);
    tube.display();
    Serial.println(tm.Hour);
    delay(1000);
  } else {
    if (RTC.chipPresent()) {
      tube.printf(" error");
      tube.display();
      delay(1000);
    } else {
      tube.printf(" error");
      tube.display();
      delay(1000);
    }
    delay(9000);
  }
}
