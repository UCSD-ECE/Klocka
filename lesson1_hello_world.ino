void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.print("Hello");
  Serial.print("\n"); //Prints a new line
  delay(2000);
  Serial.print("World");
  Serial.print("\n"); //Prints a new line
  delay(2000);

}
