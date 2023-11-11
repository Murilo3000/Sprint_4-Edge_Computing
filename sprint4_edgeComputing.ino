/**
 ******************************************************************************
   @file        mqtt_class.ino
   @author      Airton Toyofuku/Murilo Alves Mansano
   @copyright   None
   @date        17.09.2023
   @version     1.0
   @brief       Arduino Sketch to send data to the Tago.io application throug
                MQTT protocol
 ******************************************************************************
*/
/* Private includes ----------------------------------------------------------*/
#include <ArduinoJson.h>    // Lib to format JSON Document
#include "EspMQTTClient.h"  // Lib to comunicate MQTT from ESP
#include "DHT.h";           // Lib to access the DHT sensor
/* Board Configuration--------------------------------------------------------*/
char temperatura[100];
char umidade    [100];
/* DHT Configuration----------------------------------------------------------*/

#define DHTPIN 13  // The sensor is connected to GPIO 13
#define DHTTYPE DHT22 // Define the type of DHT sensor

DHT dht(DHTPIN, DHTTYPE);
float dhtTemperature = 0;
float dhtHumidity = 0;

//MQTT and WiFi configuration
EspMQTTClient client
(
  "Wokwi-GUEST",        //nome da sua rede Wi-Fi
  "",  //senha da sua rede Wi-Fi
  "mqtt.tago.io",       //Endereço do servidor MQTT
  "Default",            //User é sempre default pois vamos usar token
  "f5951b96-0679-488b-aeee-ec370f48d481",// Código do Token
  "Sprint - MQTT",         //Nome do device
  1883                  //Porta de comunicação padrao
);
void setup()
{
  //dht.begin();
}
// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{}
//loop do programa
void loop()
{
  dhtTemperature = dht.readTemperature();
  dhtHumidity = dht.readHumidity();

  //Getting temperature and Humidity data
  getDhtData();
  StaticJsonDocument<300> TemperaturaJson;
  TemperaturaJson["variable"] = "temperatura";
  TemperaturaJson["value"] = dhtTemperature;
  StaticJsonDocument<300> UmidadeJson;
  UmidadeJson["variable"] = "umidade";
  UmidadeJson["value"] = dhtHumidity;
  
  serializeJson(TemperaturaJson, temperatura);
  serializeJson(UmidadeJson, umidade);
  
  client.publish("temperatura", temperatura); 
  client.publish("umidade", umidade);
  delay(5000);
  client.loop();
}
/*
   @brief Gets the Temp/Hum data
*/
void getDhtData(void) {
}