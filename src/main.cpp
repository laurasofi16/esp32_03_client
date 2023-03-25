#include <Arduino.h>
#include <WiFi.h>

const char * nombre = "lsgo";
const char * password = "1234abcd";
const char * host ="www.google.com";
const int puerto = 80;


void setup() {

  pinMode(2,OUTPUT); // coloco el pin 2 como salida
  Serial.begin(115200);//confuguracion de velocidad de wifi
  Serial.println("Inicializando el dispositivo");
  WiFi.begin(nombre,password);

  Serial.printf("Estableciendo vinculo con el AP");
  while (WiFi.status() !=WL_CONNECTED){
  Serial.print(".");
  delay(1000);
    
  }
  Serial.println("\r\n Conexion establecida");
  Serial.println("numero IP asignado");
  Serial.println(WiFi.localIP());//imprime el numero ip
  Serial.println();
}


void loop() {
  WiFiClient Cliente;
  //
  if(!(Cliente.connect(host,puerto))){
    Serial.println("Error, conexion al host fallida");
    delay(3000);
    return;
  }
  Serial.print("conexion exitosa al host ");
  
  // peticion GET al servidor http
  Cliente.print("GET /index.html HTTP/1.1\r\nHost: "+String(host)+"\r\n"+"Connection: close\r\n\r\n");

  //Debemos darle un tiempo al servidor a que responda la peticion
  //delay(5000); // no funciona aqui bloquea el wifi 
  unsigned long milisegundos=millis(); //hora de inicio

while(Cliente.available()==0){// preguntamos si no hay datos recibidos disponibles
    if(millis()-milisegundos>7000){
      Serial.println("se expiro el tiempo de la conexion");
      Cliente.stop();
    }
}

while (Cliente.available()){
  String linea = Cliente.readStringUntil('\r');
  Serial.println(linea);
}

  Serial.println("Fin de la conexion");
  Cliente.stop();
  delay(2000);
