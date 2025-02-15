/*
  SonicBoom.ino - ESP32 Web Server
  Features: Motor Control, Servo Handling, Real-Time UI Updates
*/

#include <WiFi.h>
#include <WebServer.h>
#include "MotorControl.h"
#include "ServoControl.h"
#include "StateManager.h"

// WiFi credentials – update with your actual SSID & Password
const char* ssid = "YourSSID";
const char* password = "YourPassword";

// Create a web server on port 80
WebServer server(80);

// Define motor pins
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

// Function declarations
void handleRoot();
void handleForward();
void handleBackward();
void handleLeft();
void handleRight();
void handleStop();
void handleServoHold();
void handleServoRelease();
void handleStatus();

void setup() {
  Serial.begin(115200);

  // Initialize motor and servo modules
  motorControl.init();
  servoControl.init();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected! IP address: " + WiFi.localIP().toString());

  // Define web server routes
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/stop", handleStop);
  server.on("/servoHold", handleServoHold);
  server.on("/servoRelease", handleServoRelease);
  server.on("/status", handleStatus);

  // Start server
  server.begin();
  Serial.println("Web server started!");
}

void loop() {
  server.handleClient();
}

// 🟢 Main UI Served to Clients
void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>SONIC BOOM Control Panel</title>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
  <script src="https://cdn.tailwindcss.com"></script>
  <script src="https://unpkg.com/lucide@latest"></script>
  <style>
    body {
      font-family: "IBM Plex Mono", monospace;
      background: #f5e6d3;
      background-image: radial-gradient(#2c1810 1px, transparent 1px),
        radial-gradient(#2c1810 1px, transparent 1px);
      background-size: 20px 20px;
      background-position: 0 0, 10px 10px;
    }
    .round-button {
      border-radius: 50%;
      aspect-ratio: 1;
    }
  </style>
</head>
<body class="min-h-screen p-4">
  <div class="max-w-md mx-auto">
    <div class="bg-[#dcc7b5] rounded-xl shadow-lg p-6 border-2 border-[#8b4513]">
      
      <!-- Decorative Plant -->
      <div class="flex justify-center mb-4">
        <svg viewBox="0 0 100 100" class="w-24 h-24 text-green-800">
          <path d="M50,90 C50,90 80,60 50,30 C20,60 50,90 50,90" fill="#496b46"/>
          <rect x="48" y="80" width="4" height="20" fill="#8b4513"/>
        </svg>
      </div>

      <h1 class="text-3xl font-serif text-center text-[#2c1810] mb-6">SONIC BOOM</h1>
      
      <div class="bg-[#c4a484] rounded-lg p-4 mb-6">
        <p class="text-lg text-center text-[#2c1810]">
          Status: <span id="state" class="font-mono font-bold">IDLE</span>
        </p>
      </div>

      <!-- Control Buttons -->
      <div class="grid grid-cols-3 gap-4 mb-6">
        <div></div>
        <button onclick="location.href='/forward'" class="round-button bg-[#8b4513] hover:bg-[#6b3410] p-4">
          <i data-lucide="arrow-up"></i>
        </button>
        <div></div>

        <button onclick="location.href='/left'" class="round-button bg-[#8b4513] hover:bg-[#6b3410] p-4">
          <i data-lucide="arrow-left"></i>
        </button>
        <button onclick="location.href='/stop'" class="round-button bg-[#a52a2a] hover:bg-[#8b0000] p-4">
          <i data-lucide="square"></i>
        </button>
        <button onclick="location.href='/right'" class="round-button bg-[#8b4513] hover:bg-[#6b3410] p-4">
          <i data-lucide="arrow-right"></i>
        </button>

        <div></div>
        <button onclick="location.href='/backward'" class="round-button bg-[#8b4513] hover:bg-[#6b3410] p-4">
          <i data-lucide="arrow-down"></i>
        </button>
        <div></div>
      </div>

      <div class="grid grid-cols-2 gap-4">
        <button onclick="location.href='/servoHold'" class="bg-[#556b2f] hover:bg-[#3b4a1f] p-4">
          <i data-lucide="lock"></i> Hold
        </button>
        <button onclick="location.href='/servoRelease'" class="bg-[#556b2f] hover:bg-[#3b4a1f] p-4">
          <i data-lucide="unlock"></i> Release
        </button>
      </div>
    </div>
  </div>

  <script>
    lucide.createIcons();
    setInterval(() => { $.get("/status", data => { $("#state").text(data); }); }, 1000);
  </script>
</body>
</html>
)rawliteral";
  server.send(200, "text/html", html);
}

// Control Routes
void handleForward() { stateManager.setState(MOVING); motorControl.moveForward(); server.send(200, "text/plain", "Moving Forward"); }
void handleBackward() { stateManager.setState(MOVING); motorControl.moveBackward(); server.send(200, "text/plain", "Moving Backward"); }
void handleLeft() { stateManager.setState(MOVING); motorControl.turnLeft(); server.send(200, "text/plain", "Turning Left"); }
void handleRight() { stateManager.setState(MOVING); motorControl.turnRight(); server.send(200, "text/plain", "Turning Right"); }
void handleStop() { stateManager.setState(IDLE); motorControl.stopMotors(); server.send(200, "text/plain", "Stopped"); }
void handleServoHold() { stateManager.setState(SERVO_ACTION); servoControl.holdCube(); server.send(200, "text/plain", "Cube Held"); }
void handleServoRelease() { stateManager.setState(SERVO_ACTION); servoControl.releaseCube(); server.send(200, "text/plain", "Cube Released"); }
void handleStatus() { server.send(200, "text/plain", stateManager.getStateString()); }
