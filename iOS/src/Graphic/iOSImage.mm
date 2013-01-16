//
//  iOSImage.mm
//  R-Type
//
//  Created by Gael du Plessix on 11/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#include "OS.h"
#include "Image.h"
#include "Debug.h"
# include "Graphic/GraphicException.h"

#ifdef OS_IOS

// Biwtise hack to upper a number to its nearest power of two
static uint32 UpperPowerOfTwo(uint32 v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

void Graphic::Image::loadFromData(ByteArray const& data) {
    @autoreleasepool {
        NSData* nsData = [NSData dataWithBytes:data.getData() length:data.getSize()];
        UIImage* image = [[UIImage alloc] initWithData:nsData];
        if (image) {
            // Get the image data, and upscale it two power-of-two sizes :)
            _width = UpperPowerOfTwo([image size].width);
            _height = UpperPowerOfTwo([image size].height);
            if (_pixels)
                delete[] _pixels;
            _pixels = new uint8[_width * _height * 4];
            CGImageRef imageRef = [image CGImage];
            
            CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
            NSUInteger bytesPerPixel = 4;
            NSUInteger bytesPerRow = bytesPerPixel * _width;
            NSUInteger bitsPerComponent = 8;
            CGContextRef context = CGBitmapContextCreate((void*)_pixels, _width, _height,
                                                         bitsPerComponent, bytesPerRow, colorSpace,
                                                         kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
            CGColorSpaceRelease(colorSpace);
            
            CGContextDrawImage(context, CGRectMake(0, 0, _width, _height), imageRef);
            CGContextRelease(context);

            [image release];
        } else {
            throw new Graphic::Exception("Cannot load image from data");
        }
    }
}

#endif