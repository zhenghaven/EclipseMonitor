// Copyright 2022 Tuan Tran
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <gtest/gtest.h>

#include <EclipseMonitor/Eth/TransactionMgr.hpp>
#include <SimpleObjects/SimpleObjects.hpp>

#include "EthTransaction.hpp"

namespace EclipseMonitor_Test
{
	extern size_t g_numOfTestFile;
}

using namespace EclipseMonitor_Test;
using namespace EclipseMonitor::Eth;


GTEST_TEST(TestEthTransactionMgr, CountTestFile)
{
	static auto tmp = ++g_numOfTestFile;
	(void)tmp;
}


GTEST_TEST(TestEthTransactionMgr, LegacyTxn_15415840)
{
	const SimpleObjects::Bytes& txnBytes = LegacyTxn_15415840();
	TransactionMgr mgr = TransactionMgr::FromBytes(txnBytes);

	const SimpleObjects::Bytes& contractAddr = mgr.GetContractAddr();
	auto expContractAddr = SimpleObjects::Bytes({
		0x29U, 0x2fU, 0x04U, 0xa4U, 0x45U, 0x06U, 0xc2U, 0xfdU,
		0x49U, 0xbaU, 0xc0U, 0x32U, 0xe1U, 0xcaU, 0x14U, 0x8cU,
		0x35U, 0xa4U, 0x78U, 0xc8U
	});

	EXPECT_EQ(expContractAddr, contractAddr);

	const SimpleObjects::Bytes& data = mgr.GetContactParams();
	auto expData = SimpleObjects::Bytes({});

	EXPECT_EQ(expData, data);
}


GTEST_TEST(TestEthTransactionMgr, AccessListTxn_15415840)
{
	const SimpleObjects::Bytes& txnBytes = AccessListTxn_15415840();
	TransactionMgr mgr = TransactionMgr::FromBytes(txnBytes);

	const SimpleObjects::Bytes& contractAddr = mgr.GetContractAddr();
	auto expContractAddr = SimpleObjects::Bytes({
		0xa1U, 0x00U, 0x6dU, 0x00U, 0x51U, 0xa3U, 0x5bU, 0x00U,
		0x00U, 0xf9U, 0x61U, 0xa8U, 0x00U, 0x00U, 0x00U, 0x00U,
		0x9eU, 0xa8U, 0xd2U, 0xdbU
	});

	EXPECT_EQ(expContractAddr, contractAddr);

	const SimpleObjects::Bytes& data = mgr.GetContactParams();
	auto expData = SimpleObjects::Bytes({
		0x01U, 0x00U, 0x14U, 0x96U, 0x1cU, 0xb0U, 0xb3U, 0x9aU,
		0xf5U, 0x01U, 0x09U, 0x29U, 0x0aU, 0x6aU, 0x74U, 0x60U,
		0xb3U, 0x08U, 0xeeU, 0x3fU, 0x19U, 0x02U, 0x3dU, 0x2dU,
		0x00U, 0xdeU, 0x60U, 0x4bU, 0xcfU, 0x5bU, 0x42U, 0x01U,
		0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x38U, 0xcaU,
		0x28U, 0x12U, 0xbeU, 0x66U, 0xffU, 0x53U, 0xa5U, 0x04U,
		0x00U, 0x05U, 0x05U, 0x06U, 0x00U, 0x00U, 0x00U, 0x00U,
		0x00U, 0x00U, 0x00U, 0x07U, 0x19U, 0xf9U, 0x2dU, 0xf6U,
		0x7bU, 0x41U, 0x00U, 0x74U, 0xc9U, 0x9fU, 0x3fU, 0x53U,
		0x31U, 0x67U, 0x6fU, 0x6aU, 0xecU, 0x27U, 0x56U, 0xe1U,
		0xf3U, 0x9bU, 0x4fU, 0xc0U, 0x29U, 0xa8U, 0x3eU, 0x01U,
		0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		0x00U, 0x00U, 0x00U, 0x33U, 0x73U, 0x6eU, 0x6aU, 0x98U,
		0xc2U, 0xb0U, 0x68U, 0x1dU, 0x8bU, 0xf0U, 0x77U, 0x67U,
		0x82U, 0x6eU, 0xa8U, 0xbdU, 0x3bU, 0x11U, 0xb0U, 0xcaU,
		0x42U, 0x16U, 0x31U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		0x34U, 0xf5U, 0x71U, 0xf5U, 0x8aU, 0x66U, 0xd6U, 0x36U,
		0xfeU, 0x2dU, 0x55U, 0x25U, 0x6aU, 0xd5U, 0x81U, 0x56U,
		0x55U, 0x76U, 0x05U, 0x27U, 0x4bU, 0x33U, 0x92U, 0xf8U,
		0xbfU, 0xe0U, 0x5eU, 0x1eU, 0x4fU, 0xcaU, 0x8aU, 0x00U,
		0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x38U, 0xcaU,
		0x28U, 0x12U, 0xbeU, 0x66U, 0xffU, 0x53U, 0xa5U, 0x29U,
		0x0aU, 0x6aU, 0x74U, 0x60U, 0xb3U, 0x08U, 0xeeU, 0x3fU,
		0x19U, 0x02U, 0x3dU, 0x2dU, 0x00U, 0xdeU, 0x60U, 0x4bU,
		0xcfU, 0x5bU, 0x42U
	});

	EXPECT_EQ(expData, data);
}


GTEST_TEST(TestEthTransactionMgr, DynamicFeeTxn_15415840)
{
	const SimpleObjects::Bytes& txnBytes = DynamicFeeTxn_15415840();
	TransactionMgr mgr = TransactionMgr::FromBytes(txnBytes);

	const SimpleObjects::Bytes& contractAddr = mgr.GetContractAddr();
	auto expContractAddr = SimpleObjects::Bytes({
		0x9fU, 0x8fU, 0x72U, 0xaaU, 0x93U, 0x04U, 0xc8U, 0xb5U,
		0x93U, 0xd5U, 0x55U, 0xf1U, 0x2eU, 0xf6U, 0x58U, 0x9cU,
		0xc3U, 0xa5U, 0x79U, 0xa2U
	});

	EXPECT_EQ(contractAddr, expContractAddr);

	const SimpleObjects::Bytes& data = mgr.GetContactParams();
	auto expData = SimpleObjects::Bytes({
		0xa9U, 0x05U, 0x9cU, 0xbbU, 0x00U, 0x00U, 0x00U, 0x00U,
		0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		0xccU, 0x81U, 0x43U, 0x00U, 0x17U, 0x75U, 0x68U, 0xe1U,
		0x74U, 0x3dU, 0x67U, 0xaaU, 0x49U, 0xc5U, 0x3eU, 0x9fU,
		0x28U, 0xeeU, 0x56U, 0xd1U, 0x00U, 0x00U, 0x00U, 0x00U,
		0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		0x00U, 0x00U, 0x00U, 0x00U, 0x37U, 0x3bU, 0xccU, 0xe9U,
		0xbeU, 0x0eU, 0x00U, 0x00U
	});

	EXPECT_EQ(data, expData);
}