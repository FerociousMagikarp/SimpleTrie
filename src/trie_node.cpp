#include "trie_node.h"
#include <cstdint>
#include <memory>

namespace SimpleTrie
{
    TrieNode::TrieNode(char c)
        : m_ch_length(1)
    {
        m_ch[0] = c;
    }

    TrieNode::TrieNode(const char* s)
    {
        for (int i = 0; i < NODE_CH_COUNT; i++)
        {
            const char c = *s;
            if (c == '\0')
            {
                m_ch_length = static_cast<std::uint8_t>(i);
                break;
            }
            m_ch[i] = c;
            ++s;
        }
        if (*s != '\0') // 说明后面还有东西
        {
            auto child = std::make_unique<TrieNode>(s);
            m_children.insert(std::pair(*s, std::move(child)));
        }
        m_ch_length = m_ch_length == 0 ? NODE_CH_COUNT : m_ch_length;
    }

    TrieNode::TrieNode(char c, int index)
        : m_ch_length(1), m_flags(TrieNodeFlag_UseIndex), m_index(index)
    {
        m_ch[0] = c;
    }

    TrieNode::TrieNode(const char* s, int index)
        : m_index(index)
    {
        for (int i = 0; i < NODE_CH_COUNT; i++)
        {
            const char c = *s;
            if (c == '\0')
            {
                m_ch_length = static_cast<std::uint8_t>(i);
                break;
            }
            m_ch[i] = c;
            ++s;
        }
        if (*s != '\0') // 说明后面还有东西
        {
            auto child = std::make_unique<TrieNode>(s, index);
            m_children.insert(std::pair(*s, std::move(child)));
            m_ch_length = NODE_CH_COUNT;
        }
        else
        {
            m_index = index;
            m_flags = TrieNodeFlag_UseIndex;
            m_ch_length = m_ch_length == 0 ? NODE_CH_COUNT : m_ch_length;
        }
    }

    void TrieNode::AddEntry(const char *s, int index)
    {
        std::uint8_t new_length = m_ch_length;
        for (std::uint8_t i = 0; i < m_ch_length; i++)
        {
            const char c = *s;
            if (c == '\0')
            {
                new_length = i;
                break;
            }
            if (m_ch[i] == c)
                ++s;
            else
            {
                new_length = i;
                break;
            }
        }
        const char c = *s;
        // 如果new_length与m_ch_length不相等，有两种情况
        // 一种情况是中间某个节点的值不一样了
        // 另一种情况是s到头了
        if (new_length < m_ch_length)
        {
            // 需要裂开节点
            const char c = m_ch[new_length];
            char ch[NODE_CH_COUNT] = { '\0' };
            auto child = std::make_unique<TrieNode>();
            for (std::uint8_t i = 0; i < m_ch_length - new_length; i++)
            {
                child->m_ch[i] = m_ch[i + new_length];
            }
            child->m_ch_length = m_ch_length - new_length;
            child->m_flags = m_flags;
            child->m_index = m_index;
            for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
            {
                child->m_children[iter->first] = std::move(iter->second);
            }
            m_children.clear();
            m_ch_length = new_length;

            const char cs = *s;
            if (cs == '\0')
            {
                // s到头了
                m_flags |= TrieNodeFlag_UseIndex;
                m_index = index;
            }
            else
            {
                // s还有后续内容
                // 这个index移到c这个节点了，所以这里置空
                m_flags &= ~TrieNodeFlag_UseIndex;
                m_index = -1;
                auto other_child = std::make_unique<TrieNode>(s, index);
                m_children.insert(std::pair(cs, std::move(other_child)));
            }
            // 走到这cs肯定跟c不一样，所以就不需要再判断了
            m_children[c] = std::move(child);
        }
        else
        {
            if (c != '\0')
            {
                auto iter = m_children.find(c);
                if (iter == m_children.end())
                {
                    auto child = std::make_unique<TrieNode>(s, index);
                    m_children.insert(std::pair(c, std::move(child)));
                }
                else
                {
                    iter->second->AddEntry(s, index);
                }
            }
        }
    }

    void TrieNode::RemoveEntry(const char *s)
    {
        
    }
}
