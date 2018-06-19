void alisado(int reset_alisado) {

  for (unsigned int i = 0; i < num_sensors; i++) {
    for (unsigned int j = 0; j < LED; j++) {
      if (reset_alisado == 0) {
        f_prev[i][j] = media[i][j];
      }
      else {
        f_prev[i][j] = f_nueva[i][j];
      }
    }
  }

  for (unsigned int i = 0; i < num_sensors; i++) {
    for (unsigned int j = 0; j < LED; j++) {
      A_real[i][j] = IR[i][j];
      f_nueva[i][j] = f_prev[i][j] + cte * (A_real[i][j] - f_prev[i][j]);
    }
  }

  for (unsigned int i = 0; i < num_sensors; i++) {
    f_total[i] = (f_nueva[i][0] + f_nueva[i][1] + f_nueva[i][2]);
  }

}

void print_alisado() {
  for (unsigned int i = 0; i < num_sensors; i++) {
    for (unsigned int j = 0; j < LED; j++) {
      Serial.print(f_nueva[i][j] * (1 + porcentaje));
      Serial.print("\t");
    }
    Serial.print("|||\t");
  }
  Serial.print("\n");
}

