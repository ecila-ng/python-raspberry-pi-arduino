import RPi.GPIO as GPIO
from time import sleep
import Adafruit_DHT
import urllib2
import json

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)

DHT_PIN = 4
SENSOR = Adafruit_DHT.DHT11

humidity, temperature = Adafruit_DHT.read_retry(SENSOR, DHT_PIN)
print ("Temp:", temperature)

while True:
    humidity, temperature = Adafruit_DHT.read_retry(SENSOR, DHT_PIN)

    if temperature == None or humidity == None:
        print ("ERROR! NONE ON DATA!")
        continue
    
    if humidity > 100:
        print ('ERROR! HUMIDITY TOO HIGH!')
        continue
    
    print("Temp:", temperature)
    print("Humd:", humidity)
    
    dweet = 'http://dweet.io/dweet/for/ludreamteam?'
    
    tempVar = 'temp=' + str(temperature)
    humdVar = 'humd=' + str(humidity)
    
    dweet += tempVar + '&' + humdVar
    
    response = urllib2.urlopen(dweet)
    
    html = response.read()
    print (html)
    
    sleep(2)    