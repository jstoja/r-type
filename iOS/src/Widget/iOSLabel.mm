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
    getScene()->removeElement(getElement());
    
    _label = [[UILabel alloc] init];
    // Yes this is ugly...
    UILabel* label = (UILabel*)_label;
    UIFont* font = [UIFont fontWithName:@"Transformers" size:85.33];
    label.font = font;
    label.textColor = [UIColor whiteColor];
    label.backgroundColor = [UIColor clearColor];
    label.shadowColor = [UIColor colorWithWhite:0 alpha:0.8];
    label.shadowOffset = CGSizeMake(5, 5);
    label.adjustsFontSizeToFitWidth = YES;
    label.textAlignment = NSTextAlignmentCenter;
    
    ViewController* controller = iOSMainViewController::getInstance().getViewController();
    [controller.view addSubview:label];
    update();
}

void Widget::Label::_destroy(void) {
    UILabel* label = (UILabel*)_label;
    [label removeFromSuperview];
    [label release];
}

void    Widget::Label::update() {
    if (getSize().x + getSize().y == 0)
        return ;
    
    UILabel* label = (UILabel*)_label;
    
    // Set text aligment
    uint32 aligments[] = {NSTextAlignmentLeft, NSTextAlignmentRight, NSTextAlignmentCenter};
    if (_alignment < 3)
        label.textAlignment = aligments[_alignment];
    
    label.text = [NSString stringWithUTF8String:_text.c_str()];
    CGRect frame = label.frame;
    CGPoint center = label.center;
    
    Vec2 scenePos = getPosition();
    Vec2 viewportPos = Graphic::Renderer::getInstance().sceneToViewport(scenePos);
    Vec2 viewportSize = Graphic::Renderer::getInstance().sceneToViewport(getSize());
    viewportSize.y = Graphic::Renderer::getInstance().getViewportSize().y - viewportSize.y;
    center.x = viewportPos.x;
    center.y = viewportPos.y;
    frame.size.width = viewportSize.x;
    frame.size.height = viewportSize.y * 2;
    label.frame = frame;
    label.center = center;
}