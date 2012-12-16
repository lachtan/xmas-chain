/*
#include <Dhcp.h>
#include <Dns.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <util.h>
*/

#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>

#define BUFFER_SIZE 64

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 4, 55 };
int telnetPort = 23;
EthernetServer server(telnetPort);

int ledPin = 13;
int pwmLedPinLeft = 9;
int pwmLedPinRight = 6;
int pwmLedPinWhite = 5;

int intensityLeft = 0;
int intensityRight = 0;
int intensityWhite = 0;
  
void setup()
{  
	pinMode(pwmLedPinLeft, OUTPUT);
	pinMode(pwmLedPinRight, OUTPUT);
	pinMode(pwmLedPinWhite, OUTPUT);
	
	analogWrite(pwmLedPinLeft, intensityLeft);
	analogWrite(pwmLedPinRight, intensityRight);
	analogWrite(pwmLedPinWhite, intensityWhite);

	Ethernet.begin(mac, ip);
	server.begin();
}  

String readLine(EthernetClient client)
{
	String line = "";
	if (! client)	
	{
		return line;
	}
	while (client.connected())
	{
		if (client.available() == 0)
		{
			continue;
		}
		char chr = client.read();
		if (chr == '\r' || chr == '\n')
		{
			break;
		}
		if (line.length() > 32)
		{
			break;
		}
		line += chr;
	}
	return line;
}

void correct(int& intensity)
{
	if (intensity < 0)
	{
		intensity = 0;
	}
	else if (intensity > 255)
	{
		intensity = 255;
	}
}

void loop()
{
	char buffer[BUFFER_SIZE];
	
	EthernetClient client = server.available();	
	if (client)
	{
		//client.println("tak te tu vitam");
		while (client.connected())
		{
			String line = readLine(client);
			line.toCharArray(buffer, BUFFER_SIZE);			

			if (line[0] >= '0' && line[0] <= '9')
			{
				int intensity = atoi(buffer);
				intensityLeft = intensity;
				intensityRight = intensity;
				intensityWhite = intensity;
			}
			else if (line[0] == 'l')
			{
				intensityLeft = atoi(buffer + 1);
			}
			else if (line[0] == 'r')
			{
				intensityRight = atoi(buffer + 1);
			}
			else if (line[0] == 'w')
			{
				intensityWhite = atoi(buffer + 1);
			}
			
			client.print("L=");
			client.print(intensityLeft);
			client.print(", R=");
			client.print(intensityRight);
			client.print(", W=");
			client.print(intensityWhite);
			client.println();
			
			analogWrite(pwmLedPinLeft, intensityLeft);
			analogWrite(pwmLedPinRight, intensityRight);
			analogWrite(pwmLedPinWhite, intensityWhite);
		}
	}
	delay(1);
	client.stop();
}

void old()
{
	/*
	while (true)
	{
		intensity += 1;
		if (intensity > 128)
		{
			intensity = 0;
		}
		analogWrite(pwmLedPinLeft, intensity);
		delay(30);
	}
	*/
}

void blik()
{ 
	analogWrite(pwmLedPinLeft, 255);
	delay(500);
	analogWrite(pwmLedPinLeft, 50);
	delay(500);	
} 

void backup()
{
	digitalWrite(ledPin, HIGH);
	delay(100);
	digitalWrite(ledPin, LOW);
	delay(100);
}

