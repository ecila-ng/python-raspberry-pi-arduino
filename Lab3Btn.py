import RPi.GPIO as GPIO
from time import sleep
import urllib2
import json

GPIO.setmode(GPIO.BOARD)

LED_PIN = 11
LED_STATE_PIN = 12

GPIO.setwarnings(False)

GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.setup(LED_STATE_PIN, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)

ledState = GPIO.input(LED_STATE_PIN) # prime the led state

command = None
prevCommand = command
commandDateStamp = None
lastCommandDateStamp = commandDateStamp

while(True):
    
    dweet = 'http://dweet.io/get/latest/dweet/for/tacotuesday'
    response = urllib2.urlopen(dweet)
    html = response.read()
    myJSON = json.loads(html)

    success = myJSON['this']
    success = str(success)
    if success == "failed":
        print ("HTML ERROR: Please Retry")
        sleep(4)
        continue

    root = myJSON['with']
    #print ('ROOT:')
    #print (root)

    item = root[0]
    #print ('ITEM:')
    #print (item)
    
    commandDateStamp = item['created']
    print ('DATE STAMP:', commandDateStamp)

    content = item['content']
    #print ('CONTENT:')
    #print (content)

    command = content['command'] # IT CRASHEDEDED HIERE
    command = str(command)
    print ('COMMAND:', command)
    
    if command == prevCommand:
        print ('PREV COMMAND:', prevCommand) 
        if commandDateStamp == prevCommandDateStamp:
            print ('PREV DATE STAMP:', prevCommandDateStamp)
            
            # prime next loop iteration
            prevCommand = command
            prevCommandDateStamp = commandDateStamp
            continue

    if command == 'off':
        GPIO.output(LED_PIN, GPIO.LOW)
    elif command == 'on':
        GPIO.output(LED_PIN, GPIO.HIGH)
    elif command == 'toggle':
        ledState = GPIO.input(LED_STATE_PIN) # get the current state of the led
        if ledState is GPIO.HIGH:
            GPIO.output(LED_PIN, GPIO.LOW)
        else:
            GPIO.output(LED_PIN, GPIO.HIGH)

    sleep(2) # calm down
    
    # prime next loop iteration
    prevCommand = command
    prevCommandDateStamp = commandDateStamp
