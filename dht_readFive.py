import RPi.GPIO as GPIO
from time import sleep
import Adafruit_DHT
import urllib2
import json

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)

while True:
    dweet = 'http://dweet.io/get/dweets/for/ludreamteam'
    
    response = urllib2.urlopen(dweet)
    
    html = response.read()
    #print (html)
    
    myJSON = json.loads(html)
    
    root = myJSON['with']
    #print ('ROOT:')
    #print (root)
    
    for i in range(len(root)):
        item = root[i]
        #print ('ITEM:')
        #print (item)

        content = item['content']
        #print ('CONTENT:')
        #print (content)

        humdVar = content['humd']
        print ('HUMD ' + str(i+1) + ': ' + str(humdVar))
    
    print ("\n")
    sleep(2)
