#include <Wire.h>

int angle = 30;

int STEPS = angle/0.3;

int dirPin = 25;
int enaPin = 27;
int stepPin = 29;

static uint32_t last_step_time = 0;
static uint32_t last_step_time1 = 0;
static int step_state = 0;
static int step_state1 = 0;
static int direction = 1;
int step_delay = 1;
int step_delay1 = 1;
static int stepper_running = 0;   // Toggle flag
static int stepper_running1 = 0;  // Toggle flag
static int ebike_running = 0;     // Toggle flag
static int prev_cir = 0;
static int prev_tri = 0;
static int prev_cro = 0;
static int prev_squ = 0;
static int prev_l2 = 0;
static int prev_r2 = 0;
static int prev_ll2 = 0;
static int prev_rr2 = 0;
uint32_t target_steps = 0;
uint32_t current_steps = 0;
uint32_t drib_speed = 70;

int lx, ly, rx, ry, tri, cir, cro, squ, l2, r2;

void setup() {
  Serial.begin(115200);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  pinMode(dirPin, OUTPUT);
  pinMode(enaPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
}

void receiveEvent(int bytes) {
  while (Wire.available()) {
    lx = Wire.read();
    ly = Wire.read();
    rx = Wire.read();
    ry = Wire.read();
    tri = Wire.read();
    cir = Wire.read();
    cro = Wire.read();
    squ = Wire.read();
    l2 = Wire.read();
    r2 = Wire.read();
  }
}

void loop() {
  Serial.print(l2);
  Serial.println(r2);

  /* Stepper */
  digitalWrite(dirPin,
               direction ? HIGH : LOW);

  if (l2 == 1 && !prev_l2) {  // l2 button pressed
    direction = 1;            // Set to Anti-clockwise
    stepper_running = 1;
    target_steps = STEPS;
    digitalWrite(enaPin, LOW);
  }
  if (r2 == 1 && !prev_r2) {  // r2 button pressed
    direction = 0;            // Set to Clockwise
    stepper_running = 1;
    target_steps = STEPS;
    digitalWrite(enaPin, LOW);
  }
  if (cir == 1 && !prev_cir) {
    stepper_running = 0;
    stepper_running1 = 0;
    current_steps = 0;
    digitalWrite(enaPin, HIGH);
  }
  prev_l2 = l2;
  prev_r2 = r2;
  prev_cir = cir;

  if (stepper_running && (millis() - last_step_time) >= step_delay
      && current_steps < target_steps) {
    last_step_time = millis();  // Update last step time

    if (step_state == 0) {
      digitalWrite(stepPin, HIGH);  // Step HIGH
      step_state = 1;
      current_steps++;
    } else {
      digitalWrite(stepPin, LOW);  // Step LOW
      step_state = 0;
    }
  }

  // Stop when target steps are reached
  if (current_steps >= target_steps) {
    stepper_running = 0;
    current_steps = 0;
    digitalWrite(enaPin, HIGH);
  }
}
