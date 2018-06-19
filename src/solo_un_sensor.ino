void solo_uno() {
  for (unsigned int j = 0; j < LED; j++) {
    Serial.print(IR[1][j]);
    Serial.print("/");
  }
  Serial.print("\n");
}
