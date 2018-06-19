void print_values_processing() {
  for (unsigned int i = 0; i < num_sensors; i++) {
    for (unsigned int j = 0; j < LED; j++) {
      Serial.print(IR[i][j]);
      Serial.print("/");
    }
  }
  Serial.print("\n");
}

void print_alisado_processing() {
  for (unsigned int i = 0; i < num_sensors; i++) {
    for (unsigned int j = 0; j < LED; j++) {
      Serial.print(f_nueva[i][j]);
      Serial.print("/");
    }
  }
  Serial.print("\n");
}

/*
  //////////////////////////////////
  void print_crono_processing() {
  for (unsigned int i = 0; i < 25; i++) {
    for (unsigned int j = 0; j < 4; j++) {
      if (j == 0) {
        check_time[i][j] = i + 1;
        Serial.print("Cube ");
        Serial.print(check_time[i][j]);
        Serial.print(":  \t");
      }
      else if (j < 3) {
        Serial.print(check_time[i][j]);
        Serial.print(":");
      } else {
        Serial.print(check_time[i][j]);
      }

    }
    Serial.print("/");
  }
  Serial.print("\n");

  }

  ///////////////////////////////////
  void general_processing(int aux_cont) {
  relative();

  //for (unsigned int i = 0; i < num_sensors ; i++) {

  Serial.print(detecting_sensor);
  Serial.print("/");
  for (unsigned int i = 0; i < num_sensors ; i++) {
    for (unsigned int j = 0; j < LED ; j++) {
      Serial.print(IR_max_value[i][j]);
      Serial.print("/");
    }
  }

  for (unsigned int k = 0; k < aux_cont; k++) {
    for (unsigned int l = 0; l < 5; l++) {
      if (l == 0) {
        check_time[k][l] = k + 1;
        //Serial.print("Cube ");
        if (k < 9) {
          Serial.print("Cube 0");
        } else {
          Serial.print("Cube ");
        }
        Serial.print(check_time[k][l]);
        Serial.print(":       ");
      }
      else if (l < 3) {
        if (check_time[k][l] < 10)
          Serial.print("0");
        Serial.print(check_time[k][l]);
        Serial.print(":");
      } else if (l == 3) {
        if (check_time[k][l] < 100 && check_time[k][l] > 10)
          Serial.print("0");
        if (check_time[k][l] < 10)
          Serial.print("00");
        Serial.print(check_time[k][l]);
      } else {
        Serial.print("              Parcial:       ");
        if (check_time[k][l] < 10)
          Serial.print("0");
        Serial.print(check_time[k][l]);
        Serial.print(":");
        if (check_time[k][l + 1] < 10)
          Serial.print("0");
        Serial.print(check_time[k][l + 1]);
        Serial.print(":");
        if (check_time[k][l + 2] < 100 && check_time[k][l + 2] > 10)
          Serial.print("0");
        if (check_time[k][l + 2] < 10)
          Serial.print("00");
        Serial.print(check_time[k][l + 2]);
      }
    }
    Serial.print("/");
  }
  Serial.print("\n");
  //}
  }
*/
///////////////////////////////////

void full_data(int aux_cont) {
  relative();
  data_and_time[0] = aux_cont;
  data_and_time[1] = detecting_sensor;
  data_and_time[2] = f_nueva[detecting_sensor][0];
  data_and_time[3] = f_nueva[detecting_sensor][1];
  data_and_time[4] = f_nueva[detecting_sensor][2];
  data_and_time[5] = (millis() - inicio);
}

void print_full_data() {
  for (unsigned int i  = 0; i < 7; i++) {
    Serial.print(data_and_time[i]);
    Serial.print("/");

  }
  Serial.print("\n");
}


