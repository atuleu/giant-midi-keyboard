#pragma once


#define throw_nyi() do { \
	throw std::runtime_error( std::string(__PRETTY_FUNCTION__) + " is not yet implemented"); \
}while(0)
