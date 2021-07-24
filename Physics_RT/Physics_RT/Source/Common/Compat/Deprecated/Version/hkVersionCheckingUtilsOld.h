/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKSERIALZE_VERSION_CHECKING_UTILS_OLD_H
#define HKSERIALZE_VERSION_CHECKING_UTILS_OLD_H

#include <Common/Compat/Deprecated/Version/hkVersionRegistry.h>
#include <Common/Serialize/Util/hkVersionCheckingUtils.h>

namespace hkVersionCheckingUtils
{
		/// Verify that an update description is complete.
		/// For each class in oldClasses, verify that it is identical to the new version
		/// or that a version function exists to update it. A human readable report is
		/// written to the report stream.
	hkResult HK_CALL verifyUpdateDescription( hkOstream& report,
		const hkClassNameRegistry& oldClassReg,
		const hkClassNameRegistry& newClassReg,
		const hkVersionRegistry::UpdateDescription& updateDescriptionHead,
		hkVersionCheckingUtils::Flags flags, const char** ignoredPrefixes = HK_NULL, int numIgnoredPrefixes = 0);
}

#endif // HKSERIALZE_VERSION_CHECKING_UTILS_OLD_H

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
