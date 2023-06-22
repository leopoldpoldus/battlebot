#define CH1 10
#define CH2 11

// Integers to represent values from sticks and pots
int ch1Value;
int ch2Value;


// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}


// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;

// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

int motorADir = 1;
int motorBDir = 1;
int MotorSpeedA = 0;
int MotorSpeedB = 0;

void setup() {
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, 0);
  MotorSpeedA = 0;
  MotorSpeedB = 0;
  
  
  
  if (ch1Value >= 0) {
    motorADir = 1;
    motorBDir = 1;
  } else {
    motorADir = 0;
    motorBDir = 0;
  }

  MotorSpeedA = MotorSpeedA +  abs(ch1Value);
  MotorSpeedB = MotorSpeedB +  abs(ch1Value);

  MotorSpeedB = MotorSpeedB - ch2Value;
  MotorSpeedA = MotorSpeedA + ch2Value;

  
  

  mControlA(map(abs(MotorSpeedA), 0, 100, 0, 255), motorADir);
  mControlB(map(abs(MotorSpeedB), 0, 100, 0, 255), motorBDir);
  
  
}

void mControlA(int mspeed, int mdir) {

  // Determine direction
  if (mdir == 0) {
    // Motor backward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else {
    // Motor forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }

  // Control motor
  analogWrite(enA, mspeed);

}

void mControlB(int mspeed, int mdir) {

  // Determine direction
  if (mdir == 0) {
    // Motor backward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  } else {
    // Motor forward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }

  // Control motor
  analogWrite(enB, mspeed);

}
