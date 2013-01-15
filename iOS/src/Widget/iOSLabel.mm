//
//  iOSLabel.mm
//  R-Type
//
//  Created by Gael du Plessix on 14/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#include "Label.h"
#include "Graphic/Scene.h"
#include "Graphic/Renderer.h"
#include "iOSMainViewController.h"

void Widget::Label::_init(void) {    
    _font = [[UIFont fontWithName:@"Transformers" size:142] retain];
    update();
}

void Widget::Label::_destroy(void) {
    UIFont* font = (UIFont*)_font;
    [font release];
}

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

Graphic::Texture* Widget::Label::_getStringTexture(void) {
    
    if (_text == "")
        return new Graphic::Texture();
    
    UIFont* font = (UIFont*)_font;
    NSString* textString = [NSString stringWithUTF8String:_text.c_str()];
    
    // Compute the size of the needed texture
    CGSize textSize = [textString sizeWithFont:font];
    
    // First draw the text in an image context
    UIGraphicsBeginImageContext(textSize);
    
    [[UIColor colorWithRed:_color.x green:_color.y blue:_color.z alpha:1.0] set];

    [textString drawAtPoint:CGPointMake(0, 0) withFont:font];
    
    UIImage* textImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    // Create a CGContext with power-of-two size in which we will draw our image
    Vec2 textureSize = Vec2(UpperPowerOfTwo(textSize.width), UpperPowerOfTwo(textSize.height));
    uint8* textureData = new uint8[(uint32)textureSize.x * (uint32)textureSize.y * 4];
    memset(textureData, 0, (uint32)textureSize.x * (uint32)textureSize.y * 4);
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    NSUInteger bytesPerPixel = 4;
    NSUInteger bytesPerRow = bytesPerPixel * textureSize.x;
    NSUInteger bitsPerComponent = 8;
    CGContextRef context = CGBitmapContextCreate(textureData, textureSize.x, textureSize.y,
                                                 bitsPerComponent, bytesPerRow, colorSpace,
                                                 kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    CGColorSpaceRelease(colorSpace);

    CGContextDrawImage(context, CGRectMake(0, 0, textureSize.x, textureSize.y), textImage.CGImage);

    CGContextRelease(context);
    
    Graphic::Texture *texture = new Graphic::Texture();
    texture->setData(textureSize.x, textureSize.y, textureData);
    
    delete[] textureData;
    
    return texture;
}