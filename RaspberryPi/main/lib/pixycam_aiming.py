"""
Author: Andreas Brecl, Sean Newman
Date: 11/07/2022

This class will deal with pulling data from the pixycam for the location
of objects such as the balloon.
"""

import pixy 
from pixy import *
from ctypes import *

class PixycamAiming:
    def __init__(self):
        """
        This defintion will initalize the object for the pixycam aiming
        system.

        Input:  None
        Output: None
        """
        pass

def RedorGreen():
    blocks = BlockArray(1)
    frame = 0
    pixy.ccc_get_blocks (1, blocks)
    sig = blocks[0].m_signature

    if(sig == 2):
        return 'Red'
    elif(sig == 3):
        return "Green" 
    else:
        return "None"

def GetBlue():

    Max_x = 315
    half_x = 158
    blocks = BlockArray(1)
    frame = 0
    pixy.ccc_get_blocks (10, blocks)
    sig = blocks[0].m_signature

    count = pixy.ccc_get_blocks (10, blocks)
    if count > 0:
        for index in range (0, count):
                if(sig == 1):
                    return blocks[index].m_x-half_x
                else:
                    return "None"

    

    

    
class Blocks (Structure):
  _fields_ = [ ("m_signature", c_uint),
    ("m_x", c_uint),
    ("m_y", c_uint),
    ("m_width", c_uint),
    ("m_height", c_uint),
    ("m_angle", c_uint),
    ("m_index", c_uint),
    ("m_age", c_uint) ]