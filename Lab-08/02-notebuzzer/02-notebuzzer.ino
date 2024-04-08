const int buzzerPin = 17;  

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int quarterNote = 500;  

  // Play "Twinkle, Twinkle, Little Star"
  playNote(261, quarterNote);  // C
  playNote(261, quarterNote);  // C
  playNote(392, quarterNote);  // G
  playNote(392, quarterNote);  // G
  playNote(440, quarterNote);  // A
  playNote(440, quarterNote);  // A
  playNote(392, 2 * quarterNote);  // G (half note)
  delay(100);  
  playNote(349, quarterNote);  // F
  playNote(349, quarterNote);  // F
  playNote(329, quarterNote);  // E
  playNote(329, quarterNote);  // E
  playNote(294, quarterNote);  // D
  playNote(294, quarterNote);  // D
  playNote(261, 2 * quarterNote);  // C (half note)
  delay(100);  
}

void playNote(int frequency, int duration) {
  analogWrite(buzzerPin, 128);  
  tone(buzzerPin, frequency, duration); 
  delay(duration);
  analogWrite(buzzerPin, 0);  
  noTone(buzzerPin);  
  delay(50);  
}
