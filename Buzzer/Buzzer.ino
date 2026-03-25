//defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int buzzer= 11;
const int ledPin = 13;

// defines variables
// defines variables
// defines variables
long duration;
int distance;
int safetyDistance;


void setup() {
  pinMode(trigPin, OUTPUT); //Sets the trigPin as an Output
  pinMode(echoPin, INPUT); //Sets the echoPin as an Input
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); //starts the serial communication
}

void loop() {
  // Proper trigger signal
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance
  distance = duration * 0.034 / 2;

  // Condition
  if (distance <= 10 && distance > 0) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(ledPin, LOW);
  }

  Serial.print("Distance: ");
  Serial.println(distance);

  delay(200); // small delay for stability
}