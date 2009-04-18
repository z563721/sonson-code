// 
// client
// MyClient.m
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
//#import "MyClient.h"

@implementation MyClient

- (IBAction)accessServer:(id)sender {
	NSString *ip = [serverIPAddressStr_ stringValue];
	[self startAccessingToServer:ip port:5004];
}

- (IBAction)sendSomething:(id)sender {
	char *p = "auau\n";
	NSData *data = [NSData dataWithBytes:p length:strlen(p)];
	[fileHandle writeData: data];
}

- (void) startAccessingToServer:(NSString*)ip port: (int)port{
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return;
	
	// make file handle
	fileHandle = [[NSFileHandle alloc] initWithFileDescriptor: sockfd];
	
	struct sockaddr_in server_addr;
	struct hostent* server_host;
	
	// clear with zero
	bzero((char *)&server_addr, sizeof(server_addr));
	
	// initialize
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	// get host information
	server_host = gethostbyname([ip cString]);
	bcopy((char *)server_host->h_addr, (char *)&server_addr.sin_addr.s_addr, server_host->h_length);
	
	// try to connetct
	if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
		printf("error?n");
	
	free(server_host);
	
	// set notification from filehandle
	[[NSNotificationCenter defaultCenter] addObserver: self
								selector: @selector(receiveMessage:)
								name: NSFileHandleReadCompletionNotification
								object: fileHandle];
	// set notify
	[fileHandle readInBackgroundAndNotify];
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
		[receiveMessageStr_ setStringValue:string];
  		[fileHandle readInBackgroundAndNotify];
  	}
}

@end
