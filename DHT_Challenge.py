import RPi.GPIO as GPIO
from time import sleep
import Adafruit_DHT

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)

sensor = Adafruit_DHT.DHT11

DHT = 4
RED_LED = 11
BLUE_LED = 13

GPIO.setup(RED_LED, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(BLUE_LED, GPIO.OUT, initial=GPIO.LOW)

humidity, temperature = Adafruit_DHT.read_retry(sensor, DHT)
print(temperature)

while True:
    humidity, temperature = Adafruit_DHT.read_retry(sensor, DHT)
    if temperature > 23:
        GPIO.output(RED_LED, GPIO.HIGH)
    if temperature < 20:
        #GPIO.output(BLUE_LED, GPIO.HIGH
        sleep(1)
