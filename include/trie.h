#pragma once

#include <string>

#include "trie_node.h"

namespace SimpleTrie
{
    class Trie
    {
    public:
        Trie() : m_root_node(std::make_unique<TrieNode>()) {}
        ~Trie() = default;
        Trie(const Trie&) = delete;
        Trie(Trie&&) = delete;
        Trie& operator=(const Trie&) = delete;
        Trie& operator=(Trie&&) = delete;

        void AddEntry(const char* entry, int index);
        void RemoveEntry(const char* entry);
        void Match(int* output, int* output_count, int max_count);

        inline void SetSrc(std::string src) { m_src = std::move(src); }

        std::string GetNodeInfo();

    private:
        std::string m_src = "";
        std::unique_ptr<TrieNode> m_root_node;
    };
}
