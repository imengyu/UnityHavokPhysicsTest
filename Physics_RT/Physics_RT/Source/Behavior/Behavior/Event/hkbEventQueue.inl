/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE hkbEventQueue::hkbEventQueue()
{
}

HK_FORCE_INLINE hkbEventQueue::hkbEventQueue( int capacity )
:	m_queue( capacity )
{
}

HK_FORCE_INLINE bool hkbEventQueue::isEmpty() const
{
	return m_queue.isEmpty();
}

HK_FORCE_INLINE int hkbEventQueue::getSize() const
{
	return m_queue.getSize();
}

HK_FORCE_INLINE void hkbEventQueue::enqueueWithInternalId( hkbEvent event, const hkbSymbolIdMap* eventIdMap )
{
	HK_ASSERT2( 0xc57aab55, event.isValid(), "null events should not go on the queue" );
	

	hkCheckDeterminismUtil::checkMt(0xb0000060, HKB_DETERMINISTIC_EVENT_INTERNAL_ID_BASE + event.m_id);

	// in certain cases when doing precomputation there won't be a map available
	if ( eventIdMap != HK_NULL )
	{
		hkbEvent::Id externalEventId = eventIdMap->getExternal( event.getId() );

		HK_ASSERT2( 0xc471abf5, externalEventId != hkbEvent::EVENT_ID_NULL, "null events should not go on the queue" );

		event.setId( externalEventId );
	}

	hkCheckDeterminismUtil::checkMt(0xb0000061, HKB_DETERMINISTIC_EVENT_EXTERNAL_ID_BASE + event.m_id);

	m_queue.enqueue( event );
}

HK_FORCE_INLINE void hkbEventQueue::enqueueWithInternalId( const hkbEventProperty& ep, hkbNode* sender, const hkbSymbolIdMap* eventIdMap )
{
	hkbEvent e( ep.getId(), ep.getPayload(), sender );
	enqueueWithInternalId( e, eventIdMap );
}

HK_FORCE_INLINE void hkbEventQueue::enqueueWithExternalId( hkbEvent event )
{
	HK_ASSERT2( 0xc57aab55, event.isValid(), "null events should not go on the queue" );

	hkCheckDeterminismUtil::checkMt(0xb0000062, HKB_DETERMINISTIC_EVENT_EXTERNAL_ID_BASE + event.m_id);

	m_queue.enqueue( event );
}

HK_FORCE_INLINE const hkbEvent hkbEventQueue::dequeue()
{
	hkbEvent e;
	m_queue.dequeue( e );
	
	hkCheckDeterminismUtil::checkMt(0xb0000063, HKB_DETERMINISTIC_EVENT_EXTERNAL_ID_BASE + e.m_id);
	hkCheckDeterminismUtil::checkMt(0xb0000067, HKB_DETERMINISTIC_EVENT_COUNT_BASE + m_queue.getSize());

	return e;
}

HK_FORCE_INLINE void hkbEventQueue::clear()
{
	m_queue.clear();

	hkCheckDeterminismUtil::checkMt(0xb0000068, HKB_DETERMINISTIC_EVENT_COUNT_BASE);
}

/*
 * Havok SDK - Base file, BUILD(#20131218)
 * 
 * Confidential Information of Havok.  (C) Copyright 1999-2013
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 * 
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available from salesteam@havok.com.
 * 
 */
