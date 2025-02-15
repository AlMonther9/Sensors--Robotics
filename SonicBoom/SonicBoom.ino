/*
  SonicBoom.ino
  Main file integrating motor control, servo control, state management,
  and an artistic web-based UI for real-time feedback.
*/

#include <WiFi.h>
#include <WebServer.h>
#include "MotorControl.h"
#include "ServoControl.h"
#include "StateManager.h"

// WiFi credentials – update these with your network details
const char* ssid = "YourSSID";
const char* password = "YourPassword";

// Create a web server on port 80
WebServer server(80);

// Define hardware pins:
// Motor pins (H-bridge)
const uint8_t MOTOR1A = 16;
const uint8_t MOTOR1B = 17;
const uint8_t MOTOR2A = 18;
const uint8_t MOTOR2B = 19;
const uint8_t MOTOR3A = 21;
const uint8_t MOTOR3B = 22;
const uint8_t MOTOR4A = 23;
const uint8_t MOTOR4B = 5;

// Servo pin
const uint8_t SERVO_PIN = 15;

// Instantiate modules
MotorControl motorControl(MOTOR1A, MOTOR1B, MOTOR2A, MOTOR2B,
                          MOTOR3A, MOTOR3B, MOTOR4A, MOTOR4B);
ServoControl servoControl(SERVO_PIN);
StateManager stateManager;

// Forward declarations for route handlers
void handleRoot();
void handleStart();
void handleBackward();
void handleLeft();
void handleRight();
void handleStop();
void handleServoHold();
void handleServoRelease();
void handleStatus();

void setup() {
  Serial.begin(115200);

  // Initialize hardware modules
  motorControl.init();
  servoControl.init();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Define web server routes
  server.on("/", handleRoot);
  server.on("/start", handleStart);         // Forward
  server.on("/backward", handleBackward);     // Backward
  server.on("/left", handleLeft);             // Turn left
  server.on("/right", handleRight);           // Turn right
  server.on("/stop", handleStop);             // Stop
  server.on("/servoHold", handleServoHold);   // Hold cube
  server.on("/servoRelease", handleServoRelease); // Release cube
  server.on("/status", handleStatus);

  // Start the web server
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}

// Main UI served with Tailwind CSS for an artistic, nature-inspired design
void handleRoot() {
  String html = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>SONIC BOOM Control Panel</title>";
  // Include Tailwind CSS from CDN
  html += "<script src='https://cdn.tailwindcss.com'></script>";
  // Custom styling to evoke coffee, plants, and nature
  html += "<style>body { background: linear-gradient(135deg, #4b3621, #a1866f); } </style>";
  html += "</head><body class='text-white'>";
  html += "<div class='container mx-auto py-10'>";
  html += "<div class='bg-gray-800 bg-opacity-75 rounded-lg shadow-lg p-8'>";
  html += "<h1 class='text-4xl font-bold mb-4'>SONIC BOOM Control Panel</h1>";
  html += "<p class='text-lg mb-6'>Current State: <span id='state' class='font-mono'>" + stateManager.getStateString() + "</span></p>";
  html += "<div class='grid grid-cols-2 gap-4'>";
  html += "<button class='bg-green-500 hover:bg-green-600 text-white font-bold py-2 px-4 rounded' onclick=\"location.href='/start'\">Forward</button>";
  html += "<button class='bg-blue-500 hover:bg-blue-600 text-white font-bold py-2 px-4 rounded' onclick=\"location.href='/backward'\">Backward</button>";
  html += "<button class='bg-yellow-500 hover:bg-yellow-600 text-white font-bold py-2 px-4 rounded' onclick=\"location.href='/left'\">Left</button>";
  html += "<button class='bg-purple-500 hover:bg-purple-600 text-white font-bold py-2 px-4 rounded' onclick=\"location.href='/right'\">Right</button>";
  html += "<button class='bg-red-500 hover:bg-red-600 text-white font-bold py-2 px-4 rounded' onclick=\"location.href='/stop'\">Stop</button>";
  html += "<button class='bg-indigo-500 hover:bg-indigo-600 text-white font-bold py-2 px-4 rounded' onclick=\"location.href='/servoHold'\">Hold Cube</button>";
  html += "<button class='bg-pink-500 hover:bg-pink-600 text-white font-bold py-2 px-4 rounded' onclick=\"location.href='/servoRelease'\">Release Cube</button>";
  html += "</div></div></div>";
  // jQuery for real-time state updates (polling every second)
  html += "<script src='https://code.jquery.com/jquery-3.5.1.min.js'></script>";
  html += "<script>setInterval(function() { $.get('/status', function(data) { $('#state').text(data); }); }, 1000);</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

// Route: Move forward
void handleStart() {
  stateManager.setState(MOVING);
  motorControl.moveForward();
  server.send(200, "text/plain", "Robot moving forward!");
}

// Route: Move backward
void handleBackward() {
  stateManager.setState(MOVING);
  motorControl.moveBackward();
  server.send(200, "text/plain", "Robot moving backward!");
}

// Route: Turn left
void handleLeft() {
  stateManager.setState(MOVING);
  motorControl.turnLeft();
  server.send(200, "text/plain", "Robot turning left!");
}

// Route: Turn right
void handleRight() {
  stateManager.setState(MOVING);
  motorControl.turnRight();
  server.send(200, "text/plain", "Robot turning right!");
}

// Route: Stop all movement
void handleStop() {
  stateManager.setState(IDLE);
  motorControl.stopMotors();
  server.send(200, "text/plain", "Robot stopped!");
}

// Route: Hold cube (servo action)
void handleServoHold() {
  stateManager.setState(SERVO_ACTION);
  servoControl.holdCube();
  stateManager.setState(IDLE);
  server.send(200, "text/plain", "Cube held!");
}

// Route: Release cube (servo action)
void handleServoRelease() {
  stateManager.setState(SERVO_ACTION);
  servoControl.releaseCube();
  stateManager.setState(IDLE);
  server.send(200, "text/plain", "Cube released!");
}

// Route: Return current state for real-time UI updates
void handleStatus() {
  server.send(200, "text/plain", stateManager.getStateString());
}
