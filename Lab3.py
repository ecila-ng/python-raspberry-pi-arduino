import RPi.GPIO as GPIO
from time import sleep
import urllib2
import json

GPIO.setmode(GPIO.BOARD)

BUTTON_PIN = 7
LED_PIN = 11
LED_STATE_PIN = 12

GPIO.setwarnings(False)

GPIO.setup(BUTTON_PIN, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.setup(LED_STATE_PIN, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)

ledState = GPIO.input(LED_STATE_PIN)
print(ledState)

prevButtonState = GPIO.input(BUTTON_PIN)
currButtonState = GPIO.input(BUTTON_PIN)

while(True):

    currButtonState = GPIO.input(BUTTON_PIN)
    
    # if the current state is the same as the previous, skip the loop
    if currButtonState is prevButtonState:
        prevButtonState = currButtonState
        continue
    
    print("BUTTON_STATE: ", currButtonState)
    
    if currButtonState is GPIO.HIGH:
        dweet = 'http://dweet.io/get/latest/dweet/for/manicmonday'
        response = urllib2.urlopen(dweet)
        html = response.read()
        myJSON = json.loads(html)
        
        success = myJSON['this']
        success = str(success)
        if success == "failed":
            print ("HTML ERROR: Please Retry")
            continue

        root = myJSON['with']
        print ('ROOT:')
        print (root)

        item = root[0]
        print ('ITEM:')
        print (item)

        content = item['content']
        print ('CONTENT:')
        print (content)

        command = content['command']
        command = str(command)
        print ('COMMAND:')
        print (command)
        
        if command == 'off':
            GPIO.output(LED_PIN, GPIO.LOW)
        elif command == 'on':
            GPIO.output(LED_PIN, GPIO.HIGH)
        else:
            ledState = GPIO.input(LED_STATE_PIN) # get the current state of the led
            if ledState is GPIO.HIGH:
                GPIO.output(LED_PIN, GPIO.LOW)
            else:
                GPIO.output(LED_PIN, GPIO.HIGH)
            
        sleep(0.25) # calm down
    
    # setup next run
    prevButtonState = currButtonState
