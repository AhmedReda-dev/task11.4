// Note: 
// - I couldnt test the PID values
// - I am not sure about how to get the speed from the Encoder

// PID parameters
double kp = 2;
double ki = 4;
double kd = 2;

// Motor control pins
const int enb = 6;
const int in1 = 3;
const int in2 = 4;

// Encoder input pin
const int inputPin = 0;


int wantedSpeed = 800;

// PID variables
double error, integral, derivative, output;
double lastError = 0;
double lastTime = 0;

// filter parameters
const double alpha = 0.05; 
double filteredValue = 0;

void setup() {
  pinMode(enb, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // read the encoder value
  int encoderValue = analogRead(inputPin);

  // filter the encoder value
  filteredValue = alpha * encoderValue + (1 - alpha) * filteredValue;

  // error calculation
  error = wantedSpeed - filteredValue;

  // Calculate time difference
  double now = millis();
  double dt = (now - lastTime) / 1000.0;
  lastTime = now;

  // PID output
  integral += error * dt; // Integral formula
  derivative = (error - lastError) / dt; // Drivative formula
  lastError = error; // save the last error for the loop

  output = kp * error + ki * integral + kd * derivative; // calculate the output

  // write motor speed
  analogWrite(enb, output);

  delay(10);
}

