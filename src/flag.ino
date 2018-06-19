void IR_max_detected() {

  for (unsigned int i = 0; i < num_sensors ; i++) {
    for (unsigned int j = 0; j < LED ; j++) {
      //Busca el punto máximo de la curva de detección
      IR_max_value[i][j] = max(f_nueva[i][j] - init_value_IR[i][j], IR_max_value[i][j]);

    }
  }
}

void print_IR_max_detected() {

  for (unsigned int i = 0; i < num_sensors ; i++) {
    for (unsigned int j = 0; j < LED ; j++) {
      Serial.print(IR_max_value[i][j]);
      Serial.print("/");
    }
    Serial.println();
  }
}

void detecting_zone() {
  //Indica que sensor es el que ha realizado la detección
  for (unsigned int i = 0; i < num_sensors ; i++) {
    for (unsigned int j = 0; j < LED ; j++) {
      valor = IR_max_value[i][j];
      if (valor >= maximo) {
        maximo  = IR_max_value[i][j];
        detecting_sensor = i;
      }
    }
  }

  valor = 0;
  maximo = 0;
}

int flag() {
//Entrada por flanco de LED 1
  if (IR[0][0] > init_value_IR[0][0]  && flagIR1 == 0 && flagIR2 == 0 && flagIR3 == 0) {
    flagIR1 = 1;
    flagIR2 = 0;
    flagIR3 = 0;

    return phase = 1;
  }
  //Entrada por flanco de LED 2
  else if (IR[0][1] > init_value_IR[0][1]  && flagIR1 == 0 && flagIR2 == 0 && flagIR3 == 0) {
    flagIR1 = 0;
    flagIR2 = 1;
    flagIR3 = 0;

    return phase = 2;
  }
  //Entrada por flanco de LED 3
  else if (IR[0][2] > init_value_IR[0][0]  && flagIR1 == 0 && flagIR2 == 0 && flagIR3 == 0) {
    flagIR1 = 0;
    flagIR2 = 0;
    flagIR3 = 1;

    return phase = 3;
  }
  //No aparece entrada por flanco
  else if (IR[0][0] <= init_value_IR[0][0]  && IR[0][1] <= init_value_IR[0][1]  && IR[0][2] <= init_value_IR[0][2] ) {
    flagIR1 = 0;
    flagIR2 = 0;
    flagIR3 = 0;

    reconise(20);

    return phase = 0;
  }
}

