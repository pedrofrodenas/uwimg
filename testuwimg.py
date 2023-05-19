#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri May 19 22:32:29 2023

@author: pedrofrodenas
"""

from uwimg import *
from ctypes import *
import matplotlib.pyplot as plt

import numpy as np
import cv2

def convert_to_np(img):
    h = img.h
    w = img.w
    c = img.c
    
    img_np = np.zeros([h,w,c])
    
    
    for channel in range(c):
        for y in range(h):
            for x in range(w):
                img_np[y,x,channel] = get_pixel(img, channel, y , x)
                
    return img_np

def convert_to_image(np_img):
    
    if np_img.ndim == 3:
        h, w, c = np_img.shape
        out = make_image(w, h, c)
        
        for channel in range(c):
            for y in range(h):
                for x in range(w):
                    set_pixel(out, x, y, channel, np_img[y,x,channel])
    else:
        h, w = np_img.shape
        c = 0
        out = make_image(w, h, 1)
        
        for y in range(h):
            for x in range(w):
                set_pixel(out, x, y, 0, np_img[y,x])
        
    
    
                
    return out

def load_image(f):
    return load_image_lib(f.encode('ascii'))


im1 = load_image("data/dog.jpg")

np_img = convert_to_np(im1)

















