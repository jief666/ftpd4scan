//
//  main.m
//  ftpd4scan
//
//  Created by Jief on 08/04/2018.
//  Copyright © 2018 Jief. All rights reserved.
//

#import <Foundation/Foundation.h>

extern int ftpd_main (int argc, const char *argv[], char **envp);

int main(int argc, const char * argv[], char **envp) {
    @autoreleasepool {
        // insert code here...
        ftpd_main (argc, argv, envp);
    }
    return 0;
}
