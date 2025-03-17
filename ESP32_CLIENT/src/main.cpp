#include <WiFi.h>
#include <HTTPClient.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>
//#include <WiFiEsp.h>
// Khai báo prototype cho các hàm được sử dụng trước khi định nghĩa
void parseStr(const String& str);
void run_servo(int value);

// Định nghĩa thông tin kết nối WiFi và MQTT
const char *ssid =  "Wokwi-GUEST";
const char *pswrd = "";
const char *mqtt_server = "192.168.26.42";
// const char *mqtt_server = "192.168.122.1";

// Định nghĩa chân kết nối cho các thiết bị ngoại vi
const int tempPin   = 32;
const int presPin   = 33;
const int airPin    = 12;
const int lightPin  = 14;

Servo myServo; // Tạo đối tượng servo
int servoPin = 13;

// Khởi tạo đối tượng WiFi và MQTT client
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pswrd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void reconnect() {
  // Vòng lặp cho đến khi kết nối MQTT thành công
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Cố gắng kết nối
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      // Subscribe vào topic từ broker
      client.subscribe("esp/cmd");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000); // Thử kết nối lại sau 5 giây
    }
  }
}

// Hàm callback xử lý tin nhắn đến từ MQTT
void callback(char *topic, byte *payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  // Kiểm tra topic nhận được
  if (String(topic) == "esp/cmd") {
    Serial.println("Received message: " + message);
    // Xử lý lệnh nhận được
    parseStr(message);
  }
}

// Hàm điều khiển servo dựa trên giá trị nhận được
void run_servo(int value) {
  if (value == 0) {
    myServo.write(0);
  } else {
    myServo.write(180);
  }
}

// Hàm xử lý chuỗi lệnh nhận được
void parseStr(const String& str) {
  // Tìm vị trí dấu phẩy
  int commaIndex = str.indexOf(',');

  // Tách tên cảm biến và trạng thái
  String sensorName = str.substring(0, commaIndex);
  int pinState = str.substring(commaIndex + 1).toInt();
  Serial.println("sensorName -> " + sensorName + ", pinState -> " + String(pinState));

  // Xử lý theo tên cảm biến
  if (sensorName == "temperature") {
    digitalWrite(tempPin, pinState);
  } else if (sensorName == "pressure") {
    digitalWrite(presPin, pinState);
  } else if (sensorName == "air") {
    // Nếu nhận lệnh từ cảm biến "air" thì điều khiển servo
    run_servo(pinState);
  } else if (sensorName == "light") {
    digitalWrite(lightPin, pinState);
  } else {
    Serial.println("Unknown sensor name");
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  myServo.attach(servoPin); // Gắn servo vào chân chỉ định

  // Đặt các chân ngoại vi là OUTPUT
  pinMode(tempPin, OUTPUT);
  pinMode(presPin, OUTPUT);
  pinMode(airPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Lưu ý: Dòng gọi run_servo() không có tham số đã bị xóa vì hàm run_servo yêu cầu 1 tham số.
  // Nếu bạn muốn kiểm tra servo tại đây, hãy gọi run_servo với tham số phù hợp, ví dụ:
  // run_servo(1);

  // Giả lập đọc giá trị cảm biến
  float temperature = random(0, 100) + random(0, 100) / 100.0;
  float pressure = random(0, 1000) + random(0, 100) / 100.0;
  float airQuality = random(0, 500) + random(0, 100) / 100.0;
  float light = random(0, 100) + random(0, 100) / 100.0;

  // Gộp các giá trị cảm biến thành chuỗi, phân tách bằng dấu phẩy
  String payload = String(temperature) + "," +
                   String(pressure) + "," +
                   String(airQuality) + "," +
                   String(light);

  // Publish dữ liệu cảm biến lên MQTT topic
  client.publish("home/sensors/data", payload.c_str());
  Serial.print("Sensor data sent: ");
  Serial.println(payload);

  delay(5000); // Gửi dữ liệu sau mỗi 5 giây
}

