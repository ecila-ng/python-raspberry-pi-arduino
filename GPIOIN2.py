import RPi.GPIO as GPIO
from time import sleep
import urllib2

GPIO.setmode(GPIO.BOARD)

myDweet = 'http://dweet.io/get/latest/dweet/for/LU-CSC49008-LED'

BUTTON_PIN = 7
LED_PIN = 11
BUTTON_PIN1 = 12



#html = response.read()
#print html



GPIO.setwarnings(False)

GPIO.setup(BUTTON_PIN, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.setup(BUTTON_PIN1, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

GPIO.output(LED_PIN, GPIO.LOW) # turns off the led before doing anything else

readValue1 = GPIO.input(BUTTON_PIN1)

if readValue1 is True:
    on = True
  
else:
    on = False
   
while True:
    response = urllib2.urlopen(myDweet)
    html = response.read()


    
    ##readValue = GPIO.input(BUTTON_PIN)
    ##if readValue1 is True:
        ##on = True
        
   ##else:
        ##on = False
      
        
        ##if readValue is 1 and on is False:
            ##GPIO.output(LED_PIN, GPIO.HIGH)
            ##on = True
          
        ##elif readValue is 1 and on is True:
           ## GPIO.output(LED_PIN, GPIO.LOW)
           ## on = False
            
        ##elif readValue is 0 and on is False:
           ## GPIO.output(LED_PIN, GPIO.LOW)
           ## on = False
           
       ## elif readValue is 1 and on is False:
            ##GPIO.output(LED_PIN, GPIO.HIGH)
            ##on = True
            
        
        print(html)
            
        ##print readValue
        sleep(.15)
        
            
            