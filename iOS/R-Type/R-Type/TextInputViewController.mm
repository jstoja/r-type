//
//  TextInputViewController.m
//  R-Type
//
//  Created by Gael du Plessix on 15/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#import "TextInputViewController.h"

#include "iOSMainViewController.h"
#include "Widget/TextEdit.h"

@interface TextInputViewController ()

@end

@implementation TextInputViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)dealloc {
    [_textField release];
    [super dealloc];
}

- (void)viewWillAppear:(BOOL)animated {
    NSString* value = [NSString stringWithUTF8String:iOSMainViewController::getInstance().getCurrentTextEdit()->getValue().c_str()];
    self.textField.text = value;
    [self.textField becomeFirstResponder];
}

- (IBAction)cancelInput:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
    Widget::TextEdit* textEdit = iOSMainViewController::getInstance().getCurrentTextEdit();
    textEdit->setFocus(false);
}

- (IBAction)doneInput:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
    Widget::TextEdit* textEdit = iOSMainViewController::getInstance().getCurrentTextEdit();
    textEdit->setValue([self.textField.text UTF8String]);
    textEdit->setFocus(false);
}

-(BOOL)textFieldShouldReturn:(UITextField *)textField {
    [self doneInput:self];
    return YES;
}

@end
