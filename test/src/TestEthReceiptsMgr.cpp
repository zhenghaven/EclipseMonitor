// Copyright 2022 Tuan Tran
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <EclipseMonitor/Eth/Keccak256.hpp>
#include <EclipseMonitor/Eth/ReceiptsMgr.hpp>
#include <SimpleObjects/SimpleObjects.hpp>

#include "BlockData.hpp"
#include "EthReceipt.hpp"

namespace EclipseMonitor_Test
{
	extern size_t g_numOfTestFile;
}

using namespace EclipseMonitor_Test;
using namespace EclipseMonitor::Eth;

GTEST_TEST(TestEthReceiptsMgr, CountTestFile)
{
	static auto tmp = ++g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestEthReceiptsMgr, LegacyReceipt_15415840)
{
	const SimpleObjects::Bytes& receiptBytes = LegacyReceipt_15415840();
	Receipt mgr = Receipt::FromBytes(receiptBytes);

	const auto& receiptLogs = mgr.GetLogEntries();

	EXPECT_EQ(receiptLogs.size(), 0);
}

GTEST_TEST(TestEthReceiptsMgr, AccessListReceipt_15415840)
{
	const SimpleObjects::Bytes& receiptBytes = AccessListReceipt_15415840();
	Receipt mgr = Receipt::FromBytes(receiptBytes);

	const auto& receiptLogs = mgr.GetLogEntries();
	EXPECT_EQ(receiptLogs.size(), 12);

	ContractAddr expectedLogIndex11Address = {
		0x29, 0x0a, 0x6a, 0x74, 0x60, 0xb3, 0x08, 0xee,
		0x3f, 0x19, 0x02, 0x3d, 0x2d, 0x00, 0xde, 0x60,
		0x4b, 0xcf, 0x5b, 0x42
	};
	EXPECT_EQ(receiptLogs[11].m_contractAddr, expectedLogIndex11Address);

	EXPECT_EQ(receiptLogs[11].m_topics.size(), 3);

	std::vector<uint8_t> expectedLogIndex11Data = {
		0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x38U,
		0xcaU, 0x28U, 0x12U, 0xbeU, 0x66U, 0xffU, 0x53U, 0xa5U,
		0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU,
		0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU,
		0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU,
		0xf8U, 0xd0U, 0x95U, 0x1bU, 0x18U, 0x1aU, 0x01U, 0x66U,
		0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		0x00U, 0x00U, 0x00U, 0x00U, 0x05U, 0xb3U, 0x1fU, 0xbfU,
		0xbaU, 0xd4U, 0x84U, 0x83U, 0x0bU, 0xcbU, 0xe9U, 0x38U,
		0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0xbdU, 0x13U,
		0x92U, 0x7bU, 0xb8U, 0xbbU, 0x27U, 0x0dU, 0x9eU, 0xf1U,
		0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU,
		0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU,
		0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU,
		0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xfeU, 0xd6U, 0xbcU
	};
	EXPECT_EQ(receiptLogs[11].m_logData, expectedLogIndex11Data);
}

GTEST_TEST(TestEthReceiptsMgr, DynamicFeeReceipt_15415840)
{
	const SimpleObjects::Bytes& receiptBytes = DynamicFeeReceipt_15415840();
	Receipt mgr = Receipt::FromBytes(receiptBytes);

	const auto& receiptLogs = mgr.GetLogEntries();
	EXPECT_EQ(receiptLogs.size(), 1);

	ContractAddr expectedLogEntryAddress = {
		0x9fU, 0x8fU, 0x72U, 0xaaU, 0x93U, 0x04U, 0xc8U, 0xb5U,
		0x93U, 0xd5U, 0x55U, 0xf1U, 0x2eU, 0xf6U, 0x58U, 0x9cU,
		0xc3U, 0xa5U, 0x79U, 0xa2U
	};

	EXPECT_EQ(receiptLogs[0].m_contractAddr, expectedLogEntryAddress);

	EXPECT_EQ(receiptLogs[0].m_topics.size(), 3);

	std::vector<uint8_t> expectedData = {
		0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		0x37U, 0x3bU, 0xccU, 0xe9U, 0xbeU, 0x0eU, 0x00U, 0x00U
	};
	EXPECT_EQ(receiptLogs[0].m_logData, expectedData);
}

GTEST_TEST(TestEthReceiptsMgr, TopicTest)
{
	std::string event("Revoke(bytes32)");
	std::array<uint8_t, 32> hashedEvent = Keccak256(event);

	std::array<uint8_t, 32> expected = {
		0x22U, 0xb3U, 0xf5U, 0x49U, 0x5eU, 0xf9U, 0xc5U, 0x6aU,
		0xd6U, 0xe2U, 0x70U, 0xe8U, 0xc8U, 0x4fU, 0x1aU, 0x2fU,
		0x0eU, 0x0bU, 0xd8U, 0x3cU, 0xcbU, 0x69U, 0x88U, 0xa1U,
		0x84U, 0x23U, 0x14U, 0x72U, 0x7aU, 0x44U, 0x1dU, 0x5cU
	};

	EXPECT_EQ(hashedEvent, expected);
}

GTEST_TEST(TestEthReceiptsMgr, EventTest1)
{
	const SimpleObjects::Bytes& receiptBytes = TestReceipt1();
	Receipt mgr = Receipt::FromBytes(receiptBytes);

	std::vector<std::array<uint8_t, 32> > topics(1);
	std::string event("Revoke(bytes32)");
	topics[0] = Keccak256(event);

	ContractAddr contractAddress = {
		0xe3U, 0x3bU, 0x30U, 0xcdU, 0xe1U, 0xaaU, 0xe0U, 0x64U,
		0x09U, 0xe8U, 0xaaU, 0xdfU, 0xa5U, 0xb5U, 0xfcU, 0xfcU,
		0x8dU, 0x8dU, 0xdaU, 0x7cU
	};

	auto logEntiresRefs = mgr.SearchEvents(
		contractAddress,
		topics.cbegin(), topics.cend()
	);

	ASSERT_GT(logEntiresRefs.size(), 0);

	std::vector<uint8_t> expectedEventData = {
		0x9fU, 0x8fU, 0x72U, 0xaaU, 0x93U, 0x04U, 0xc8U, 0xb5U,
		0x93U, 0xd5U, 0x55U, 0xf1U, 0x2eU, 0xf6U, 0x58U, 0x9cU,
		0xc3U, 0xa5U, 0x79U, 0xa2U, 0x9fU, 0x8fU, 0x72U, 0xaaU,
		0x93U, 0x04U, 0xc8U, 0xb5U, 0x93U, 0xd5U, 0x9fU, 0x8fU
	};
	EXPECT_EQ(logEntiresRefs[0].get().m_logData, expectedEventData);
}

GTEST_TEST(TestEthReceiptsMgr, EventTest2)
{
	const SimpleObjects::Bytes& receiptBytes = TestReceipt2();
	Receipt mgr = Receipt::FromBytes(receiptBytes);

	std::vector<std::array<uint8_t, 32> > topics(1);
	std::string event("Revoke(bytes32,uint64,bool)");
	topics[0] = Keccak256(event);

	ContractAddr contractAddress = {
		0x4cU, 0x66U, 0x08U, 0xcdU, 0xe7U, 0x5eU, 0x62U, 0x20U,
		0x82U, 0x8eU, 0x3fU, 0x37U, 0x61U, 0x66U, 0x3bU, 0xdbU,
		0x86U, 0x05U, 0x38U, 0xe6U
	};

	auto logEntiresRefs = mgr.SearchEvents(
		contractAddress,
		topics.cbegin(), topics.cend()
	);

	ASSERT_GT(logEntiresRefs.size(), 0);

	// test something shouldn't be in the log

	std::string event2("Revoke(bytes32,uint64)");
	topics[0] = Keccak256(event2);

	logEntiresRefs = mgr.SearchEvents(
		contractAddress,
		topics.cbegin(), topics.cend()
	);

	ASSERT_EQ(logEntiresRefs.size(), 0);
}

GTEST_TEST(TestEthReceiptsMgr, EventTest3)
{
	const SimpleObjects::Bytes& receiptBytes = TestReceipt3();
	Receipt mgr = Receipt::FromBytes(receiptBytes);

	std::vector<std::array<uint8_t, 32> > topics(1);
	std::string event("Revoke(bytes[])");
	topics[0] = Keccak256(event);

	ContractAddr contractAddress = {
		0x51U, 0x3aU, 0xafU, 0xe1U, 0x14U, 0x37U, 0x20U, 0x77U,
		0x19U, 0x45U, 0xbcU, 0x3aU, 0x43U, 0x0dU, 0x7fU, 0x41U,
		0x71U, 0xf2U, 0xd2U, 0x48U
	};

	auto logEntiresRefs = mgr.SearchEvents(
		contractAddress,
		topics.cbegin(), topics.cend()
	);

	ASSERT_GT(logEntiresRefs.size(), 0);
}


GTEST_TEST(TestEthReceiptsMgr, ReceiptsMgr_B15415840)
{
	const auto headerB15415840 =
		BlockData::ReadBinary(
			BlockData::GetRlpFilePath("mainnet_b_15415840.header")
		);
	const auto receiptsB15415840 =
		BlockData::ReadRlp("mainnet_b_15415840.receipts");

	const HeaderMgr headerMgr(headerB15415840, 0);

	ReceiptsMgr mgr(receiptsB15415840.AsList());

	EXPECT_EQ(
		mgr.GetRootHashBytes(),
		headerMgr.GetRawHeader().get_ReceiptsRoot()
	);
}


GTEST_TEST(TestEthReceiptsMgr, ReceiptsMgr_B15209997)
{
	const auto headerB15209997 =
		BlockData::ReadBinary(
			BlockData::GetRlpFilePath("mainnet_b_15209997.header")
		);
	const auto receiptsB15209997 =
		BlockData::ReadRlp("mainnet_b_15209997.receipts");

	const HeaderMgr headerMgr(headerB15209997, 0);

	ReceiptsMgr mgr(receiptsB15209997.AsList());

	EXPECT_EQ(
		mgr.GetRootHashBytes(),
		headerMgr.GetRawHeader().get_ReceiptsRoot()
	);
}
