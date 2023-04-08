#ifndef __CHESS_DLL_H__
#define __CHESS_DLL_H__

#define EXPORT_DLL __declspec(dllexport)

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
    // 添加查找字符串
    EXPORT_DLL void AddEntry(const char* entry, int index);
    // 删除查找字符串
    EXPORT_DLL void RemoveEntry(const char* entry);
    // 设置需要被查找的字符串
    EXPORT_DLL void SetSrc(const char* src);
    // 返回匹配到的词条ID
    EXPORT_DLL void Match(int* output, int* output_count, int max_count);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __CHESS_DLL_H__
