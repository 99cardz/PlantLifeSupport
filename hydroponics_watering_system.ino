int water_level_analog_in = A1;
int supply_pump = 3; // PIN 3 
int air_pump = 6; //PIN 2
int air_pump_interval = 10;
int floating_switch = 10;
int pump_on_time = 5; //sec

int water_level_analog_reading = 0;
int water_level_count = 0;
long timer = 0;
long air_pump_counter = 0;
int air_pump_state = LOW;
void setup() {
        Serial.begin(9600);
        pinMode(air_pump, OUTPUT);
        pinMode(supply_pump, OUTPUT);
        pinMode(floating_switch, OUTPUT);
        digitalWrite(floating_switch, LOW);
        digitalWrite(9, HIGH);
}
void serial() {
        Serial.print(timer);  Serial.println(" timer");
        Serial.print(water_level_analog_reading); Serial.println(" analog_reading");
        Serial.print(water_level_count);  Serial.println(" water_level_count");
        Serial.print(air_pump_counter);Serial.println(" air_pump_counter");
        Serial.print(air_pump_state);Serial.println(" air_pump_state");
        Serial.println("---");
        
        
}
void loop() {
        digitalWrite(floating_switch, HIGH);
        water_level_analog_reading = analogRead(water_level_analog_in);
      	water_level_analog_reading = analogRead(water_level_analog_in);
        digitalWrite(floating_switch, LOW);
        if (water_level_analog_reading < 10) {water_level_count ++;}
        else { water_level_count = 0; }
        serial();
        if (water_level_count >= 20) { //Turn on supply Pump
          digitalWrite(air_pump, LOW);
          digitalWrite(supply_pump, HIGH);
          delay(pump_on_time * 1000);
          digitalWrite(supply_pump, LOW);
          water_level_count = 0;
        }
        
        
        if (timer == air_pump_interval + air_pump_counter && air_pump_state == LOW) {  //Turn on Air Pump
          air_pump_state = HIGH;
          analogWrite(air_pump, 255);
          air_pump_counter = timer;
        }
        else if (timer == air_pump_interval + air_pump_counter && air_pump_state == HIGH) {  //Trun off Air Pump
          air_pump_state = LOW;
          analogWrite(air_pump, 0);
          air_pump_counter = timer;
        }

        
        timer ++;
        if (timer == 1200) { //Reset Timer
          timer = 0;
          air_pump_counter = 0;
        }
        delay(60000); //1 min
}
