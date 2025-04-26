#include <Adafruit_NeoPixel.h>

// Định nghĩa chân và số lượng LED
#define LED_PIN    27    // Chân kết nối với dải LED WS2812B
#define NUM_LEDS   160   // Số lượng LED trong dải

// Khởi tạo đối tượng Adafruit_NeoPixel
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
// Hàm hỗ trợ tạo màu Rainbow
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
// Hàm tạo hiệu ứng Rainbow
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 chu kỳ màu
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


void setup() {
  // Khởi tạo dải LED
  strip.begin();
  strip.show(); // Xóa tất cả các LED (tắt)
  strip.setBrightness(50); // Đặt độ sáng (0-255)
}

void loop() {
  // Hiệu ứng Rainbow
  rainbowCycle(10); // Tốc độ hiệu ứng (ms)
}

