#include "trie_dll.h"
#include "trie.h"
// #ifdef _WIN32
// #include <windows.h>
// #endif

SimpleTrie::Trie g_trie;

void AddEntry(const char* entry, int index)
{
    g_trie.AddEntry(entry, index);
}

void RemoveEntry(const char* entry)
{
    g_trie.RemoveEntry(entry);
}

void SetSrc(const char* src)
{
    g_trie.SetSrc(src);
}

void Match(int* output, int* output_count, int max_count)
{
    g_trie.Match(output, output_count, max_count);
}

// #ifdef _WIN32
// BOOL APIENTRY DllMain( HMODULE hModule,
//                        DWORD  ul_reason_for_call,
//                        LPVOID lpReserved
// 					 )
// {
// 	switch (ul_reason_for_call)
// 	{
// 	case DLL_PROCESS_ATTACH:
//         break;
// 	case DLL_THREAD_ATTACH:
// 	case DLL_THREAD_DETACH:
//         break;
// 	case DLL_PROCESS_DETACH:
// 		break;
// 	}
// 	return TRUE;
// }
// #endif
