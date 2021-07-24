/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Return the master weight for the control
inline hkReal hkaDefaultAnimationControl::getMasterWeight() const
{
	return m_masterWeight;
}

// Set the master weight for this playing animation
inline void hkaDefaultAnimationControl::setMasterWeight( hkReal weight )
{
	m_masterWeight = weight;
}

// Return the master weight for the control
inline hkReal hkaDefaultAnimationControl::getPlaybackSpeed() const
{
	return m_playbackSpeed;
}

// Set the playback speed.
// If the is set to a negative value the animation will run backwards
inline void hkaDefaultAnimationControl::setPlaybackSpeed( hkReal speed )
{
	m_playbackSpeed = speed;
}

inline hkUint32 hkaDefaultAnimationControl::getOverflowCount() const
{
	return m_overflowCount;
}

inline void hkaDefaultAnimationControl::setOverflowCount( hkUint32 count )
{
	m_overflowCount = count;
}

inline hkUint32 hkaDefaultAnimationControl::getUnderflowCount() const
{
	return m_underflowCount;
}

inline void hkaDefaultAnimationControl::setUnderflowCount( hkUint32 count )
{
	m_underflowCount = count;
}


inline enum hkaDefaultAnimationControl::EaseStatus hkaDefaultAnimationControl::getEaseStatus() const
{
	return m_easeStatus;
}

inline void hkaDefaultAnimationControl::setEaseInCurve(hkReal y0, hkReal y1, hkReal y2, hkReal y3)
{
	m_easeInCurve.set(y0, y1, y2, y3);
}

inline void hkaDefaultAnimationControl::setEaseOutCurve(hkReal y0, hkReal y1, hkReal y2, hkReal y3)
{
	m_easeOutCurve.set(y0, y1, y2, y3);
}


// We assume that ease out and in are symmetric
inline hkReal hkaDefaultAnimationControl::easeIn(hkReal durationR)
{
	const hkSimdReal duration = hkSimdReal::fromFloat(durationR);
	hkSimdReal easeT; easeT.load<1>(&m_easeT);

	// Test if the control is currently easing out
	if ( m_easeStatus == EASING_OUT || m_easeStatus == EASED_OUT )
	{
		// "Mirror" the amount of time left for easing
		easeT = hkSimdReal_1 - easeT;
		easeT.store<1>(&m_easeT);
	}

	hkSimdReal invD; invD.setSelect(duration.greater(hkSimdReal_Eps), duration.reciprocal(), hkSimdReal_Max);
	invD.store<1>(&m_easeInvDuration);
	m_easeStatus = easeT.isEqual(hkSimdReal_1) ? EASED_IN : EASING_IN;

	return (duration * (hkSimdReal_1 - easeT)).getReal();
}

// We assume that ease out and in are symmetric
inline hkReal hkaDefaultAnimationControl::easeOut(hkReal durationR)
{
	const hkSimdReal duration = hkSimdReal::fromFloat(durationR);
	hkSimdReal easeT; easeT.load<1>(&m_easeT);

	// Test if the control is currently easing out
	if ( m_easeStatus == EASING_IN || m_easeStatus == EASED_IN )
	{
		// "Mirror" the amount of time left for easing
		easeT = hkSimdReal_1 - easeT;
		easeT.store<1>(&m_easeT);
	}

	hkSimdReal invD; invD.setSelect(duration.greater(hkSimdReal_Eps), duration.reciprocal(), hkSimdReal_Max);
	invD.store<1>(&m_easeInvDuration);
	m_easeStatus = easeT.isEqual(hkSimdReal_1) ? EASED_OUT : EASING_OUT;

	return (duration * (hkSimdReal_1 - easeT)).getReal();
}

// Select between easeIn/easeOut based on a boolean
inline hkReal hkaDefaultAnimationControl::ease( hkReal duration, hkBool easeInIfTrue )
{
	return easeInIfTrue ? easeIn( duration ) : easeOut( duration );
}

// Add a listener 
inline void hkaDefaultAnimationControl::addDefaultControlListener(hkaDefaultAnimationControlListener* listener)
{
	HK_ASSERT2(0x5efefba3, m_defaultListeners.indexOf( listener ) < 0, "You tried to add  a control listener twice" );
	m_defaultListeners.pushBack( listener );
}

// Remove a listener
inline void hkaDefaultAnimationControl::removeDefaultControlListener(hkaDefaultAnimationControlListener* listener)
{
	int i = m_defaultListeners.indexOf( listener );
	HK_ASSERT2(0x2c7b3925, i >= 0, "You tried to remove a control listener, which was never added" );
	m_defaultListeners.removeAt(i);
}

// Set the amount (in local seconds) to crop the start of the animation.
inline void hkaDefaultAnimationControl::setCropStartAmountLocalTime( hkReal cropStartAmountLocalTime )
{
	m_cropStartAmountLocalTime = cropStartAmountLocalTime;

	// make sure the local time is kept in range
	if ( m_localTime < m_cropStartAmountLocalTime )
	{
		m_localTime = m_cropStartAmountLocalTime;
	}
}

// Set the amount (in local seconds) to crop the end of the animation.
inline void hkaDefaultAnimationControl::setCropEndAmountLocalTime( hkReal cropEndAmountLocalTime )
{
	m_cropEndAmountLocalTime = cropEndAmountLocalTime;

	hkReal endTime = m_binding->m_animation->m_duration - m_cropEndAmountLocalTime;

	// make sure the local time is kept in range
	m_localTime = hkMath::min2( m_localTime, endTime );
}

// Get the amount (in local seconds) to crop the start of the animation.
inline hkReal hkaDefaultAnimationControl::getCropStartAmountLocalTime()
{
	return m_cropStartAmountLocalTime;
}

// Get the amount (in local seconds) to crop the end of the animation.
inline hkReal hkaDefaultAnimationControl::getCropEndAmountLocalTime()
{
	return m_cropEndAmountLocalTime;
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
