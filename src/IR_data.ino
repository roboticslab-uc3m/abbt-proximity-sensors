//Toma valores ADC de los sensores
void data() {
  unsigned long leftSI114Total = 0, rightSI114Total = 0, start;

  int k = 0;

  for (unsigned int i = 0; i < num_sensors; i++) {
    total[i] = 0;
    for (unsigned int j = 0; j < LED; j++) {
      IR[i][j] = 0;
    }
  }

  start = millis();

  //SI114Left.fetchData();
  //SI114Right.fetchData();

  SI114Left.fetchLedData();
  SI114Cent.fetchLedData();
  SI114Right.fetchLedData();

  IR[0][0] += SI114Left.ps1;
  IR[0][1] += SI114Left.ps2;
  IR[0][2] += SI114Left.ps3;

  IR[1][0] += SI114Cent.ps1;
  IR[1][1] += SI114Cent.ps2;
  IR[1][2] += SI114Cent.ps3;

  IR[2][0] += SI114Right.ps1;
  IR[2][1] += SI114Right.ps2;
  IR[2][2] += SI114Right.ps3;

  k++;

  for (unsigned int i = 0; i < num_sensors; i++) {
    for (unsigned int j = 0; j < LED; j++) {
      IR[i][j] = IR[i][j] / k;
    }
  }

  for (unsigned int i = 0; i < num_sensors; i++) {
    total[i] = IR[i][0] + IR[i][1] + IR[i][2];
  }

  //Bucle para transformar datos ADC a mm (aproximado)
  /*
    for (unsigned int i = 0; i < num_sensors; i++) {
      for (unsigned int j = 0; j < LED; j++) {
        IR[i][j] = transform(IR[i][j]);
      }
    }

    for (unsigned int i = 0; i < num_sensors; i++) {
      total[i] = transform(total[i]);
    }
  */
}

void print_values() {

  for (unsigned int i = 0; i < num_sensors; i++) {
    for (unsigned int j = 0; j < LED; j++) {
      Serial.print(IR[i][j]);
      Serial.print("\t");
    }
    Serial.print("|||\t");
  }

  Serial.print("\n");

}

float transform(float valor) {
  //double mm = 331.57*(pow(((double) valor), -1.98));        //Aproximación de la ecuación de la curva característica del sensor (KODAK 100mm2)
  double mm = 20 * (17.833 * (exp(+0.0004 * ((double) valor))));   
    return (float) mm;
 
}

