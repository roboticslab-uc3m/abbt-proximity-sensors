 /**
 * @file    Sensores_BBT.ino
 * @brief   Sistema automatizado de conteo de cubos mediante sensores de proximidad SI1143 aplicado a la prueba de destreza manual gruesa Box & Blocks Test.
 *
 * @author  Victor Pozo Perez <100303638@alumnos.uc3m.es>
 * @date    2018-06
 * 
 * @note Hardware setup + please consult the pin chart below for your choice of SDA/SCL pins to use
  for the num_sensors. Note that this I2C version is strictly bit+banged which makes it a
  tad slower than the arduino version.
  However you can use it on any pins you choose, adding a lot of flexibility.
  The SI114 is not applicable to I2C daisy chaining on the same I2C line so use different ports
  for two num_sensorss.

  Note that no series resistors are required using this library.
  If you choose to use series resistors on the data lines, use 4.7 or 5k.
  Connect Ground.
  Connect 3.3V line to 3.3 volts (PWR line on num_sensorss are not connected).

  For JeeNode / Arduino / ATmega328 users, just set the port used

  JeeNode Port  SDA ('duino pin)  SCL ('duino pin)
  0             A4            A5    // Leonardo: SDA is pin 2, SCL is pin 3.
  1             4             14 (A0)
  2             5             15 (A1)
  3             6             16 (A2)
  4             7             17 (A3)
*/

//Asocia cada sensor a los pares de pines del microprocesador
const int PORT_SI114_LEFT = 0;
const int PORT_SI114_CENT = 1;
const int PORT_SI114_RIGHT = 2;

int led_verde = 12;
int led_rojo = 9;

#include <SI114.h>

//Estructura de sensores
#define num_sensors 3
#define LED 3

//Valores IR de los sensores
float IR[num_sensors][LED];
float total[num_sensors];

//Valores IR de los sensores para modelar la supresión de primer plano
float init_value_IR[num_sensors][LED];
float IR_max_value[num_sensors][LED];
float suma[num_sensors][LED];
float media[num_sensors][LED];
float init_total[num_sensors];

//Valores IR para el alisado exponencial
float f_nueva[num_sensors][LED], cte = 0.8, A_real[num_sensors][LED], f_prev[num_sensors][LED], f_total[num_sensors];
int reset_alisado = 0;
float init_min = 0, init_max = 0, min_max = 0, porcentaje = 0, umbral = 1.1;

int event = 0;
int cont = 0, aux_cont = 0;
int start_play = 0;

//Variables para triangulación de objetos
float Avect = 0.0;
float Bvect = 0.0;
float Cvect = 0.0;
float Tvect, x, y, angle = 0;


//Variables para análisis detección por flancos y máxima detección
int flagIR1 = 0, flagIR2 = 0, flagIR3 = 0, phase = 0;
int detecting_sensor = -1;
int valor = 0, maximo = 0;

//Variables de tiempo de detección
unsigned long start, aux_tiempo;
long tiempo, inicio;
long relative_time[2];
int m, s, l;
unsigned long tiempo_BBT = 60000;

//Almacén de datos
//int check_time[20][11];
long data_and_time[7];

//Variable para cambio de fase durante la curva de detección
int go = 0;

PortI2C rightBus (PORT_SI114_RIGHT);
PulsePlug SI114Right (rightBus);

PortI2C CentBus (PORT_SI114_CENT);
PulsePlug SI114Cent (CentBus);

PortI2C leftBus (PORT_SI114_LEFT);
PulsePlug SI114Left (leftBus);

///////////////////////////////////////////////
///
///////////////////////////////////////////////
void setup () {

  Serial.begin(9600);

  pinMode(led_verde, OUTPUT);
  pinMode(led_rojo, OUTPUT);

  system_on();

  //Inicializa los sensores
  SI114Left.initPulsePlug();
  SI114Cent.initPulsePlug();
  SI114Right.initPulsePlug();

  //Reconoce el entorno y aplica una supresión de primer plano (Offset de detección)
  reconise(200);

  //Inicia cronometro
  init_crono();
  init_relative();

  Serial.flush();
  inicio = millis();
  //Serial.println("START TEST");
  start_matlab();
  test_on();



}

///////////////////////////////////////////////
///
///////////////////////////////////////////////
void loop() {

  data();                         //Lee los sensores

  alisado(reset_alisado);         //Amortigua los valores de las señales (alisado exponencial)
  reset_alisado = 1;

  //print_alisado_processing();
  //print_alisado_matlab();
  //solo_uno();

  //Algoritmo para la detección de objetos
  switch (start_play) {
    //Análisis durante la detección
    case 0:
      //Busca flanco de entrada del objeto
      if (((f_total[0] > init_total[0] * (umbral + porcentaje)) || 
      (f_total[1] > init_total[1] * (umbral + porcentaje)) || 
      (f_total[2] > init_total[2] * (umbral + porcentaje))) && go == 0) {
        //aux_start = start;
        for (unsigned int i = 0; i < num_sensors ; i++) {
          for (unsigned int j = 0; j < LED ; j++) {
            IR_max_value[i][j] = 0;
          }
        }
        go = 1;

      }
      //Analiza el máximo de la curva de detección
      if (((f_total[0] > init_total[0] * (umbral + porcentaje)) || 
      (f_total[1] > init_total[1] * (umbral + porcentaje)) || 
      (f_total[2] > init_total[2] * (umbral + porcentaje))) && go == 1) {
        IR_max_detected();
        detecting_zone();

      }
      //Comprueba que se completa la curva de detección
      if (f_total[detecting_sensor] < init_total[detecting_sensor] * (umbral + porcentaje) && go == 1) {

        aux_cont++;                             //Incrementa contador de objetos
        crono(aux_cont);                        //Toma de tiempo de detección
        //print_crono(aux_cont);
        //print_crono_relative(aux_cont);         //Imprime datos sobre la detección


        full_data(aux_cont);
        print_matlab();


        //todo(aux_cont);
        //Serial.print(detecting_sensor);

        //print_crono_processing();
        //print_IR_max_detected();
        //general_processing();
        //print_matlab();

        valor = 0;
        maximo = 0;
        detecting_sensor = -1;

        go = 0;
      }
      //Condición de final de ejercicio de detección. Colocar mano sobre el sensor central o detectar 50 objetos
      // if ((f_total[1] > 130000) || aux_cont >= 150){//((millis() - inicio) > tiempo_BBT)) {
      if ((f_total[1] > 130000) || ((millis() - inicio) > tiempo_BBT)) {
        start_play = 1;
      }
      break;

    //Detección finalizada. Imprime todos los datos.
    case 1:
      //Serial.println("Finished.");
      end_matlab();
      //print_crono(aux_cont);
      start_play = -1;
      test_off();
      break;

    case -1:
      break;

    default:
      start_play = 0;
      break;
  }

  //solo_uno();
  //print_alisado();
  //print_values();
  //print_values_processing();

  delay(5);
}



