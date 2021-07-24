/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
TOPOLOGY_HDR
HK_FORCE_INLINE unsigned	TOPOLOGY_TYP::ip1mod3(unsigned i)
{ 
	HK_ASSERT(0x23be31ed, i<3);
#ifdef HK_ARCH_PPC
	// Variable shifts are slow on PowerPC consoles. 
	// The ternary op should be pretty easy to optimize, however
	const unsigned mod3 = (i==2) ? 0 : i+1;
	return mod3;
#else
	return((0x09>>(i<<1))&3); 
#endif
}

//
TOPOLOGY_HDR
HK_FORCE_INLINE unsigned	TOPOLOGY_TYP::ip2mod3(unsigned i)
{
	HK_ASSERT(0x23be31ed, i<3);
#ifdef HK_ARCH_PPC
	unsigned mod3 = (i==0) ? 2 : i-1;
	return mod3;
#else
	return((0x12>>(i<<1))&3);
#endif
}

//
TOPOLOGY_HDR
HKGP_FORCE_INLINE void		TOPOLOGY_TYP::bind(const Edge& edge) const
{	
#if defined(HK_DEBUG)
	if(!canBind(edge))
	{
		bool found=false;
		for(int i=2,j=0;j<3;i=j++)
		{
			if(edge.triangle()->vertex(i)==end() && edge.triangle()->vertex(j)==start())
			{
				HK_REPORT("Edge index should be "<<i<<" instead of "<<edge.index());
				found=true;break;
			}
		}
		if(!found) HK_REPORT("Incorrect triangle bind");
	}
#endif
	HK_ASSERT2(0x9801541,canBind(edge),"Incorrect edge bind");
	m_triangle->link(m_index)=edge.uid();
	if(edge.isValid()) edge.m_triangle->link(edge.m_index)=uid();	
}
//
TOPOLOGY_HDR
HKGP_FORCE_INLINE void		TOPOLOGY_TYP::bindSides() const
{
	EDGE	n=next().link(),p=prev().link();
	if(p.isValid()) { EDGE t=n;n=p;p=t; }
	if(n.isValid())
	{
		n.bind(p);
		next().bind(null());
		prev().bind(null());
	}
}
//
TOPOLOGY_HDR
HKGP_FORCE_INLINE void		TOPOLOGY_TYP::unbind() const
{
	if(!isNaked())
	{
		EDGE l=link();
		l.m_triangle->link(l.m_index)=0;
	}
	m_triangle->link(m_index)=0;
}
//
TOPOLOGY_HDR
HKGP_FORCE_INLINE EDGE		TOPOLOGY_TYP::flip() const
{
	const Edge	lk=link();
	const Edge	ep=prev();
	const Edge	lp=lk.prev();
	start()=lp.start();
	lk.start()=ep.start();
	lk.bind(ep.link());
	bind(lp.link());
	ep.bind(lp);
	return(prev());
}

//
TOPOLOGY_HDR
template <typename FNC>
HKGP_FORCE_INLINE bool		TOPOLOGY_TYP::applyFan(FNC& fnc) const
{
	EDGE	base(self());
	EDGE	curr(base);
	do
	{
		if(fnc(curr)) curr=curr.turnCw(); else return false;
	} while(curr.isValid() && (curr!=base));
	if(!curr.isValid())
	{
		curr=base.turnCcw();
		while(curr.isValid())
		{
			if(fnc(curr)) curr=curr.turnCcw(); else return false;
		}
	}
	return true;
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
