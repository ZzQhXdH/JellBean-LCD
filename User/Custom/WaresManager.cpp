#include "Custom/WaresManager.h"

static const char *pDefaultPassword = "187258369";


void WaresManager::setPassword(const char *password)
{
	char *p = mPassword;
	
	while (*password != '\0')
	{
		*p = *password;
		p ++;
		password ++;
	}
	*p = '\0';
	save();
}

bool WaresManager::isPasswordDefaultEquals(const char *password)
{
	const char *p = pDefaultPassword;
	
	while (*password != '\0')
	{
		if (*p != *password)
		{
			return false;
		}
		password ++;
		p ++;
	}
	if (*p != '\0') {
		return false;
	}
	
	return true;
}

bool WaresManager::isPasswordEquals(const char *password)
{
	char *p = mPassword;
	
	while (*password != '\0')
	{
		if (*password != *p) 
		{
			return false;
		}
		
		password ++;
		p ++;
	}
	
	if (*p != '\0') {
		return false;
	}
	return true;
}
