/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_CONSTRAINT_DRAWER_H
#define HKP_CONSTRAINT_DRAWER_H

#include <Common/Base/hkBase.h>
#include <Physics/Constraint/Visualize/Drawer/hkpPrimitiveDrawer.h>


class hkpConstraintDrawer
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HKP_MEMORY_CLASS_VDB, hkpConstraintDrawer );

		hkpConstraintDrawer();

			/// Sets the size of lines drawn.
		void setLineLength(hkReal lineLength);

			/// Sets the radius of arcs drawn.
		void setArcRadius(hkReal arcRadius);

			/// Allows the user to up the number of segments used when displaying curved geometry.
		void setNumArcSegments(int numSegments);

			/// Set the size of the pivots drawn.
		void setPivotSize(hkReal size);

			/// Sets the size of arrows drawn.
		void setArrowSize(hkReal arrrowSize);

			/// Sets the scale of all drawing
		void setScale(hkReal scale);

	protected:

		void drawPivots(int id, int tag);

		void drawBodyFrames(int id, int tag);

		void updateCommonParameters(const hkTransform& attLocalToWorld, const hkTransform& refLocalToWorld);

	private:

		hkReal m_lineLength;
		hkReal m_arcRadius;
		hkReal m_pivotSize;
		hkReal m_arrowSize;
		hkReal m_coneSize;
		hkReal m_planeSize;
		int	   m_numArcSegments;

		hkReal m_scale;

	protected:

		hkReal getLineLengthForDraw()
		{
			return m_scale * m_lineLength;
		}

		hkReal getArrowSizeForDraw()
		{
			return m_scale * m_arrowSize;
		}

		hkReal getConeSizeForDraw()
		{
			return m_scale * m_coneSize;
		}

		hkReal getPlaneSizeForDraw()
		{
			return m_scale * m_planeSize;
		}

		hkReal getPivotSizeForDraw()
		{
			return m_scale * m_pivotSize;
		}

		hkReal getArcRadiusForDraw()
		{
			return m_scale * m_arcRadius;
		}

		int getNumArcSegmentsForDraw()
		{
			return m_numArcSegments;
		}

	protected:

		// world positions
		hkVector4 m_bodyAWPos;
		hkVector4 m_bodyBWPos;

		// world positions of pivots
		hkVector4 m_bodyAWPivot;
		hkVector4 m_bodyBWPivot;

		hkRotation m_RA;
		hkRotation m_RB;

		hkpPrimitiveDrawer m_primitiveDrawer;
};

#endif // HKP_CONSTRAINT_DRAWER_H

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
