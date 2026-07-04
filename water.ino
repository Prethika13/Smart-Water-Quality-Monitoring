#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD address (0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

int sensorPin = A0;     
int turbidityValue = 0;

void setup() {
  lcd.init();          
  lcd.backlight();     
  Serial.begin(9600);  
}

void loop() {

  // 📊 Take average for stable reading
  int total = 0;
  for (int i = 0; i < 10; i++) {
    total += analogRead(sensorPin);
    delay(10);
  }
  turbidityValue = total / 10;

  // 🖥 Serial Monitor Output
  Serial.print("Turbidity: ");
  Serial.println(turbidityValue);

  // 📟 LCD Display
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Turb:");
  lcd.print(turbidityValue);

  lcd.setCursor(0, 1);

  // ✅ CORRECTED LOGIC (as per your requirement)
  if (turbidityValue < 550) {
    lcd.print("Status: UNSAFE");
  }
  else if (turbidityValue >= 550 && turbidityValue <= 650) {
    lcd.print("Status: NO WATER");
  }
  else {
    lcd.print("Status: SAFE");
  }

  delay(2000);
}
