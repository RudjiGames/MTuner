/*
 * Copyright 2023 Milos Tosic. All Rights Reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE
 */

/*
Capture file (*.MTuner) will be stored in active user's APPDATA folder
For example:

	C:\Users\[username]\AppData\Roaming\MTuner
*/

#include "../../inc/rmem.h"
#include "../../inc/rmem_entry.h"

#include <stdlib.h>

#if RMEM_PLATFORM_PS4
unsigned int sceLibcHeapMemoryLock = 1;
size_t sceLibcHeapSize = 10*1024*1024;
#endif // RMEM_PLATFORM_PS4

#if RMEM_PLATFORM_ANDROID
#include <android/input.h>
#include <android/log.h>
#include <android/looper.h>
#include <android/window.h>
#include <android_native_app_glue.h>

extern "C"
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <android_native_app_glue.c>
#pragma GCC diagnostic pop
} // extern "C"

#endif // RMEM_PLATFORM_ANDROID

struct Allocator
{
	static void* s_allocate()
	{
		static int i=0;
		return malloc(i++&1? 23 : 46);
	}

	static void* s_realloc(void* _ptr)
	{
		return realloc(_ptr, 123);
	}
		
	static void s_free(void* _ptr)
	{
		free(_ptr);
	}
};

RMEM_ENTRY_CONSOLE

enum { ALLOC_ARRAY_SIZE = 1024*10 };

#if RMEM_PLATFORM_ANDROID
extern "C" void android_main(android_app* _app)
#else // RMEM_PLATFORM_ANDROID
int main(int , char* [])
#endif // RMEM_PLATFORM_ANDROID
{

#if RMEM_PLATFORM_ANDROID
    app_dummy();
#endif // RMEM_PLATFORM_ANDROID

	RMEM_REGISTER_TAG("Root tag");
	RMEM_REGISTER_TAG_CHILD("First half - Alloc", "Root tag");
	RMEM_REGISTER_TAG_CHILD("First half - Realloc", "Root tag");
	RMEM_REGISTER_TAG_CHILD("Second half", "Root tag");
	
	RMEM_TAG("Root tag");
	void* memory[ALLOC_ARRAY_SIZE];

	RMEM_MARKER("Start alloc",MARKER_COLOR_DEFAULT);

	{
		RMEM_TAG("First half - Alloc");
		for (size_t i=0; i<ALLOC_ARRAY_SIZE/2; i++)
			memory[i] = Allocator::s_allocate();
	}

	RMEM_MARKER_RGB("Realloc",90,90,120);

	{
		RMEM_TAG("First half - Realloc");
		for (size_t i=0; i<ALLOC_ARRAY_SIZE/2; i++)
			memory[i] = Allocator::s_realloc(memory[i]);
	}

	RMEM_MARKER_RGB("Alloc",90,120,90);

	{
		RMEM_TAG("Second half");
		for (size_t i=ALLOC_ARRAY_SIZE/2; i<ALLOC_ARRAY_SIZE; i++)
			memory[i] = Allocator::s_allocate();
	}

	RMEM_MARKER("Free",MARKER_COLOR_DEFAULT);

	for (size_t i=0; i<ALLOC_ARRAY_SIZE; i++)
		Allocator::s_free(memory[i]);

	RMEM_MARKER("End",MARKER_COLOR_DEFAULT);

#if RMEM_PLATFORM_ANDROID
	ANativeActivity_finish(_app->activity);
	exit(0);
#else // RMEM_PLATFORM_ANDROID
	return 0;
#endif // RMEM_PLATFORM_ANDROID
}

