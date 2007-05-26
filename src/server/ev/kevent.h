/*******************************************************************************

   Copyright (C) 2007 M.K.A. <wyrmchild@users.sourceforge.net>
   
   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:
   
   Except as contained in this notice, the name(s) of the above copyright
   holders shall not be used in advertising or otherwise to promote the sale,
   use or other dealings in this Software without prior written authorization.
   
   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.

*******************************************************************************/

#ifndef EventKevent_INCLUDED
#define EventKevent_INCLUDED

#include "interface.h"
#include "traits.h"

#ifndef NDEBUG
	#include <iostream>
	using std::cout;
	using std::endl;
#endif

class EventKevent
	: EventInterface<EventKevent>
{
private:
	timeval _timeout;
	int nfds;
	int evfd;
public:
	EventKevent() throw();
	~EventKevent() throw();
	
	void timeout(uint msecs) throw();
	int wait() throw();
	int add(fd_t fd, int events) throw();
	int remove(fd_t fd) throw();
	int modify(fd_t fd, int events) throw();
	bool getEvent(fd_t &fd, int &events) throw();
};

/* traits */

template <> struct event_has_accept<EventKevent> { static const bool value; };
template <> struct event_read<EventKevent> { static const int value; };
template <> struct event_write<EventKevent> { static const int value; };
template <> struct event_accept<EventKevent> { static const int value; };
template <> struct event_system<EventKevent> { static const std::string value; };

#endif // EventKevent_INCLUDED
