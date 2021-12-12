# -*- coding: UTF-8 -*-
def get_bc(pattern):
    bc = dict()
    for i in range(len(pattern) - 1):
        char = pattern[i]
        bc[char] = i + 1
    return bc


def get_gs(pattern):
    gs = dict()
    gs[''] = 0

    # suf_len 用于标记后缀长度
    for suf_len in range(len(pattern)):
        suffix = pattern[len(pattern) - suf_len - 1:]
        # j 用于标记可用于匹配的位置
        for j in range(len(pattern) - suf_len - 1):
            substr = pattern[j:j + suf_len + 1]
            if suffix == substr:
                gs[suffix] = len(pattern) - j - suf_len - 1

    for suf_len in range(len(pattern)):
        suffix = pattern[len(pattern) - suf_len - 1:]
        if suffix in gs: continue
        gs[suffix] = gs[suffix[1:]]

    return gs


def bm(string, pattern, bc, gs):
    # i 用于标记当前模式串和主串哪个位置左对齐。
    i = 0 
    # j 用于标记当前模式串匹配到哪个位置；从右往左遍历匹配。
    j = len(pattern)

    while i < len(string) - len(pattern) and (j > 0):
            a = string[i + j - 1]
            b = pattern[j - 1]
            if a == b:
                j = j - 1
            else:
                i = i + max(gs.setdefault(pattern[j:], len(pattern)), j - bc.setdefault(a, 0))
                j = len(pattern)
            # 匹配成功返回匹配位置
            if j == 0:
                return i
    # 匹配失败返回 None
    return -1


if __name__ == '__main__':
    string = 'here is a simple example'
    pattern = 'efadef'

    bc = get_bc(pattern)  # 坏字符表
    gs = get_gs(pattern)  # 好后缀表

    print(gs)

    x = bm(string, pattern, bc, gs)

    print(x)