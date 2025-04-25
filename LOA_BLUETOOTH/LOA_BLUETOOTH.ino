#include "BluetoothA2DPSink.h"
#include "Audio.h"
// Các chân I2S
#define I2S_BCLK  27  // Chân Bit Clock (BCLK)
#define I2S_LRC   26  // Chân Left-Right Clock (LRCK)
#define I2S_DOUT  25  // Chân Data Out (DOUT)
// Khai báo đối tượng Audio và Bluetooth A2DP Sink
Audio audio;
BluetoothA2DPSink a2dp_sink;
// Hàm cấu hình I2S
void setupI2S() {
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);  // Cấu hình chân I2S
  audio.setVolume(30);  // Cài đặt âm lượng cho đầu ra
}
void setup() {
  Serial.begin(115200);
  // Khởi tạo Bluetooth A2DP Sink
  a2dp_sink.set_auto_reconnect(true);
  a2dp_sink.start("ESP32_BT_Loudspeaker");  // Tên loa Bluetooth
  
  // Thiết lập I2S
  setupI2S();
  
  // Đảm bảo loa phát âm thanh khi nhận được tín hiệu Bluetooth
  a2dp_sink.set_stream_reader(stream_reader);
  Serial.println("ESP32 đã sẵn sàng làm loa Bluetooth!");
}
void loop() {
  // Không cần làm gì trong vòng lặp chính
  // Bluetooth tự động xử lý kết nối và phát âm thanh
}
// Hàm xử lý dữ liệu âm thanh từ Bluetooth và phát qua I2S
void stream_reader(const uint8_t *data, size_t len) {
  // Chuyển đổi dữ liệu âm thanh nhận được từ Bluetooth A2DP thành dữ liệu I2S
  audio.loop();  // Hàm này sẽ xử lý dữ liệu âm thanh và phát ra qua I2S
  // Bạn có thể thêm các xử lý tùy chỉnh nếu cần
}
