void reconise(int time_scan) {

  for (unsigned int i = 0; i < num_sensors; i++) {
    init_total[i] = 0;
    for (unsigned int j = 0; j < LED; j++) {
      init_value_IR[i][j] = 0;
      suma[i][j] = 0;
      media[i][j] = 0;
    }
  }
  data();

  if (total[0] < 50000 && total[1] < 50000) {               //Detiente el inicio si los sensores estan tapados 
    for (unsigned int t = 0; t < time_scan; t++) {
      data();
      for (unsigned int i = 0; i < num_sensors; i++) {
        if (total[i] < 50000) {
          if (min_max == 0) {
            init_min = IR[i][1];
            init_max = IR[i][1];
            min_max = 1;
          }
          else if (IR[i][1] < init_min) {
            init_min = IR[i][1];
          } else if (IR[i][1] > init_max) {
            init_max = IR[i][1];
          }
        }

        for (unsigned int j = 0; j < LED; j++) {
          //init_value_IR[i][j] = transform(IR[i][j]);

          init_value_IR[i][j] = IR[i][j];
          suma[i][j] = suma[i][j] + init_value_IR[i][j];
        }

      }
    }

    for (unsigned int i = 0; i < num_sensors; i++) {
      for (unsigned int j = 0; j < LED; j++) {
        media[i][j] = suma[i][j] / time_scan;
        init_value_IR[i][j] = media[i][j];                          //Valores IR de supresion de primer plano. Valor de offset
      }
    }

    for (unsigned int i = 0; i < num_sensors; i++) {
      init_total[i] = media[i][0] + media[i][1] + media[i][2];      //Media total de supresion de primer plano. Valor de offset
    }

    porcentaje = 1 - (init_value_IR[0][0] / init_max);             //Determina un porcentaje de error en la medicion del offset
  }

}

