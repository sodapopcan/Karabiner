// -*- Mode: objc -*-
//
//  KeyDumpAppDelegate.h
//  KeyDump
//
//  Created by Takayama Fumihiko on 09/10/25.
//

#import <Cocoa/Cocoa.h>
#import "EventQueue.h"

@interface KeyDumpAppDelegate : NSObject <NSApplicationDelegate> {
  NSWindow* window;
  IBOutlet id keyResponder_;
  IBOutlet EventQueue* eventqueue_;
}

@property (assign) IBOutlet NSWindow* window;

//
// Actions
//
- (IBAction) quit:(id)sender;

@end
