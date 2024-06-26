// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <cstdint>

#include <vector>

#include <gtest/gtest.h>

#include <EclipseMonitor/Eth/AbiParser.hpp>

namespace EclipseMonitor_Test
{
	extern size_t g_numOfTestFile;
}

using namespace EclipseMonitor_Test;
using namespace EclipseMonitor::Eth;

GTEST_TEST(TestEthAbiParser, CountTestFile)
{
	static auto tmp = ++EclipseMonitor_Test::g_numOfTestFile;
	(void)tmp;
}

GTEST_TEST(TestEthAbiParser, ParseIntegerPrimitive)
{
	using AbiParserUint64 =
		AbiParser<
			SimpleObjects::ObjCategory::Integer,
			AbiUInt64
		>;

	{
		std::vector<uint8_t> input = {
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0xFFU,
		};
		// test HeadToPrimitive
		{
			auto expRes = std::make_tuple(
				static_cast<uint64_t>(0xFFULL),
				input.end(),
				1
			);

			auto actRes = AbiParserUint64().HeadToPrimitive(
					input.begin(), input.end()
				);

			EXPECT_EQ(expRes, actRes);
		}
		// test ToPrimitive
		{
			auto expRes = std::make_tuple(
				static_cast<uint64_t>(0xFFULL),
				input.end()
			);

			auto actRes = AbiParserUint64().ToPrimitive(
					input.begin(), input.end(), input.begin()
				);

			EXPECT_EQ(expRes, actRes);
		}
	}

	{
		std::vector<uint8_t> input = {
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
		};
		auto expRes = std::make_tuple(
			static_cast<uint64_t>(0xFEDCBA9876543210ULL),
			input.end()
		);

		auto actRes = AbiParserUint64().ToPrimitive(
				input.begin(), input.end(), input.begin()
			);

		EXPECT_EQ(expRes, actRes);
	}

	// Error - non-zero bytes in the skipped bytes
	{
		std::vector<uint8_t> input = {
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x01U,
			0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
		};

		auto testProg = [&input]() {
			AbiParserUint64().ToPrimitive(
					input.begin(), input.end(), input.begin()
				);
		};

		EXPECT_THROW(testProg();, EclipseMonitor::Exception);
	}

	// Error - not enough input bytes
	{
		std::vector<uint8_t> input = {
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
		};

		auto testProg = [&input]() {
			AbiParserUint64().ToPrimitive(
					input.begin(), input.end(), input.begin()
				);
		};

		input.resize(31);
		EXPECT_THROW(testProg();, EclipseMonitor::Exception);

		input.resize(15);
		EXPECT_THROW(testProg();, EclipseMonitor::Exception);
	}
}

GTEST_TEST(TestEthAbiParser, ParseBoolPrimitive)
{
	using AbiParserBool =
		AbiParser<SimpleObjects::ObjCategory::Bool>;

	// false
	{
		std::vector<uint8_t> input = {
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		};
		// test HeadToPrimitive
		{
			auto expRes = std::make_tuple(
				static_cast<bool>(false),
				input.end(),
				1
			);

			auto actRes = AbiParserBool().HeadToPrimitive(
					input.begin(), input.end()
				);

			EXPECT_EQ(expRes, actRes);
		}
		// test ToPrimitive
		{
			auto expRes = std::make_tuple(
				static_cast<bool>(false),
				input.end()
			);

			auto actRes = AbiParserBool().ToPrimitive(
					input.begin(), input.end(), input.begin()
				);

			EXPECT_EQ(expRes, actRes);
		}
	}

	// true
	{
		std::vector<uint8_t> input = {
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x01U,
		};
		auto expRes = std::make_tuple(
			static_cast<bool>(true),
			input.end()
		);

		auto actRes = AbiParserBool().ToPrimitive(
				input.begin(), input.end(), input.begin()
			);

		EXPECT_EQ(expRes, actRes);
	}

	// invalid bool value
	{
		std::vector<uint8_t> input = {
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x02U,
		};

		auto testProg = [&input]() {
			AbiParserBool().ToPrimitive(
				input.begin(), input.end(), input.begin()
			);
		};

		EXPECT_THROW(testProg();, EclipseMonitor::Exception);
	}
}

GTEST_TEST(TestEthAbiParser, ParseStaticBytesPrimitive)
{
	using AbiParserBytes =
		AbiParser<
			SimpleObjects::ObjCategory::Bytes,
			std::false_type
		>;
	using AbiParserBytes16 =
		AbiParser<
			SimpleObjects::ObjCategory::Bytes,
			AbiSize<16>
		>;
	using AbiParserBytes32 =
		AbiParser<
			SimpleObjects::ObjCategory::Bytes,
			AbiSize<32>
		>;

	// bytes16
	{
		std::vector<uint8_t> input = {
			0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
			0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		};
		// test HeadToPrimitive
		{
			auto expRes = std::make_tuple(
				std::vector<uint8_t>({
					0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
					0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
				}),
				input.end(),
				1
			);

			auto actRes = AbiParserBytes(16).HeadToPrimitive(
				input.begin(), input.end()
			);
			auto actRes2 = AbiParserBytes16().HeadToPrimitive(
				input.begin(), input.end()
			);

			EXPECT_EQ(expRes, actRes);
			EXPECT_EQ(expRes, actRes2);
		}
		// test ToPrimitive
		{
			auto expRes = std::make_tuple(
				std::vector<uint8_t>({
					0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
					0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
				}),
				input.end()
			);

			auto actRes = AbiParserBytes(16).ToPrimitive(
				input.begin(), input.end(), input.begin()
			);
			auto actRes2 = AbiParserBytes16().ToPrimitive(
				input.begin(), input.end(), input.begin()
			);

			EXPECT_EQ(expRes, actRes);
			EXPECT_EQ(expRes, actRes2);
		}
	}

	// bytes32
	{
		std::vector<uint8_t> input = {
			0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
			0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
			0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
			0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
		};
		auto expRes = std::make_tuple(
			std::vector<uint8_t>({
				0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
				0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
				0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
				0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
			}),
			input.end()
		);

		auto actRes = AbiParserBytes(32).ToPrimitive(
			input.begin(), input.end(), input.begin()
		);
		auto actRes2 = AbiParserBytes32().ToPrimitive(
			input.begin(), input.end(), input.begin()
		);

		EXPECT_EQ(expRes, actRes);
		EXPECT_EQ(expRes, actRes2);
	}

	// Error - not enough bytes (smaller than target type)
	{
		std::vector<uint8_t> input = {
			0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
		};

		auto testProg = [&input]() {
			auto actRes = AbiParserBytes16().ToPrimitive(
				input.begin(), input.end(), input.begin()
			);
		};

		EXPECT_THROW(testProg();, EclipseMonitor::Exception);
	}

	// Error - not enough bytes (smaller than chunk size)
	{
		std::vector<uint8_t> input = {
			0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
			0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
		};

		auto testProg = [&input]() {
			auto actRes = AbiParserBytes16().ToPrimitive(
				input.begin(), input.end(), input.begin()
			);
		};

		EXPECT_THROW(testProg();, EclipseMonitor::Exception);
	}

	// Error - non-zero padding bytes
	{
		std::vector<uint8_t> input = {
			0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
			0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
			0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
			0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
		};

		auto testProg = [&input]() {
			auto actRes = AbiParserBytes16().ToPrimitive(
				input.begin(), input.end(), input.begin()
			);
		};

		EXPECT_THROW(testProg();, EclipseMonitor::Exception);
	}
}

GTEST_TEST(TestEthAbiParser, ParseDynamicBytesPrimitive)
{
	using AbiParserBytes =
		AbiParser<
			SimpleObjects::ObjCategory::Bytes,
			std::true_type
		>;

	// bytes dyn 16
	{
		std::vector<uint8_t> input = {
			// offset
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x20U,
			// tails:
				// len
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x10U,
				// data
				0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
				0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		};
		// test Head + Tail ToPrimitive
		{
			auto expHeadRes = std::make_tuple(
				static_cast<uint64_t>(32ULL),
				input.begin() + 32,
				1
			);

			auto actHeadRes = AbiParserBytes().HeadToPrimitive(
				input.begin(), input.end()
			);

			ASSERT_EQ(expHeadRes, actHeadRes);

			auto expTailRes = std::make_tuple(
				std::vector<uint8_t>({
					0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
					0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
				}),
				input.end(),
				2
			);

			auto actTailRes = AbiParserBytes().TailToPrimitive(
				input.begin() + 32, input.end()
			);

			EXPECT_EQ(expTailRes, actTailRes);
		}
		// test ToPrimitive
		{
			auto expRes = std::make_tuple(
				std::vector<uint8_t>({
					0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
					0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
				}),
				input.begin() + 32
			);

			auto actRes = AbiParserBytes().ToPrimitive(
				input.begin(), input.end(), input.begin()
			);

			EXPECT_EQ(expRes, actRes);
		}
	}

	// Error - no enough bytes (smaller than target size)
	{
		std::vector<uint8_t> input = {
			// offset
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x20U,
			// tails:
				// len
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x10U,
				// data
				0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
		};

		auto testProg = [&input]() {
			AbiParserBytes().ToPrimitive(
				input.begin(), input.end(), input.begin()
			);
		};

		EXPECT_THROW(testProg();, EclipseMonitor::Exception);
	}

	// Error - no enough bytes (smaller than chunk size)
	{
		std::vector<uint8_t> input = {
			// offset
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x20U,
			// tails:
				// len
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x10U,
				// data
				0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
				0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
		};

		auto testProg = [&input]() {
			AbiParserBytes().ToPrimitive(
				input.begin(), input.end(), input.begin()
			);
		};

		EXPECT_THROW(testProg();, EclipseMonitor::Exception);
	}

	// Error - non-zero padding bytes
	{
		std::vector<uint8_t> input = {
			// offset
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x20U,
			// tails:
				// len
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x10U,
				// data
				0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
				0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x01U,
		};

		auto testProg = [&input]() {
			AbiParserBytes().ToPrimitive(
				input.begin(), input.end(), input.begin()
			);
		};

		EXPECT_THROW(testProg();, EclipseMonitor::Exception);
	}
}

GTEST_TEST(TestEthAbiParser, ParseListStLenStITypePrimitive)
{
// uint64[2]
// [ 32, 64 ]
// 0000000000000000000000000000000000000000000000000000000000000020
// 0000000000000000000000000000000000000000000000000000000000000040
	using AbiParserUInt64 =
		AbiParser<
			SimpleObjects::ObjCategory::Integer,
			AbiUInt64
		>;
	using AbiParserList =
		AbiParser<
			SimpleObjects::ObjCategory::List,
			AbiParserUInt64,
			std::false_type
		>;
	using AbiParserList_2 =
		AbiParser<
			SimpleObjects::ObjCategory::List,
			AbiParserUInt64,
			AbiSize<2>
		>;

	{
		std::vector<uint8_t> input = {
			// data 1
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x20U,
			// data 2
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x40U,
		};

		// test Head ToPrimitive
		{
			AbiParserList listParser(AbiParserUInt64(), 2);
			AbiParserList_2 listParser2 = AbiParserList_2(AbiParserUInt64());

			auto expHeadRes = std::make_tuple(
				std::vector<uint64_t>({
					32ULL,
					64ULL,
				}),
				input.end(),
				2
			);

			auto actHeadRes = listParser.HeadToPrimitive(
				input.begin(), input.end()
			);
			auto actHeadRes2 = listParser2.HeadToPrimitive(
				input.begin(), input.end()
			);

			ASSERT_EQ(expHeadRes, actHeadRes);
			ASSERT_EQ(expHeadRes, actHeadRes2);
		}

		// test ToPrimitive
		{
			AbiParserList listParser(AbiParserUInt64(), 2);
			AbiParserList_2 listParser2 = AbiParserList_2(AbiParserUInt64());

			auto expRes = std::make_tuple(
				std::vector<uint64_t>({
					32ULL,
					64ULL,
				}),
				input.end()
			);

			auto actRes = listParser.ToPrimitive(
				input.begin(), input.end(), input.begin()
			);
			auto actRes2 = listParser2.ToPrimitive(
				input.begin(), input.end(), input.begin()
			);

			EXPECT_EQ(expRes, actRes);
			EXPECT_EQ(expRes, actRes2);
		}
	}
}

GTEST_TEST(TestEthAbiParser, ParseListDynLenStITypePrimitive)
{
// uint64[]
// [ 32, 64 ]
// 0000000000000000000000000000000000000000000000000000000000000020
// 0000000000000000000000000000000000000000000000000000000000000002
// 0000000000000000000000000000000000000000000000000000000000000020
// 0000000000000000000000000000000000000000000000000000000000000040
	using AbiParserUInt64 =
		AbiParser<
			SimpleObjects::ObjCategory::Integer,
			AbiUInt64
		>;
	using AbiParserList =
		AbiParser<
			SimpleObjects::ObjCategory::List,
			AbiParserUInt64,
			std::true_type
		>;

	{
		std::vector<uint8_t> input = {
			// offset
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x20U,
				// length
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x02U,
				// data 1
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x20U,
				// data 2
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x40U,
		};

		// test Head + Tail ToPrimitive
		{
			AbiParserList listParser = AbiParserList(AbiParserUInt64());

			auto expHeadRes = std::make_tuple(
				static_cast<uint64_t>(32ULL),
				input.begin() + 32,
				1
			);

			auto actHeadRes = listParser.HeadToPrimitive(
				input.begin(), input.end()
			);

			ASSERT_EQ(expHeadRes, actHeadRes);

			auto expTailRes = std::make_tuple(
				std::vector<uint64_t>({
					32ULL,
					64ULL,
				}),
				input.end(),
				3
			);

			auto actTailRes = listParser.TailToPrimitive(
				input.begin() + 32, input.end()
			);

			EXPECT_EQ(expTailRes, actTailRes);
		}

		// test ToPrimitive
		{
			AbiParserList listParser = AbiParserList(AbiParserUInt64());

			auto expRes = std::make_tuple(
				std::vector<uint64_t>({
					32ULL,
					64ULL,
				}),
				input.begin() + 32
			);

			auto actRes = listParser.ToPrimitive(
				input.begin(), input.end(), input.begin()
			);

			EXPECT_EQ(expRes, actRes);
		}
	}
}

GTEST_TEST(TestEthAbiParser, ParseListStLenDynITypePrimitive)
{
// Bytes[2]
// [ "0x0123456789abcdef0123456789abcdef", "0xfedcba9876543210fedcba9876543210" ]
// 0000000000000000000000000000000000000000000000000000000000000020
// 0000000000000000000000000000000000000000000000000000000000000040
// 0000000000000000000000000000000000000000000000000000000000000080
// 0000000000000000000000000000000000000000000000000000000000000010
// 0123456789abcdef0123456789abcdef00000000000000000000000000000000
// 0000000000000000000000000000000000000000000000000000000000000010
// fedcba9876543210fedcba987654321000000000000000000000000000000000
	using AbiParserBytes =
		AbiParser<
			SimpleObjects::ObjCategory::Bytes,
			std::true_type
		>;
	using AbiParserList =
		AbiParser<
			SimpleObjects::ObjCategory::List,
			AbiParserBytes,
			std::false_type
		>;
	using AbiParserList_2 =
		AbiParser<
			SimpleObjects::ObjCategory::List,
			AbiParserBytes,
			AbiSize<2>
		>;

	{
		std::vector<uint8_t> input = {
			// offset
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x20U,
			// tails:
				// offset
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x40U,
				// offset
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x80U,
					// len
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x10U,
					// data
					0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
					0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					// len
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x10U,
					// data
					0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
					0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		};

		// test Head + Tail ToPrimitive
		{
			AbiParserList listParser(AbiParserBytes(), 2);
			AbiParserList_2 listParser2 = AbiParserList_2(AbiParserBytes());

			auto expHeadRes = std::make_tuple(
				static_cast<uint64_t>(32ULL),
				input.begin() + 32,
				1
			);

			auto actHeadRes = listParser.HeadToPrimitive(
				input.begin(), input.end()
			);
			auto actHeadRes2 = listParser2.HeadToPrimitive(
				input.begin(), input.end()
			);

			ASSERT_EQ(expHeadRes, actHeadRes);
			ASSERT_EQ(expHeadRes, actHeadRes2);

			auto expTailRes = std::make_tuple(
				std::vector<std::vector<uint8_t> >({
					{
						0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
						0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
					},
					{
						0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
						0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
					},
				}),
				input.end(),
				6
			);

			auto actTailRes = listParser.TailToPrimitive(
				input.begin() + 32, input.end()
			);
			auto actTailRes2 = listParser2.TailToPrimitive(
				input.begin() + 32, input.end()
			);

			EXPECT_EQ(expTailRes, actTailRes);
			EXPECT_EQ(expTailRes, actTailRes2);
		}

		// test ToPrimitive
		{
			AbiParserList listParser(AbiParserBytes(), 2);
			AbiParserList_2 listParser2 = AbiParserList_2(AbiParserBytes());

			auto expRes = std::make_tuple(
				std::vector<std::vector<uint8_t> >({
					{
						0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
						0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
					},
					{
						0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
						0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
					},
				}),
				input.begin() + 32
			);

			auto actRes = listParser.ToPrimitive(
				input.begin(), input.end(), input.begin()
			);
			auto actRes2 = listParser2.ToPrimitive(
				input.begin(), input.end(), input.begin()
			);

			EXPECT_EQ(expRes, actRes);
			EXPECT_EQ(expRes, actRes2);
		}
	}
}

GTEST_TEST(TestEthAbiParser, ParseListDynLenDynITypePrimitive)
{
// Bytes[]
// [ "0x0123456789abcdef0123456789abcdef", "0xfedcba9876543210fedcba9876543210" ]
// 0000000000000000000000000000000000000000000000000000000000000020
// 0000000000000000000000000000000000000000000000000000000000000002
// 0000000000000000000000000000000000000000000000000000000000000040
// 0000000000000000000000000000000000000000000000000000000000000080
// 0000000000000000000000000000000000000000000000000000000000000010
// 0123456789abcdef0123456789abcdef00000000000000000000000000000000
// 0000000000000000000000000000000000000000000000000000000000000010
// fedcba9876543210fedcba987654321000000000000000000000000000000000
	using AbiParserBytes =
		AbiParser<
			SimpleObjects::ObjCategory::Bytes,
			std::true_type
		>;
	using AbiParserList =
		AbiParser<
			SimpleObjects::ObjCategory::List,
			AbiParserBytes,
			std::true_type
		>;

	{
		std::vector<uint8_t> input = {
			// offset
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x20U,
			// tails:
				// length
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x02U,
				// offset
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x40U,
				// offset
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x80U,
				// tails:
					// len
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x10U,
					// data
					0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
					0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					// len
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x10U,
					// data
					0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
					0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		};

		// test Head + Tail ToPrimitive
		{
			AbiParserList listParser = AbiParserList(AbiParserBytes());

			auto expHeadRes = std::make_tuple(
				static_cast<uint64_t>(32ULL),
				input.begin() + 32,
				1
			);

			auto actHeadRes = listParser.HeadToPrimitive(
				input.begin(), input.end()
			);

			ASSERT_EQ(expHeadRes, actHeadRes);

			auto expTailRes = std::make_tuple(
				std::vector<std::vector<uint8_t> >({
					{
						0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
						0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
					},
					{
						0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
						0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
					},
				}),
				input.end(),
				7
			);

			auto actTailRes = listParser.TailToPrimitive(
				input.begin() + 32, input.end()
			);

			EXPECT_EQ(expTailRes, actTailRes);
		}

		// test ToPrimitive
		{
			AbiParserList listParser = AbiParserList(AbiParserBytes());

			auto expRes = std::make_tuple(
				std::vector<std::vector<uint8_t> >({
					{
						0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
						0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
					},
					{
						0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
						0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
					},
				}),
				input.begin() + 32
			);

			auto actRes = listParser.ToPrimitive(
				input.begin(), input.end(), input.begin()
			);

			EXPECT_EQ(expRes, actRes);
		}
	}
}

GTEST_TEST(TestEthAbiParser, ParseMixParamsPrimitive)
{
	using AbiParserBool = AbiParser<
		SimpleObjects::ObjCategory::Bool
	>;
	using AbiParserUInt64 = AbiParser<
		SimpleObjects::ObjCategory::Integer,
		AbiUInt64
	>;
	using AbiParserBytes16 = AbiParser<
		SimpleObjects::ObjCategory::Bytes,
		AbiSize<16>
	>;
	using AbiParserBytes = AbiParser<
		SimpleObjects::ObjCategory::Bytes,
		std::true_type
	>;
	using AbiParserListUInt64_2 = AbiParser<
		SimpleObjects::ObjCategory::List,
		AbiParserUInt64,
		AbiSize<2>
	>;
	using AbiParserListBytes = AbiParser<
		SimpleObjects::ObjCategory::List,
		AbiParserBytes,
		std::true_type
	>;

	// function bar(
	// 		bool isFoo,
	// 		uint64 num,
	// 		bytes32 fooBytes,
	// 		bytes dynBytes,
	// 		uint64[2] nums,
	// 		bytes[] arrBytes,
	// ) public

	{
		std::vector<uint8_t> input = {
			// 0000 - bool isFoo
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x01U,
			// 0020 - uint64 num
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
			// 0040 - bytes16 fooBytes
			0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
			0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			// 0060 - offset - bytes dynBytes
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0xE0U,
			// 0080 - uint64[2] nums - [0]
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
			// 00A0 - uint64[2] nums - [1]
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0x00U, 0x00U,
			// 00C0 - offset - bytes[] arrBytes
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
			0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x01U, 0x20U,
			// tails
				// 00E0 - en - bytes dynBytes
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x10U,
				// 0100 - data - bytes dynBytes
				0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
				0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				// 0120 - len - bytes[] arrBytes
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x02U,
				// 0140 - 0000 - offset - bytes[] arrBytes
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x40U,
				// 0160 - 0020 - offset - bytes[] arrBytes
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
				0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x80U,
					// 0180 - 0040 - len - bytes[] arrBytes
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x10U,
					// 01A0 - 0060 - data - bytes[] arrBytes
					0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
					0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					// 01C0 - 0080 - len - bytes[] arrBytes
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x10U,
					// 01E0 - 00A0 - data - bytes[] arrBytes
					0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
					0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
					0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
		};

		// destination variables
		bool                 param1;
		bool                 param1ExpVal = true;
		uint64_t             param2;
		uint64_t             param2ExpVal = 0x123456789ABCDEFULL;
		std::vector<uint8_t> param3;
		std::vector<uint8_t> param3ExpVal = {
			0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
			0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
		};
		std::vector<uint8_t> param4;
		std::vector<uint8_t> param4ExpVal = {
			0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
			0xEFU, 0xCDU, 0xABU, 0x89U, 0x67U, 0x45U, 0x23U, 0x01U,
		};
		std::vector<uint64_t> param5;
		std::vector<uint64_t> param5ExpVal = {
			0x123456789ABCDEFULL,
			0x123456789AB0000ULL,
		};
		std::vector<std::vector<uint8_t> >
		                      param6;
		std::vector<std::vector<uint8_t> >
		                      param6ExpVal = {
			{
				0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
				0x01U, 0x23U, 0x45U, 0x67U, 0x89U, 0xABU, 0xCDU, 0xEFU,
			},
			{
				0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
				0xFEU, 0xDCU, 0xBAU, 0x98U, 0x76U, 0x54U, 0x32U, 0x10U,
			},
		};

		// parse
		auto begin = input.begin();
		std::tie(param1, begin) =
			AbiParserBool().ToPrimitive(
				begin, input.end(), input.begin()
			);
		std::tie(param2, begin) =
			AbiParserUInt64().ToPrimitive(
				begin, input.end(), input.begin()
			);
		std::tie(param3, begin) =
			AbiParserBytes16().ToPrimitive(
				begin, input.end(), input.begin()
			);
		std::tie(param4, begin) =
			AbiParserBytes().ToPrimitive(
				begin, input.end(), input.begin()
			);
		std::tie(param5, begin) =
			AbiParserListUInt64_2(AbiParserUInt64()).ToPrimitive(
				begin, input.end(), input.begin()
			);
		std::tie(param6, begin) =
			AbiParserListBytes(AbiParserBytes()).ToPrimitive(
				begin, input.end(), input.begin()
			);

		// check parsed values
		EXPECT_EQ(param1, param1ExpVal);
		EXPECT_EQ(param2, param2ExpVal);
		EXPECT_EQ(param3, param3ExpVal);
		EXPECT_EQ(param4, param4ExpVal);
		EXPECT_EQ(param5, param5ExpVal);
		EXPECT_EQ(param6, param6ExpVal);

		// check the returned iterator
		EXPECT_EQ(
			begin,
			input.begin() +
				32 + // bool
				32 + // uint64
				32 + // bytes16
				32 + // bytes
				64 + // int64[2]
				32 // bytes[]
		);
	}
}
