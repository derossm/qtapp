/**********************************************************************************************************************************************\
	Copyright© 2020-2021 Mason DeRoss

	Released under the MIT License.

	Copying and distribution of this file, with or without modification, are permitted in any medium without royalty,
	provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.

	DESCRIPTION:

\**********************************************************************************************************************************************/
#pragma once
#pragma system_header

#ifndef _WIN32
	#include <fcntl.h>
	#include <unistd.h>
	#include <signal.h>

	#include <sys/io.h>
	#include <sys/ioctl.h>
	#include <sys/signal.h>
	#include <sys/socket.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <sys/wait.h>

	#include <linux/kd.h>
	#include <machine/sysarch.h>

	#include <memory.h>
	#include <sys/un.h>
	#include <sys/time.h>
	#include <sys/mman.h>
	#include <strings.h>
	#include <dirent.h> // linux dir traverse

//POSIX threads.
#include <pthread.h>

#endif // #ifndef _WIN32
