import logging
import os
import sys

from gpiozero import DistanceSensor, Servo
#import serial

logging.basicConfig()
logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)

sonar_trigger = xyz
sonar_echo = xyz

servo_pwm = xyz

#serial_port = '/dev/ttyACM0'
#serial_port = 'COM3'
#serial_baud = 115200


if __name__ == '__main__':
    #ser = serial.Serial(serial_port, serial_baud)

    while True:
        pass

        """
        if ser.in_waiting():
            sonar_data = ser.readline()
            logger.debug('sonar_data: ' + sonar_data)

            sonar_components = sonar_data.split(',')
            sonar_angle = int(sonar_components[0])
            logger.debug('sonar_angle: ' + str(sonar_angle))
            sonar_dist = int(sonar_components[1])
            logger.debug('sonar_dist: ' + str(sonar_dist))
        """