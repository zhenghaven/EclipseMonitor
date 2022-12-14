// Copyright (c) 2022 Haofan Zheng
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "Internal/SimpleObj.hpp"

/**
 * @brief Eclipse Monitor Secure Version Number (SVN) - Upper 1 byte
 *
 */
#define ECLIPSEMONITOR_SVN_UPPER 0x01U
/**
 * @brief Eclipse Monitor Secure Version Number (SVN) - Lower 2 bytes
 *
 */
#define ECLIPSEMONITOR_SVN_LOWER 0x0000U

namespace EclipseMonitor
{

namespace Internal
{

using MonitorIdTupleCore = std::tuple<
	std::pair<
		Obj::StrKey<SIMOBJ_KSTR("sessionID")>,
		Obj::Bytes>
>;

using MonitorConfigTupleCore = std::tuple<
	std::pair<
		Obj::StrKey<SIMOBJ_KSTR("checkpointSize")>,
		Obj::UInt64
	>,
	std::pair<
		Obj::StrKey<SIMOBJ_KSTR("minDiffPercent")>,
		Obj::UInt8
	>,
	std::pair<
		Obj::StrKey<SIMOBJ_KSTR("maxWaitTime")>,
		Obj::UInt64
	>,
	std::pair<
		Obj::StrKey<SIMOBJ_KSTR("syncMaxWaitTime")>,
		Obj::UInt64
	>
>;

using MonitorSecStateTupleCore = std::tuple<
	std::pair<
		Obj::StrKey<SIMOBJ_KSTR("chainName")>,
		Obj::String
	>,
	std::pair<
		Obj::StrKey<SIMOBJ_KSTR("genesisHash")>,
		Obj::Bytes
	>,
	std::pair<
		Obj::StrKey<SIMOBJ_KSTR("checkpointIter")>,
		Obj::UInt64
	>,
	std::pair<
		Obj::StrKey<SIMOBJ_KSTR("checkpointHash")>,
		Obj::Bytes
	>
>;

} // namespace Internal


/**
 * @brief Data used to identify the eclipse monitor instance, and it's
 *        not critical to security considerations
 *
 */
class MonitorId :
	public Internal::Obj::StaticDict<Internal::MonitorIdTupleCore>
{
public: // static members:

	using Self = MonitorId;
	using Base = Internal::Obj::StaticDict<Internal::MonitorIdTupleCore>;

	template<typename _StrSeq>
	using _StrKey = Internal::Obj::StrKey<_StrSeq>;
	template<typename _StrSeq>
	using _RetRefType = typename Base::template GetRef<_StrKey<_StrSeq> >;
	template<typename _StrSeq>
	using _RetKRefType = typename Base::template GetConstRef<_StrKey<_StrSeq> >;

public:

	using Base::Base;

	/**
	 * @brief The 128-bit session ID (randomly generated) used to identify
	 *        a specific monitor process runtime
	 *
	 */
	_RetRefType<SIMOBJ_KSTR("sessionID")> get_sessionID()
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("sessionID")> >();
	}

	_RetKRefType<SIMOBJ_KSTR("sessionID")> get_sessionID() const
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("sessionID")> >();
	}

}; // class MonitorId


/**
 * @brief Configurations of eclipse monitor, and it's *critical* to
 *        security considerations
 *
 */
class MonitorConfig :
	public Internal::Obj::StaticDict<Internal::MonitorConfigTupleCore>
{
public: // static members:

	using Self = MonitorConfig;
	using Base = Internal::Obj::StaticDict<Internal::MonitorConfigTupleCore>;

	template<typename _StrSeq>
	using _StrKey = Internal::Obj::StrKey<_StrSeq>;
	template<typename _StrSeq>
	using _RetRefType = typename Base::template GetRef<_StrKey<_StrSeq> >;
	template<typename _StrSeq>
	using _RetKRefType = typename Base::template GetConstRef<_StrKey<_StrSeq> >;

public:

	using Base::Base;

	/**
	 * @brief The number of blocks in each checkpoint window
	 *
	 */
	_RetRefType<SIMOBJ_KSTR("checkpointSize")> get_checkpointSize()
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("checkpointSize")> >();
	}

	_RetKRefType<SIMOBJ_KSTR("checkpointSize")> get_checkpointSize() const
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("checkpointSize")> >();
	}

	/**
	 * @brief The "percentage" value used to calculate the minimum difficulty
	 *        value. In order to calculate the minimum difficulty value in a
	 *        integer value system, it's using the formula
	 *        "diff_min = (diff_median >> 7) * m_minDiffPercent", which is
	 *        approximately "diff_min = diff_median * (m_minDiffPercent / 128)"
	 *
	 */
	_RetRefType<SIMOBJ_KSTR("minDiffPercent")> get_minDiffPercent()
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("minDiffPercent")> >();
	}

	_RetKRefType<SIMOBJ_KSTR("minDiffPercent")> get_minDiffPercent() const
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("minDiffPercent")> >();
	}

	/**
	 * @brief The maximum time (in seconds) to wait for a new block. After this
	 *        time has passed since the creation of a block, that block will
	 *        stop to accept any new block to be its direct child, and it
	 *        will be marked as inactive.
	 *
	 */
	_RetRefType<SIMOBJ_KSTR("maxWaitTime")> get_maxWaitTime()
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("maxWaitTime")> >();
	}

	_RetKRefType<SIMOBJ_KSTR("maxWaitTime")> get_maxWaitTime() const
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("maxWaitTime")> >();
	}

	/**
	 * @brief The maximum time (in seconds) to wait for the sync message to be
	 *        published on the blockchain. If the sync message is detected after
	 *        this time, the sync process is unsuccessful, and a re-sync will be
	 *        needed.
	 *
	 */
	_RetRefType<SIMOBJ_KSTR("syncMaxWaitTime")> get_syncMaxWaitTime()
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("syncMaxWaitTime")> >();
	}

	_RetKRefType<SIMOBJ_KSTR("syncMaxWaitTime")> get_syncMaxWaitTime() const
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("syncMaxWaitTime")> >();
	}

}; // class MonitorConfig


class MonitorSecState :
	public Internal::Obj::StaticDict<Internal::MonitorSecStateTupleCore>
{
public: // static members:

	using Self = MonitorSecState;
	using Base = Internal::Obj::StaticDict<Internal::MonitorSecStateTupleCore>;

	template<typename _StrSeq>
	using _StrKey = Internal::Obj::StrKey<_StrSeq>;
	template<typename _StrSeq>
	using _RetRefType = typename Base::template GetRef<_StrKey<_StrSeq> >;
	template<typename _StrSeq>
	using _RetKRefType = typename Base::template GetConstRef<_StrKey<_StrSeq> >;

public:

	using Base::Base;

	/**
	 * @brief The name of the blockchain to be monitored (e.g., "bitcoin",
	 *        "ethereum", and so on)
	 *        NOTE: only ethereum is supported for now
	 *
	 */
	_RetRefType<SIMOBJ_KSTR("chainName")> get_chainName()
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("chainName")> >();
	}

	_RetKRefType<SIMOBJ_KSTR("chainName")> get_chainName() const
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("chainName")> >();
	}

	/**
	 * @brief The hash of the genesis block. This will be set by the monitor
	 *        during the bootstrapI phase
	 *
	 */
	_RetRefType<SIMOBJ_KSTR("genesisHash")> get_genesisHash()
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("genesisHash")> >();
	}

	_RetKRefType<SIMOBJ_KSTR("genesisHash")> get_genesisHash() const
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("genesisHash")> >();
	}

	/**
	 * @brief The current iteration number/count of checkpoint windows.
	 *        The number of the first checkpoint window containing the
	 *        genesis block is 0
	 *
	 */
	_RetRefType<SIMOBJ_KSTR("checkpointIter")> get_checkpointIter()
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("checkpointIter")> >();
	}

	_RetKRefType<SIMOBJ_KSTR("checkpointIter")> get_checkpointIter() const
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("checkpointIter")> >();
	}

	/**
	 * @brief The hash of the last block in the current checkpoint window
	 *
	 */
	_RetRefType<SIMOBJ_KSTR("checkpointHash")> get_checkpointHash()
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("checkpointHash")> >();
	}

	_RetKRefType<SIMOBJ_KSTR("checkpointHash")> get_checkpointHash() const
	{
		return Base::template get<_StrKey<SIMOBJ_KSTR("checkpointHash")> >();
	}
}; // class MonitorSecState


inline MonitorConfig BuildDefaultMonitorConfig()
{
	MonitorConfig conf;
	conf.get_checkpointSize()  = 430;
	conf.get_minDiffPercent()  = 103; // which is around 80%
	conf.get_maxWaitTime()     = 400;
	conf.get_syncMaxWaitTime() = 13;

	return conf;
}

} // namespace EclipseMonitor
