/*
 * Written by the Chair for Operating Systems, RWTH Aachen University
 *
 * NO Copyright (C) 2010-2011, Stefan Lankes
 * consider these trivial functions to be public domain.
 *
 * These functions are distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */

#include <string.h>

void *memcpy(void *dest, const void *src, size_t count)
{
	size_t i;

	if (BUILTIN_EXPECT(!dest || !src, 0))
		return dest;

	for (i = 0; i < count; i++)
		((char*)dest)[i] = ((char*)src)[i];
	
	return dest;
}

void *memset(void *dest, int val, size_t count)
{
	size_t i;

	if (BUILTIN_EXPECT(!dest, 0))
		return dest;

	for (i = 0; i < count; i++)
		((char*) dest)[i] = (char) val;

	return dest;
}

size_t strlen(const char *str)
{
	size_t len = 0;

	if (BUILTIN_EXPECT(!str, 0))
		return len;

	while (str[len] != '\0')
		len++;

	return len;
}

char* strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	if (BUILTIN_EXPECT(!dest || !src, 0))
		return dest;

	for (i = 0 ; i < n && src[i] != '\0' ; i++)
		dest[i] = src[i];
	if (i < n)
		dest[i] = '\0';
	else
		dest[n-1] = '\0';

	return dest;
}

char* strcpy(char *dest, const char *src)
{
        size_t i;

	if (BUILTIN_EXPECT(!dest || !src, 0))
		return dest;

        for (i = 0 ; src[i] != '\0' ; i++)
                dest[i] = src[i];
        dest[i] = '\0';

        return dest;
}

int strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s1 == *s2) {
		s1++;
		s2++;
	}

	return (*(unsigned char *) s1) - (*(unsigned char *) s2);
}

int strncmp(const char *s1, const char *s2, size_t n)
{
	if (BUILTIN_EXPECT(n == 0, 0))
		return 0;

	while (n-- != 0 && *s1 == *s2) {
		if (n == 0 || *s1 == '\0')
			break;
		s1++;
		s2++;
	}

	return (*(unsigned char *) s1) - (*(unsigned char *) s2);
}
