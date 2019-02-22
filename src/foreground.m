#import <AppKit/AppKit.h>

void macos_force_foreground_level() {
    NSLog(@"Trying to move this front");
    [NSApp activateIgnoringOtherApps: YES];
}
