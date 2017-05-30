#include "Logger.h"

Logger logger;

////////////////////////////
// USER-ENTERED VARIABLES //
////////////////////////////
char* dataLoggerName = "SC 01";
char* fileName = "SC01.txt"; // Name of file for logged data: 8.3 format (e.g, 
                             // ABCDEFGH.TXT); <= 8 chars before ".txt" is OK

//Setup logging interval here, may setup more than one variable. 
//Minimum interval = 1 sec, maximum interval is 23 hours, 59 minutes, 59 seconds 
//0 for all means that the logger will not sleep
int Log_Interval_Seconds = 0; //Valid range is 0-59 seconds
int Log_Interval_Minutes = 0; //Valid range is 0-59 minutes
int Log_Interval_Hours = 0; //Valid range is 0-23 hours
// external_interrupt is true for a tipping bucket rain gauge
bool external_interrupt = false;

void setup(){  //Serial baud rate is set to 38400
  logger.initialize(dataLoggerName, fileName,
    Log_Interval_Hours, Log_Interval_Minutes, Log_Interval_Seconds, 
    external_interrupt);
  logger.setupLogger();
}

void loop(){
  // ***************************************** 
  logger.goToSleep_if_needed(); // Send logger to sleep
  logger.startLogging();  // Wake up and initialize
  // ****** DO NOT EDIT ABOVE THIS LINE ****** 

  //////////////////////////////////
  // READ SENSORS: EDIT THIS PART //
  //////////////////////////////////

  // Analog sensors: place all analog sensor commands between
  // startAnalog() and endAnalog().
  // If you have no analog sensors, you should comment out the 
  // startAnalog() and endAnalog() commands

  logger.startAnalog(); //turn on 3.3V power

  delay(5);  //Allow voltage to stabalize

  //Honeywell_HSC_analog(int pin, float Vsupply, vRef, float Pmin, float Pmax, int TransferFunction_number, int units)

  //TransferFunction: 1 = 10% to 90% of Vsupply (A in second to last digit of part number)
  //TransferFunction: 2 = 5% to 95% of Vsupply (B in second to last digit of part number)
  //TransferFunction: 3 = 5% to 85% of Vsupply (C in second to last digit of part number)
  //TransferFunction: 4 = 4% to 94% of Vsupply (F in second to last digit of part number)

  //Units: 0 = mbar
  //Units: 1 = bar
  //Units: 2 = Pa
  //Units: 3 = KPa
  //Units: 4 = MPa
  //Units: 5 = inH2O
  //Units: 6 = PSI

  //Example: logger.Honeywell_HSC_analog(A1, 5, 3.3, 0, 30, 1, 6);

  logger.Honeywell_HSC_analog(1, 3.3, 3.3, 0, 30, 1, 6);

  logger.endAnalog();  //turn off 3.3V power

  //
  // INSERT DIGITAL SENSOR READING COMMANDS HERE!
  //

  // NOTE: THE BUFFER SIZE IS (CHECK ON THIS!!!!!!!!!!!!!!) 256 BYTES;
  // run "logger.bufferWrite" if you think you are approaching this limit.
  // Otherwise, the buffer will overflow and I'm not sure what will happen.


  // ****** DO NOT EDIT BELOW THIS LINE ****** 

  // Wrap up files, turn off SD card, and go back to sleep
  logger.endLogging();

  // ***************************************** 

}
