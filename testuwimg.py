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
        out = make_image(c,h, w)
        
        for channel in range(c):
            for y in range(h):
                for x in range(w):
                    set_pixel(out, channel, y, x, np_img[y,x,channel])
    else:
        h, w = np_img.shape
        c = 0
        out = make_image(1, h, w)
        
        for y in range(h):
            for x in range(w):
                set_pixel(out, 0, y, x, np_img[y,x])
    return out

def load_image(f):
    return load_image_lib(f.encode('ascii'))


im1 = load_image("data/dog.jpg")

np_img = convert_to_np(im1)

resized2 = nn_resize(im1, 467, 713)

res_np = convert_to_np(resized2)

im2 = load_image("/Users/pedrofrodenas/Projects/uwimg/figs/dog-resize-nn.png")\
    
im2_np = convert_to_np(im2)

# Check where are not equal
b = np.where(im2_np != res_np, im2_np, 0)


# def test_gaussian_filter():
    
    
    
f = make_gaussian_filter(7)

f_np = convert_to_np(f)

f_scaled = f_np * 100

gt = load_image("figs/gaussian_filter_7.png")

gt_np = convert_to_np(gt)

gt_scaled = gt_np / 100

gtandf = np.where(f_np != gt_np, f_np, 0)
    
















