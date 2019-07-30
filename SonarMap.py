import logging
import os
import sys

import serial

logging.basicConfig()
logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)

#serial_port = '/dev/ttyACM0'
serial_port = 'COM3'
serial_baud = 115200


if __name__ == '__main__':
    ser = serial.Serial(serial_port, serial_baud)

    while True:
        if ser.in_waiting():
            sonar_data = ser.readline()
            logger.debug('sonar_data: ' + sonar_data)

            sonar_components = sonar_data.split(',')
            sonar_angle = int(sonar_components[0])
            logger.debug('sonar_angle: ' + str(sonar_angle))
            sonar_dist = int(sonar_components[1])
            logger.debug('sonar_dist: ' + str(sonar_dist))