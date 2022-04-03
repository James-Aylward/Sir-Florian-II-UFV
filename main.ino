#include "esp_camera.h"
#include "camera_pins.h"
#include <WiFi.h>

const char *ssid = "Saint Florian II UFV";
const char *password = "goldenboys";

camera_config_t generate_camera();

void setup()
{
	// Set up serial
	Serial.begin(115200);
	Serial.setDebugOutput(true);
	Serial.println();

	// Set up camera pins and check for errors
	camera_config_t camera_config = generate_camera();
	esp_err_t err = esp_camera_init(&camera_config);
	if (err != ESP_OK)
	{
		Serial.printf("Camera init failed with error 0x%x", err);
		return;
	}

	// Set up sensors - initially flipped vertically and colors are a bit saturated
	sensor_t *s = esp_camera_sensor_get();
	s->set_vflip(s, 1);		  // flip it back
	s->set_brightness(s, 1);  // up the brightness just a bit
	s->set_saturation(s, -2); // lower the saturation
	s->set_framesize(s, FRAMESIZE_QVGA);

	// Start up WAP
	Serial.println("Starting up WAP");
	WiFi.softAP(ssid, password);

	startCameraServer();

	Serial.print("Camera Ready! Use 'http://");
	Serial.print(WiFi.localIP());
	Serial.println("' to connect");
}

void loop()
{
	delay(10000);
}

camera_config_t generate_camera()
{ 
	// Set up camera config
	camera_config_t camera_config;
	camera_config.ledc_channel = LEDC_CHANNEL_0;
	camera_config.ledc_timer = LEDC_TIMER_0;
	camera_config.pin_d0 = Y2_GPIO_NUM;
	camera_config.pin_d1 = Y3_GPIO_NUM;
	camera_config.pin_d2 = Y4_GPIO_NUM;
	camera_config.pin_d3 = Y5_GPIO_NUM;
	camera_config.pin_d4 = Y6_GPIO_NUM;
	camera_config.pin_d5 = Y7_GPIO_NUM;
	camera_config.pin_d6 = Y8_GPIO_NUM;
	camera_config.pin_d7 = Y9_GPIO_NUM;
	camera_config.pin_xclk = XCLK_GPIO_NUM;
	camera_config.pin_pclk = PCLK_GPIO_NUM;
	camera_config.pin_vsync = VSYNC_GPIO_NUM;
	camera_config.pin_href = HREF_GPIO_NUM;
	camera_config.pin_sscb_sda = SIOD_GPIO_NUM;
	camera_config.pin_sscb_scl = SIOC_GPIO_NUM;
	camera_config.pin_pwdn = PWDN_GPIO_NUM;
	camera_config.pin_reset = RESET_GPIO_NUM;
	camera_config.xclk_freq_hz = 20000000;
	camera_config.pixel_format = PIXFORMAT_JPEG;
	camera_config.frame_size = FRAMESIZE_UXGA;
	camera_config.jpeg_quality = 10;
	camera_config.fb_count = 2;

	return camera_config;
}