#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>

namespace SimpleTrie
{
    constexpr int NODE_CH_COUNT = 10;

    enum TrieNodeFlag : std::uint8_t
    {
        TrieNodeFlag_UseIndex = (1 << 0),
    };
    using TrieNodeFlags = std::uint8_t;

    class TrieNode
    {
    public:
        TrieNode() = default;
        // 用单个字符创建节点，默认为中间节点
        explicit TrieNode(char c);
        // 用字符串创建节点，每个节点最多NODE_CH_COUNT个字符，超了用下一个
        explicit TrieNode(const char* s);
        // 用字符、索引创建节点
        TrieNode(char c, int index);
        // 用字符串、索引创建节点
        TrieNode(const char* s, int index);
        ~TrieNode() = default;

        void AddEntry(const char* s, int index);
        void RemoveEntry(const char* s);

    private:

        friend class Trie;

        char          m_ch[NODE_CH_COUNT];
        std::uint8_t  m_ch_length = 0;
        TrieNodeFlags m_flags     = 0;
        int           m_index     = -1;
        std::unordered_map<char, std::unique_ptr<TrieNode>> m_children;
    };
}
