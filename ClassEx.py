import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BOARD)

BUTTON_PIN = 7
LED_PIN = 11

GPIO.setwarnings(False)

GPIO.setup(BUTTON_PIN, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.output(LED_PIN, GPIO.LOW)

while(True):

    readValue = GPIO.input(BUTTON_PIN)
    print(readValue)
    
    
    if(readValue is 1):
        GPIO.output(LED_PIN, GPIO.HIGH)
    else:
        GPIO.output(LED_PIN, GPIO.LOW)
    