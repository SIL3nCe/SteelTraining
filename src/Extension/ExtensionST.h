#ifndef __EXTENSION_H
#define __EXTENSION_H

#if defined(_WIN32)
#	if defined(ExtensionST_EXPORTS)
#		define EXTENSION_ST_EXPORT __declspec(dllexport)
#	else
#		define EXTENSION_ST_EXPORT __declspec(dllimport)
#	endif // ExtensionST_EXPORTS
#else // defined(_WIN32)
#	define EXTENSION_ST_EXPORT
#endif

class CShIdentifier;

extern "C"
{
	EXTENSION_ST_EXPORT void	ExtensionInitialize			(void);
	EXTENSION_ST_EXPORT void	ExtensionRelease			(void);

	EXTENSION_ST_EXPORT void	ExtensionOnPluginStarted	(const CShIdentifier & levelIdentifier);
	EXTENSION_ST_EXPORT void	ExtensionOnPluginStopped	(const CShIdentifier & levelIdentifier);
}

#endif // __EXTENSION_H
