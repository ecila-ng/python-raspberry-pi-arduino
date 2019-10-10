/************************************************************************ 
 *  reads DHT11 pin and reports resulting humidity and                  *
 * temperature values                                                    *
 *                                                                      *
 *  AUTHOR: Stephen Blythe                                              *
 *  DATE: 9/2019                                                        *
 *  THANKS TO: UUGear's DHT11 data sheet summary                        *
 *    (see http://www.uugear.com/                                       *
 *                 portfolio/dht11-humidity-temperature-sensor-module/) *
 ************************************************************************/

#include <wiringPi.h>
#include <iostream>


#define DHTPIN		  7

#define SETUP_LOW_ERROR   1
#define SETUP_HIGH_ERROR  2
#define DATA_ERROR        3
#define CHECKSUM_ERROR    4

/***************************************************************
 *   reads data from DHT11 sensor for RaspberryPi              *
 *                                                             *
 *  pinNumber: the RaspberryPi pin number to use (wiringPi).   * 
 *  dataRead: 5 element array to hold DHT11 data:              *
 *               [0] integer portion of humidity               *
 *               [1] tenths (1/10ths) value of humidity        *
 *               [2] integer portion of temperature            *
 *               [3] tenths (1/10ths) value of temperature     *
 *               [4] checksum of previous 4 values             *
 *                                                             *
 *   Returns: 0 on success, error code on failure.             *
 *   Side effect: modifies dataRead on success.                *
 ***************************************************************/
int read_dht11_dat(int pinNumber, int dataRead[])
{

  std::string result=""; // holds binary string of bits read
  int highTime=0;        // time spent reading a HIGH signal
  int lowTime=0;         // time spent reading a LOW signal
  
  // start all data values at 0. 
  dataRead[0] = dataRead[1] = dataRead[2] = dataRead[3] = dataRead[4] = 0;
  
  // prime the DHT11 device
  pinMode( pinNumber, OUTPUT );
  
  //  ... send low for 18ms
  digitalWrite( pinNumber, LOW );
  delay( 18 );
  
  // ... send high for 20-40 us
  digitalWrite( pinNumber, HIGH );
  delayMicroseconds( 40 );
  
  // get ready for DHT11 to respond
  pinMode( pinNumber, INPUT );
  
  
  
  // DHT11 should send 80 us of low
  while(digitalRead(pinNumber) == LOW && lowTime<150)
    {
      delayMicroseconds(20);
      lowTime+=20;
    }
  // ... check DHT11 init low time
  if (lowTime>100 || lowTime<60) 
    {
      return SETUP_LOW_ERROR;
    }
  
  
  // DHT11 should next send 80 us of HIGH
  while(digitalRead(pinNumber) == HIGH && highTime<150)
    {
      delayMicroseconds(20);
      highTime+=20;
    }
  // ... check DHT11 init high time
  if (highTime>100 || highTime<60) 
    {
      return SETUP_HIGH_ERROR;
    }
  
  
  // now, we're ready for data ...
  // there will be 40 bits of data
  for (int bit=0; bit<40; bit++)
    {
      highTime=0;
      lowTime=0;
      // wait until signal is no longer low 
      while(digitalRead(pinNumber) == LOW && lowTime<60)
	{
	  lowTime++;
	  delayMicroseconds(1);
	}
      // too much low? That's an error. 
      if (lowTime>=60)
	{ 
	  return DATA_ERROR;
	}
      
      // now check how long the high signal is ...
      while(digitalRead(pinNumber) == HIGH && highTime<80)
	{
	  delayMicroseconds(1);
	  highTime++;
	}
      if (highTime>=80)
	{ 
	  return DATA_ERROR;
	}
      
      
      // spec says 26-28 us of high is a '0', 70us is a '1'.
      //     49us seems like a good cutoff. 
      if (highTime>49)
	{
	  result+="1";
	}
      else
	{
	  result+="0";
	}   
    }


  // now convert data to integers, and use checksum to verify data:
  int checksum=0;
  // convert each byte from string value
  for (int byteNum=0; byteNum<5; byteNum++)
    {
      // assume byte is 0, and fill in as bits dictate ...
      dataRead[byteNum]=0;
      for (int bitNum=0; bitNum<8; bitNum++)
	{ 
	  dataRead[byteNum]=dataRead[byteNum]<<1; // The << here left shifts everything by one position
	  if(result.at(byteNum*8+bitNum)=='1')
	    dataRead[byteNum]+=1;
	}
      // add data bytes into the checksum. skipping read checksum
      if (byteNum!=4)
		checksum+=dataRead[byteNum];
    }
  // make sure checksum verified by the presented check (dataRead[4])
  // & does bitwise comparison of each side, 0xff is a hexadecimal number
  if ( (checksum&0xff)!=dataRead[4])
    return CHECKSUM_ERROR;
  
  // it worked!!!!
  return 0;
}


/***************************************************************
 *   reads data from DHT11 sensor for RaspberryPi; repeats     *
 *       until succeeds                                        *
 *                                                             *
 *  pinNumber: the RaspberryPi pin number to use (wiringPi).   * 
 *  dataRead: 5 element array to hold DHT11 data:              *
 *               [0] integer portion of humidity               *
 *               [1] tenths (1/10ths) value of humidity        *
 *               [2] integer portion of temperature            *
 *               [3] tenths (1/10ths) value of temperature     *
 *               [4] checksum of previous 4 values             *
 *                                                             *
 *   Side effect: modifies dataRead on success.                *
 ***************************************************************/
void read_until_success(int pinNumber, int dataRead[])
{
  int x;
  while(x=read_dht11_dat(pinNumber, dataRead)!=0) 
    {
      //std::cout<<x;
      //std::cout.flush();
      delay(1000); // let dht11 "cool down" before next attempt
    }
} 

int main( int argc, char *argv[] )
{
  int pinNumber;

  // if specified on command line, use the corresponding pin. Otherwise, use 
  //  default oin number
  if (argc<2)
    pinNumber=DHTPIN;
  else
    pinNumber = atoi(argv[1]); //atoi() converts a string to an integer

  std::cout << "Raspberry Pi wiringPi DHT11 Temperature test program" 
       << std::endl;
  
  // if RaspberryPi pins not working, give up!
  if ( wiringPiSetup() == -1 )
    exit( 1 );
 
  // To repeatedly get data, put the following code block in a loop

  // data to hold DHT11 results
  int dht11_dat[5] = { 0, 0, 0, 0, 0 };

  // get next DHT11 reading 
  read_until_success(pinNumber, dht11_dat);

  // dump results of DHT11 read
  std::cout << dht11_dat[0] << "." << dht11_dat[1] << "% humid ";
  std::cout << dht11_dat[2] << "." << dht11_dat[3] << "C";
  std::cout << std::endl;

  // End the loop here

  return(0);
}

