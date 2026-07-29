#include "lcs.h"

#include <algorithm>
#include <string>
#include <vector>

std::string recLCS(const std::string& str1,
                   const std::string& str2,
                   int i,
                   int j)
{
    if (!i || !j) {
        return "";
    }

    if (str1[i - 1] == str2[j - 1]) {
        return recLCS(str1, str2, i - 1, j - 1) + str1[i - 1];
    }

    std::string lcs1 = recLCS(str1, str2, i - 1, j);
    std::string lcs2 = recLCS(str1, str2, i, j - 1);

    return (lcs1.length() > lcs2.length()) ? lcs1 : lcs2;
}

std::vector<std::vector<int>> PD_LCS(const std::string& str1,
                                     const std::string& str2)
{
    int n = str1.length();
    int m = str2.length();

    std::vector<std::vector<int>> table(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                table[i][j] = table[i - 1][j - 1] + 1;
            } else {
                table[i][j] = std::max(table[i - 1][j], table[i][j - 1]);
            }
        }
    }

    return table;
}

std::string STR_LCS(const std::string& str1,
                    const std::string& str2,
                    const std::vector<std::vector<int>>& table)
{
    std::string lcs;

    int i = str1.length();
    int j = str2.length();

    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            lcs.insert(0, 1, str1[i - 1]);
            --i;
            --j;
        } else if (table[i - 1][j] >= table[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    return lcs;
}
