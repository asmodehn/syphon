#ifndef __WKCOCOS_TOOLBOX_H__
#define __WKCOCOS_TOOLBOX_H__

#include <sstream>

namespace WkCocos
{
	/**
	* Tool box class.
	* Set of useful static function.
	*/
	class ToolBox
	{
	public:
		/**
		* Default destructor
		*/
		virtual ~ToolBox();

		/**
		* Transform a int value to text
		* @param value Value to transform to text
		* @return A string representing the value.
		*/
		template <class T>
		static std::string itoa(T value)
		{
			std::stringstream str;
			str << value;

			return str.str();
		}

		/**
		* small extension on fopen, which creates intermediate directories if needed
		*/
		static FILE* FOpen(std::string name, std::string mode);

		/**
		* Implementation ( from VS C++ ) of std::stoul for Android, who doesnt have it ( no C99 function )
		*/
		static unsigned long stoul(const std::string& _Str, size_t *_Idx = 0, int _Base = 10);

		/**
		* Implementation of std::to_string for Android, who doesnt have it.
		*/
		template <typename T>
		static std::string to_string(T value)
		{
			std::ostringstream os;
			os << value;
			return os.str();
		}

	private:
		/**
		* Default constructor.
		* Static class, no need to create object.
		*/
		ToolBox();

	};
}//namespace WkCocos

#endif //__WKCOCOS_TOOLBOX_H__
