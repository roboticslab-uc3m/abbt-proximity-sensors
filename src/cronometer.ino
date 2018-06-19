void init_crono() {

  //for (unsigned int i = 0; i < 25; i++) {
    for (unsigned int j = 0; j < 6; j++) {
      //check_time[i][j] = 0;
      data_and_time[j];
    //}
  }
}

void crono(int aux_cont) {
  tiempo = millis() - inicio;        //Toma el tiempo de funcionamiento del microprocesador en milésimas
}

///////////////////////////////////////
/*
void convert_to_time(long tiemp, int i) {

  m = (tiemp / 1000) / 60;    //minutos
  s = (tiemp / 1000) % 60;    //segundos
  l = (tiemp % 1000);         //milesimas de segundo

  //Tiempo real
  if (i == 1) {
    check_time[aux_cont - 1][5] = m;
    check_time[aux_cont - 1][6] = s;
    check_time[aux_cont - 1][7] = l;
  }
  //Tiempo parcial
  else if (i == 2) {
    check_time[aux_cont - 1][8] = m;
    check_time[aux_cont - 1][9] = s;
    check_time[aux_cont - 1][10] = l;
  }

}
*/
/////////////////////////////////////////
void init_relative() {
  for (unsigned int i = 0; i < 2; i++) {
    relative_time[i] = 0;
  }

}

void relative() {

  if (aux_cont == 1) {
    relative_time[0] = tiempo;
    relative_time[1] = tiempo;
    data_and_time[6] = relative_time[0];
  }
  else if (aux_cont > 1) {
    //Cálculo del tiempo parcial entre dertecciones
    relative_time[1] = tiempo - relative_time[0];
    relative_time[0] = tiempo;
    data_and_time[6] = relative_time[1];
  }
  //convert_to_time(relative_time[0], 1);
  //convert_to_time(relative_time[1], 2);

}

//////////////////////////////////////////////
/*void print_crono_relative(int aux_cont) {
  relative();
  Serial.println();
  check_time[aux_cont - 1][0] = detecting_sensor;
  Serial.print("Detección en sensor: ");
  Serial.print(check_time[aux_cont - 1][0]);
  Serial.print("\t");

  Serial.print("Valores IR. ");
  check_time[aux_cont - 1][1] = IR_max_value[detecting_sensor][0];
  check_time[aux_cont - 1][2] = IR_max_value[detecting_sensor][1];
  check_time[aux_cont - 1][3] = IR_max_value[detecting_sensor][2];

  for (unsigned int i = 0; i < num_sensors ; i++) {
    Serial.print("S");
    Serial.print(i + 1);
    Serial.print(": ");

    for (unsigned int j = 0; j < LED ; j++) {
      Serial.print(IR_max_value[i][j]);
      Serial.print("   ");
    }
    Serial.print("   ");
  }
  Serial.print("\t");

  Serial.println();
  for (unsigned int j = 4; j < 9; j++) {
    if (j == 4) {
      check_time[aux_cont - 1][j] = aux_cont;
      if (aux_cont < 10) {
        Serial.print("Cube 0");
      } else {
        Serial.print("Cube ");
      }
      Serial.print(check_time[aux_cont - 1][j]);
      Serial.print(":  \t");
    }
    else if (j > 4 && j < 7) {
      if (check_time[aux_cont - 1][j] < 10)
        Serial.print("0");
      Serial.print(check_time[aux_cont - 1][j]);
      Serial.print(":");
    } else if (j == 7) {
      if (check_time[aux_cont - 1][j] < 100 && check_time[aux_cont - 1][j] > 10)
        Serial.print("0");
      if (check_time[aux_cont - 1][j] < 10)
        Serial.print("00");
      Serial.print(check_time[aux_cont - 1][j]);
    } else if (j > 7) {
      Serial.print("\t\tParcial:  ");
      if (check_time[aux_cont - 1][j] < 10)
        Serial.print("0");
      Serial.print(check_time[aux_cont - 1][j]);
      Serial.print(":");
      if (check_time[aux_cont - 1][j + 1] < 10)
        Serial.print("0");
      Serial.print(check_time[aux_cont - 1][j + 1]);
      Serial.print(":");
      if (check_time[aux_cont - 1][j + 2] < 100 && check_time[aux_cont - 1][j + 2] > 10)
        Serial.print("0");
      if (check_time[aux_cont - 1][j + 2] < 10)
        Serial.print("00");
      Serial.print(check_time[aux_cont - 1][j + 2]);
    }
  }

  Serial.print("\n");


}

////////////////////////////////////////////
void print_crono(int aux_cont) {
  // relative();
  Serial.println();

  for (unsigned int i = 0; i < aux_cont; i++) {
    Serial.println();

    for (unsigned int j = 0; j < 9; j++) {

      if (j == 0) {
        Serial.print("Detección en sensor: ");
        Serial.print(check_time[i][j]);
        Serial.print("\t");
      }

      if (j == 1) {
        Serial.print("Valores IR: ");
        Serial.print("LED 1: ");
        Serial.print(check_time[i][j]);
        Serial.print(" ");
        Serial.print("LED 2: ");
        Serial.print(check_time[i][j + 1]);
        Serial.print(" ");
        Serial.print("LED 3: ");
        Serial.print(check_time[i][j + 2]);
        Serial.print("\t");
      }

      if (j == 4) {
        if (i < 9) {
          Serial.print("Cube 0");
        } else {
          Serial.print("Cube ");
        }
        Serial.print(check_time[i][j]);
        Serial.print(":  ");
      }
      else if (j > 4 && j < 7) {
        if (check_time[i][j] < 10)
          Serial.print("0");
        Serial.print(check_time[i][j]);
        Serial.print(":");
      } else if (j == 7) {
        if (check_time[i][j] < 100 && check_time[i][j] > 10)
          Serial.print("0");
        if (check_time[i][j] < 10)
          Serial.print("00");
        Serial.print(check_time[i][j]);
      } else if (j > 7) {
        Serial.print("\tParcial: ");
        if (check_time[i][j] < 10)
          Serial.print("0");
        Serial.print(check_time[i][j]);
        Serial.print(":");
        if (check_time[i][j + 1] < 10)
          Serial.print("0");
        Serial.print(check_time[i][j + 1]);
        Serial.print(":");
        if (check_time[i][j + 2] < 100 && check_time[i][j + 2] > 10)
          Serial.print("0");
        if (check_time[i][j + 2] < 10)
          Serial.print("00");
        Serial.print(check_time[i][j + 2]);
      }
    }
  }

  Serial.print("\n");
}
*/
