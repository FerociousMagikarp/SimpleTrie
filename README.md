# SimpleTrie

## 简介
本来的需求是给定一些词条，然后去word里匹配这些词条。解析word这件事是用python搞的。
但是匹配的时候，如果遍历词条，再对每个词条使用if entry in s，这样做太慢了。所以就用C++写了这么个东西。
结果就是简单满足这个需求了，但是这个接口看起来却有点莫名其妙,
比如AddEntry接口中的那个index。留着这个库放在这，万一以后想扩展呢，比如把index改成个什么value，
做成一个key-value查询的结构什么的。

## 调用示例
编译出的dll使用python进行调用

```python
dll = ctypes.CDLL(path) # path是dll的路径

# 添加词条
dll.AddEntry(bytes('aaaaa', encoding='ascii'), 1)
dll.AddEntry(bytes('aabbb', encoding='ascii'), 2)
dll.AddEntry(bytes('ccccc', encoding='ascii'), 3)
dll.AddEntry(bytes('ddedd', encoding='ascii'), 4)
dll.AddEntry(bytes('eeeee', encoding='ascii'), 5)

# 设置需要匹配的文本
dll.SetSrc(bytes('aaaaaaaaabbbbbbaaaaaccccaccddeeeeeeee', encoding='ascii'))

# 匹配
types_int_array = ctypes.c_int * 5
match_res = types_int_array()
count = ctypes.c_int(0)

dll.Match(match_res, ctypes.byref(count), 5)
# 应该会输出 1 2 5
for i in range(count.value):
    print(match_res[i])
```

## 注意
目前没有实现RemoveEntry接口。（过两天再说吧:dog:）（过两天是多长时间:pig:）
