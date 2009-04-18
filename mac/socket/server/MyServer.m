// 
// server
// MyServer.m
// 
// The MIT License
// 
// Copyright (c) 2009 sonson, sonson@Picture&Software
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//#import "MyServer.h"

@implementation MyServer
- (void) dealloc {
	[fileHandle_ closeFile];
	close(nConnection_);
	[super dealloc];
}
- (IBAction)startServer:(id)sender {
	[self startListening];
}
- (IBAction)sendSomething:(id)sender {
	char *p = "abcdef\n";
	NSData *data = [NSData dataWithBytes:p length:strlen(p)];
	[fileHandle_ writeData: data];
}

- (void) setTextMessage:(NSString*)str {
	[receiveStr_ setStringValue:str];
}

- (void) startListening {
	int result=0;
	struct sockaddr_in addr;
	
	nSockfd_ = socket(AF_INET, SOCK_STREAM, 0);
	
	memset( &addr, 0, sizeof( addr ) );
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(5004);
	
	char on = 1;
	setsockopt(nSockfd_, SOL_SOCKET, SO_REUSEADDR, (char * ) & on, sizeof (on));
	result = bind(nSockfd_, (struct sockaddr *)&addr, sizeof(addr));
	if ( result < 0) {
		[NSException raise: @"SockBindingException" format: @"Can't bind socket: %s", strerror(errno)];
		exit(0);
	}
	result = listen(nSockfd_, 1);
	if ( result < 0) {
		[NSException raise: @"SockListeningException" format: @"Can't listen socket: %s", strerror(errno)];
		// [ self close ];
		exit(0);
	}
	nConnection_ = accept(nSockfd_, (struct sockaddr *)NULL, NULL);
	if ( nConnection_ < 0) {
		[NSException raise: @"SockAcceptException" format: @"Can't accept socket: %s", strerror(errno)];
		exit(0);
	}
	fileHandle_ = [[NSFileHandle alloc] initWithFileDescriptor: nConnection_];
	NSData *data = [fileHandle_ availableData];
	[fileHandle_ writeData: data];
	
	[[NSNotificationCenter defaultCenter] addObserver: self
		selector: @selector(receiveMessage:)
		name: NSFileHandleReadCompletionNotification
		object: fileHandle_];
	[fileHandle_ readInBackgroundAndNotify];
}

- (void)receiveMessage: (NSNotification*)notification {
  	// check error
  	NSNumber *pUNIXError = [ NSNumber numberWithInt:0 ];
  	pUNIXError = [[notification userInfo] objectForKey:@"NSFileHandleError"];
  	
  	if( ![ pUNIXError intValue ] ){
  		NSData *data;
  		data = [[notification userInfo] objectForKey:NSFileHandleNotificationDataItem];
  		NSString *string = [[NSString alloc] initWithData: data encoding: NSASCIIStringEncoding];
  		NSLog(string);
		[self setTextMessage:string];
  		[fileHandle_ readInBackgroundAndNotify];
  	}
  	else{
		NSLog( "Test" );
  		close(nSockfd_);
  		close(nConnection_);
  		[fileHandle_ release ];
	}
}

- (NSString*) GetComputerName {
    NSString *ret = nil;
    CFStringRef computerName = (CFStringRef)SCDynamicStoreCopyComputerName(NULL, NULL);
    if (computerName != NULL) {
        ret = [NSString stringWithString:(NSString*)computerName];
		NSLog( ret );
        CFRelease(computerName);
    }
    return ret;
}

- (NSString*) GetComputerIPAddressV4 {
	NSHost*host = [NSHost currentHost];
	NSArray*array = [host addresses];
	// NSString*ipv6 = [array objectAtIndex:0];
	NSString*ipv4 = [array objectAtIndex:1];
	return ipv4;
}

- (void) awakeFromNib {
	[IPStr_ setStringValue:[self GetComputerIPAddressV4]];
}

@end
