#include <iostream>
#include "trie.h"

int main(int argc, char** argv)
{
    {
        // Test
        SimpleTrie::Trie trie;
        trie.AddEntry("aaaaaaaaaaaaaaaaaaa", 1);
        trie.AddEntry("aaaaaaabbbbbaaaaa", 2);
        trie.AddEntry("To", 3);
        trie.AddEntry("aaaaaaabbbaaaaa", 4);
        trie.AddEntry("ly sluggardiz", 5);
        trie.AddEntry("ly sluggardizaa", 6);
        trie.AddEntry("uggar", 7);
        trie.AddEntry("ly sl", 8);

        trie.SetSrc
        (
            "Cease to persuade, my loving Proteus: Home-keeping youth have ever homely wits."
            "Were't not affection chains thy tender days To the sweet glances of thy honour'd love,"
            "I rather would entreat thy company To see the wonders of the world abroad Than,"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbaaaaaaaaaaaaaaaaaaaabbaaaaaaaaaaaaaaaaa"
            "living dully sluggardiz'd at home, Wear out thy youth with shapeless idleness."
        );

        std::cout << trie.GetNodeInfo() << "\n";

        int result[8];
        int count = 0;
        trie.Match(result, &count, 8);
        std::cout << "Total Count : " << count << "\n";
        for (int i = 0; i < count; i++)
            std::cout << result[i] << " ";
        std::cout << std::endl;
    }
    return 0;
}
