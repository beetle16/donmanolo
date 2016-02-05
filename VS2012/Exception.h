#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <exception>

namespace Exception
{
	//TODO: Stacktrace, current position, file etc.
	class ApplicationException : public std::exception
	{
	protected:
		char* message;

	public:
		ApplicationException()
		{
			message = new char[1];
			message[0] = '\0';
		}

		ApplicationException(const char* message)
		{
			int message_len = strlen(message)+1;
			if( message_len > 1024 )
			{
				throw "exception message size exceeded 1024!";
			}

			this->message = new char[message_len];
			strcpy_s(this->message, message_len, message);
		}

		~ApplicationException()
		{
			delete[] message;
		}
	};


}



#endif