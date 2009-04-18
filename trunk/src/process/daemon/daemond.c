// 
// daemon
// daemond.c
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
///*
 Original source code, here.
 http://www.enderunix.org/documents/eng/daemon.php
  UNIX Daemon Server Programming Sample Program
  Levent Karakas <levent at mektup dot at> May 2001
*/

#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// invariables
#define RUNNING_DIR			"/tmp"
#define LOCK_FILE			"daemond.lock"
#define LOG_FILE			"daemond.log"
#define PID_BUFFER_SIZE		10

void log_output( char *filename, char *message ) {
	FILE *logfile = fopen( filename, "a" );
	if( !logfile )
		return;
	fprintf( logfile, "%s¥n", message );
	fclose( logfile );
}

void signal_handler( int sig ) {
	switch( sig ){
	case SIGHUP:
		log_output( LOG_FILE, "hangup signal catched" );
		break;
	case SIGTERM:
		log_output( LOG_FILE, "terminate signal catched" );
		exit(0);
		break;
	}
}

void daemonize() {
	int i,lfp;
	char str[PID_BUFFER_SIZE];
	
	if( getppid() == 1 ) {
		log_output( LOG_FILE, "already a daemon" );
		return;
	}
	
	i = fork();
	if( i < 0 ){
		log_output( LOG_FILE, "fork error" );
		exit(1);
	}
	if( i > 0 )		// this is a parent process, will exit
		exit(0);
	
	setsid();				// new process group setup
	for( i = getdtablesize(); i >= 0; --i )
		close(i);
	
	i = open( "/dev/null", O_RDWR );
	dup( i );
	dup( i );
	
	// set newly created file permissions
	umask( 027 );
	chdir( RUNNING_DIR );
	
	// open lock file
	lfp = open( LOCK_FILE, O_RDWR | O_CREAT, 0640 );

	if( lfp < 0 ) {
		log_output( LOG_FILE, "can not open" );
		exit(1);
	}
	if( lockf( lfp, F_TLOCK, 0 ) < 0 ) {
		log_output( LOG_FILE, "can not lock" );
		exit(0);
	}
	
	// record pid to lockfile
	sprintf( str, "%d¥n", getpid() );
	write( lfp, str, strlen(str) );
	
	//
	signal( SIGCHLD, SIG_IGN );
	signal( SIGTSTP, SIG_IGN );
	signal( SIGTTOU, SIG_IGN );
	signal( SIGTTIN, SIG_IGN );
	
	// signal handler setup
	signal( SIGHUP, signal_handler);
	signal( SIGTERM, signal_handler);
}

int main( int argc, void** argv ){
	daemonize();
	while(1)
		sleep(1);
}
