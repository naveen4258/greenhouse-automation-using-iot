#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <WiFi.h>
#include "dht.h"
#define dht_apin A1 // Analog Pin sensor is connected to
 dht DHT;

#include<SoftwareSerial.h>
SoftwareSerial comm(2,3); //setting Rx and Tx pins

String server="192.168.137.149"; //variable for sending data to webpage
String uri = "/iot/irrigationupdate.php";
boolean No_IP=false;//variable to check for ip Address
String IP=""; //variable to store ip Address
char temp1='0';
String data = "";

int a=0;
int b=0;
int x= 0,y , z;

String str1="<p>I am Arduino</p>";   //String to display on webpage
String str2="<p>Data Received Successfully.....</p>";     //another string to display on webpage

 int led= 7;
int ACWATERPUMP = 13; //You can remove this line, it has no use in the program.
int sensor =A0; //You can remove this line, it has no use in the program.
int val=0;
char st1[]="don't water the plants";
char st2[]="water the plants";

     
void setup() 
{
   Serial.begin(9600);
   comm.begin(115200);
   wifi_init();
   Serial.println("System Ready..");
 Serial.begin(9600);
  pinMode(ACWATERPUMP,OUTPUT); //Set pin 13 as OUTPUT pin, to send signal to relay
  pinMode(sensor,INPUT); //Set pin 8 as input pin, to receive data from Soil moisture sensor.`

   
}


void loop() 
{
  b=0;
  Serial.println("Refresh Page");
  x += 1;
  data = "moisture=" + String(x)+"&humidity=" + String(y)+"&temperature=" + String(z );
  Serial.println(data);
  Serial.println("Starting");
  postData(data);
  Serial.println("Finished");
  delay(30000);

   val =digitalRead(8);//Read data from soil moisture sensor  
  Serial.println(val);
  if(val<500) 
  {
  digitalWrite(ACWATERPUMP,LOW);
  digitalWrite(led,HIGH);  
  //if soil moisture sensor provides LOW value send LOW value to relay
    Serial.println(str2);
  }
  else
  {
  digitalWrite(ACWATERPUMP,HIGH); //if soil moisture sensor provides HIGH value send HIGH value to relay
    digitalWrite(led,LOW);  
   Serial.println(str1);
  }
  delay(1000); //Wait for few second and then continue the loop.
   DHT.read11(dht_apin);
    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    
    delay(1000);//Wait 5 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
 
}// end loop()   


void findIp(int time1) //check for the availability of IP Address
{
  int time2=millis();
  while(time2+time1>millis())
  {
    while(comm.available()>0)
    {
      if(comm.find("IP has been read"))
      {
        No_IP=true;
      }
    }
  }
}

void showIP()//Display the IP Address 
{
  IP="";
  Serial.println("IP");
  char ch=0;
  while(1)
  {
    comm.println("AT+CIFSR");
    while(comm.available()>0)
    {
      if(comm.find("STAIP,"))
      {
        delay(1000);
        Serial.print("IP Address:");
        while(comm.available()>0)
        {
          ch=comm.read();
          if(ch=='+')
          break;
          IP+=ch;
        }
      }
      if(ch=='+')
      break;
    }
    if(ch=='+')
    break;
    delay(1000);
  }
  Serial.print(IP);
  Serial.print("Port:");
  Serial.println(80);
}

void establishConnection(String command, int timeOut) //Define the process for sending AT commands to module
{
  int q=0;
  while(1)
  {
    Serial.println(command);
    comm.println(command); 
    while(comm.available())
    {
      if(comm.find("OK"))
      q=8;
    }
    delay(timeOut);
    if(q>5)
    break;
    q++;
  }
  if(q==8)
  Serial.println("OK");
  else
  Serial.println("Error");
}

void wifi_init() //send AT commands to module
{
      establishConnection("AT",100);
      establishConnection("AT+CWMODE=3",100);
      establishConnection("AT+CWQAP",100);  
      establishConnection("AT+RST",5000);
      findIp(5000);
      if(!No_IP)
      {
        Serial.println("Connecting Wifi....");
        establishConnection("AT+CWJAP=\"12345678\",\"12345678\"",7000);         //provide your WiFi username and password here
      }
      else
        {
        }
      Serial.println("Wifi Connected"); 
      delay(2000);
      showIP();
}

void postData (String data1) {
  establishConnection("AT+CIPSTATUS",500);
  establishConnection("AT+CIPSTART=\"TCP\",\"" + server + "\",80", 100);//start a TCP connection.
  delay(1000);
  String postRequest = "POST " + uri + " HTTP/1.0\r\n" +
                       "Host: " + server + "\r\n" +
                       "Accept: *" + "/" + "*\r\n" +
                       "Content-Length: " + data.length() + "\r\n" +
                       "Content-Type: application/x-www-form-urlencoded\r\n" +"\r\n" + data;
  Serial.println(postRequest);
  String sendCmd = "AT+CIPSEND=";//determine the number of caracters to be sent.
  comm.print(sendCmd);
  comm.println(postRequest.length() );
  delay(500);
  if(comm.find(">")) { 
    Serial.println("Sending..");
    comm.print(postRequest);
    if( comm.find("SEND OK")) { 
      Serial.println("Packet sent");
      while (comm.available()) {
        String tmpResp = comm.readString();
          Serial.println(tmpResp);
      }
    }
  }
  comm.println("AT+CIPCLOSE=0");
}
