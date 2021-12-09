# Door Lock System
 This is a Door Lock System Project using AVR-Atmega16 MCU Simulated By Protues 8.11 Professional
 
# Description
 TWO MCU are used in this Project.
 
  - First MCU is used to get the password from the user and send it using UART Communication Protocol 
    to the second MCU.
  - Second MCU is used to compare between the password received from first MCU and the one saved in 
    EEPROM interfaced by I2C. Depending on this comparison some actions are ready to happen:
    
     - First: if the two passwords are matched , the user will enter the system to decide whether he wants
              to change the password or open the door ( Start the Door Motor ).
              
     - Second: if the two passwords are not matched, the user will get 3 chances to enter the right password.
               if he failled , this would mean that he is not the owner of the house and a buzzer will start Peeping for
               a while which means that a help in on the way.
