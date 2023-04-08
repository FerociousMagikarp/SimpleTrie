#include "trie.h"
#include "trie_node.h"
#include <set>
#include <vector>
#include <functional>
#include <sstream>

namespace SimpleTrie
{
    void Trie::AddEntry(const char* entry, int index)
    {
        char c = *entry;
        auto iter = m_root_node->m_children.find(c);
        if (iter == m_root_node->m_children.end())
        {
            auto child = std::make_unique<TrieNode>(entry, index);
            m_root_node->m_children.insert(std::pair(c, std::move(child)));
        }
        else
        {
            iter->second->AddEntry(entry, index);
        }
    }

    void Trie::RemoveEntry(const char *entry)
    {

    }

    void Trie::Match(int* output, int* output_count, int max_count)
    {
        if (m_src.empty() || max_count <= 0)
        {
            output_count = 0;
            return;
        }
        // 保证一下顺序
        std::set<int> final_match;
        // 表示匹配到哪个节点了，该匹配第几个字符
        std::vector<std::pair<TrieNode*, int>> matching;
        // 中间需要添加的数组
        std::vector<std::pair<TrieNode*, int>> next_matching;
        for (const char c : m_src)
        {
            // 继续匹配之前能匹配的内容
            for (auto match_iter = matching.begin(); match_iter != matching.end();)
            {
                TrieNode* node = match_iter->first;
                // 如果字符匹配数没超过这个节点就继续匹配
                if (match_iter->second < node->m_ch_length)
                {
                    if (c == node->m_ch[match_iter->second])
                    {
                        match_iter->second++;
                        ++match_iter;
                    }
                    else
                    {
                        // 删除以后更新迭代器
                        match_iter = matching.erase(match_iter);
                    }
                }
                else
                {
                    // 如果超出范围就判断是否可以将index塞进返回值
                    if (node->m_flags & TrieNodeFlag_UseIndex)
                    {
                        final_match.insert(node->m_index);
                    }
                    // 然后再找到下一个能匹配的节点塞进这个数组，不过要之后塞，否则迭代器可能会失效
                    auto next_iter = node->m_children.find(c);
                    if (next_iter != node->m_children.end())
                    {
                        next_matching.push_back(std::pair(next_iter->second.get(), 1));
                    }
                    // 删除当前的数据
                    match_iter = matching.erase(match_iter);
                }
            }
            // 将需要添加的内容都添加到matching容器中
            if (!next_matching.empty())
            {
                matching.insert(matching.end(), next_matching.begin(), next_matching.end());
                next_matching.clear();
            }

            // 判断一下第一个字符能不能匹配上
            auto iter = m_root_node->m_children.find(c);
            if (iter != m_root_node->m_children.end())
            {
                // 很丑但是就这么用了
                TrieNode* node = iter->second.get();
                if (node->m_ch_length == 1 && (node->m_flags & TrieNodeFlag_UseIndex))
                {
                    final_match.insert(node->m_index);
                }
                // 满足上面的条件后面还可能有东西，所以不用else
                if (node->m_ch_length > 1 || !node->m_children.empty())
                {
                    matching.push_back(std::pair(node, 1));
                }
            }
        }

        // 所有匹配结束后判断matching里还有没有，如果有就看看有没有能塞到结果中的
        if (!matching.empty())
        {
            for (auto iter = matching.cbegin(); iter != matching.cend(); ++iter)
            {
                TrieNode* node = iter->first;
                if (iter->second >= node->m_ch_length && (node->m_flags & TrieNodeFlag_UseIndex))
                {
                    final_match.insert(node->m_index);
                }
            }
        }

        // 返回
        int size = static_cast<int>(final_match.size());
        int i = 0;
        if (size > max_count)
        {
            // 超了上面还继续计算，这里有点问题
            *output_count = max_count;
            for (int index : final_match)
            {
                *(output + i++) = index;
                if (i >= max_count)
                    break;
            }
        }
        else
        {
            *output_count = size;
            for (int index : final_match)
            {
                *(output + i++) = index;
            }
        }
    }

    std::string Trie::GetNodeInfo()
    {
        std::string result("TrieNodes : \n");
        result.reserve(512);
        std::function<void(const std::unordered_map<char, std::unique_ptr<TrieNode>>&, unsigned int)> dfs = 
        [this, &result, &dfs](const std::unordered_map<char, std::unique_ptr<TrieNode>>& nodes, unsigned int level)->void
        {
            for (auto iter = nodes.cbegin(); iter != nodes.cend(); ++iter)
            {
                // 补充空格
                result.insert(result.end(), level * 4, ' ');
                for (std::uint8_t i = 0; i < iter->second->m_ch_length; i++)
                {
                    result += iter->second->m_ch[i];
                }
                if (iter->second->m_flags & TrieNodeFlag_UseIndex)
                {
                    std::stringstream ss;
                    std::string tmp;
                    ss << iter->second->m_index;
                    ss >> tmp;
                    result += "(";
                    result += tmp;
                    result += ")";
                }
                result += "\n";
                dfs(iter->second->m_children, level + 1);
            }
        };

        dfs(m_root_node->m_children, 1);

        return result;
    }
}
