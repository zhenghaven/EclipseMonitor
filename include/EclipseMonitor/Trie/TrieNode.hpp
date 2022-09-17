// Copyright 2022 Tuan Tran
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "EclipseMonitor/Internal/SimpleRlp.hpp"

namespace EclipseMonitor
{

namespace TrieNode
{

class NodeBase
{
public:
    virtual SimpleObjects::Bytes Hash() = 0;
    virtual SimpleObjects::List Raw() = 0;
};

struct EmptyNode
{
    static bool IsEmptyNode(const NodeBase* node)
    {
        return !node;
    }

    static SimpleObjects::Bytes EmptyNodeRaw()
    {
        return SimpleObjects::Bytes();
    }

    static SimpleObjects::Bytes EmptyNodeHash()
    {
        // https://github.com/ethereum/go-ethereum/blob/master/trie/trie.go#L32
        SimpleObjects::Bytes emptyTrieHash = {
            0x56, 0xe8, 0x1f, 0x17, 0x1b, 0xcc, 0x55, 0xa6,
            0xff, 0x83, 0x45, 0xe6, 0x92, 0xc0, 0xf8, 0x6e,
            0x5b, 0x48, 0xe0, 0x1b, 0x99, 0x6c, 0xad, 0xc0,
            0x01, 0x62, 0x2f, 0xb5, 0xe3, 0x63, 0xb4, 0x21
        };
        return emptyTrieHash;
    }

}; // struct EmptyNode

struct Node
{
    static std::vector<uint8_t> Serialize(NodeBase* node)
    {
        SimpleObjects::Object raw;
        if (EmptyNode::IsEmptyNode(node))
        {
            raw = EmptyNode::EmptyNodeRaw();
        }
        else
        {
            raw = node->Raw();
        }

        SimpleRlp::OutputContainerType rlp = SimpleRlp::WriteRlp(raw);
        return rlp;
    }
}; // struct Node

} // namespace TrieNode
} // namespace EclipseMonitor