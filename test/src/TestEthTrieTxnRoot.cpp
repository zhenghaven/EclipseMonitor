// Copyright 2022 Tuan Tran
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <EclipseMonitor/Eth/Trie/Trie.hpp>

#include "EthTransactions.hpp"

namespace EclipseMonitor_Test
{
	extern size_t g_numOfTestFile;
}

using namespace EclipseMonitor_Test;

using namespace EclipseMonitor::Eth::Trie;

// converts a uint64_t to byte vector
using IntWriter = SimpleRlp::EncodePrimitiveIntValue<
	uint64_t,
	SimpleRlp::Endian::little,
	false
>;

GTEST_TEST(TestEthTrieTxnRoot, CountTestFile)
{
	static auto tmp = ++g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestEthTrieTxnRoot, TestTransactionsRootBlock15415840)
{
	std::vector<uint8_t> key;
	SimpleObjects::Bytes keyBytes;
	SimpleObjects::Bytes encodedKey;
	SimpleObjects::Bytes value;
	PatriciaTrie trie;

	const SimpleObjects::Bytes& expected = GetTransactionsRoot_15415840();
	const auto& txns = GetEthTransactions_15415840();

	// insert transactions
	for(uint64_t i = 0; i < txns.size(); i++)
	{
		key.clear();

		IntWriter::Encode(key, i);
		keyBytes = SimpleObjects::Bytes(key);
		encodedKey = SimpleObjects::Bytes(SimpleRlp::WriteRlp(keyBytes));

		value = txns[i];
		trie.Put(encodedKey, value);
	}

	EXPECT_EQ(expected, trie.Hash());
}


GTEST_TEST(TestEthTrieTxnRoot, TestTransactionsRootBlock15209997)
{
	std::vector<uint8_t> key;
	SimpleObjects::Bytes keyBytes;
	SimpleObjects::Bytes encodedKey;
	SimpleObjects::Bytes value;
	PatriciaTrie trie;

	const SimpleObjects::Bytes& expected = GetTransactionsRoot_15209997();
	const auto& txns = GetEthTransactions_15209997();

	// insert transactions
	for(uint64_t i = 0; i < txns.size(); i++)
	{
		key.clear();

		IntWriter::Encode(key, i);
		keyBytes = SimpleObjects::Bytes(key);
		encodedKey = SimpleObjects::Bytes(SimpleRlp::WriteRlp(keyBytes));

		value = txns[i];
		trie.Put(encodedKey, value);
	}
	EXPECT_EQ(expected, trie.Hash());
}
