//
//  TextInputViewController.h
//  R-Type
//
//  Created by Gael du Plessix on 15/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface TextInputViewController : UIViewController<UITextFieldDelegate>

- (IBAction)cancelInput:(id)sender;
- (IBAction)doneInput:(id)sender;


@property (retain, nonatomic) IBOutlet UITextField *textField;

@end
