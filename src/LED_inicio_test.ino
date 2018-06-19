void system_on() {
  digitalWrite(led_rojo, HIGH);
  digitalWrite(led_verde, HIGH);
  delay(1000);
}

void test_on() {
  digitalWrite(led_rojo, LOW);
  digitalWrite(led_verde, HIGH);
}

void test_off() {

  digitalWrite(led_rojo, HIGH);
  digitalWrite(led_verde, LOW);
}

