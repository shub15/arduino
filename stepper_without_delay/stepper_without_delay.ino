 #define STEPS 240

int dirPin1 = 24;
int dirPin2 = 26;
int pulsePin1 = 28;
int pulsePin2 = 30;
int enaPin = 32;

static uint32_t last_step_time = 0;
static uint32_t last_step_time1 = 0;
static int step_state = 0;
static int step_state1 = 0;
static int direction = 1;
int step_delay = 1;
int step_delay1 = 1;
static int stepper_running = 0;  // Toggle flag
static int stepper_running1 = 0;  // Toggle flag
static int prev_circle = 0;
static int prev_tri = 0;
static int prev_cro = 0;
static int prev_squ = 0;
static int prev_l1 = 0;
static int prev_r1 = 0;
static int prev_ll2 = 0;
static int prev_rr2 = 0;
uint32_t target_steps = 0;
uint32_t current_steps = 0;
uint32_t target_steps1 = 0;
uint32_t current_steps1 = 0;

int8_t lx, ly, rx, ry, up, down, left, right, tri, squ, circle, cross, l1, l2, r1, r2;

void setup() {
  pinMode(dirPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(pulsePin1, OUTPUT);
  pinMode(pulsePin2, OUTPUT);
  pinMode(enaPin, OUTPUT);
}

void loop() {
  digitalWrite(dirPin1,
                    direction ? HIGH : LOW);
  digitalWrite(dirPin2,
                    direction ? HIGH : LOW);

  if (l1 == 1 && !prev_l1) {  // l1 button pressed
    direction = 1;             // Set to Anti-clockwise
    stepper_running = 1;
    stepper_running1 = 1;
    target_steps = STEPS;
    target_steps1 = STEPS;
    digitalWrite(enaPin, LOW);
  }
  if (r1 == 1 && !prev_r1) {  // r1 button pressed
    direction = 0;             // Set to Clockwise
    stepper_running = 1;
    stepper_running1 = 1;
    target_steps = STEPS;
    target_steps1 = STEPS;
    digitalWrite(enaPin, LOW);
  }
  if (circle == 1 && !prev_circle) {
    stepper_running = 0;
    stepper_running1 = 0;
    current_steps = 0;
    current_steps1 = 0;
    digitalWrite(enaPin, HIGH);
  }
  prev_l1 = l1;
  prev_r1 = r1;
  prev_circle = circle;

  if (stepper_running && (millis() - last_step_time) >= step_delay
      && current_steps < target_steps) {
    last_step_time = millis();  // Update last step time

    if (step_state == 0) {
      digitalWrite(pulsePin1, HIGH);  // Step HIGH
      step_state = 1;
      current_steps++;
    } else {
      digitalWrite(pulsePin1, LOW);  // Step LOW
      step_state = 0;
    }
  }
  if (stepper_running1 && (millis() - last_step_time1) >= step_delay1
      && current_steps1 < target_steps1) {
    last_step_time1 = millis();  // Update last step time

    if (step_state1 == 0) {
      digitalWrite(pulsePin2, HIGH);  // Step HIGH
      step_state1 = 1;
      current_steps1++;
    } else {
      digitalWrite(pulsePin2, LOW);  // Step LOW
      step_state1 = 0;
    }
  }
  // Stop when target steps are reached
  if (current_steps >= target_steps) {
    stepper_running = 0;
    current_steps = 0;
    digitalWrite(enaPin, HIGH);
  }
  if (current_steps1 >= target_steps1) {
    stepper_running1 = 0;
    current_steps1 = 0;
    digitalWrite(enaPin, HIGH);
  }
}
