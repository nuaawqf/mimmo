/*---------------------------------------------------------------------------*\
 *
 *  MiMMO
 *
 *  Copyright (C) 2015-2016 OPTIMAD engineering Srl
 *
 *  -------------------------------------------------------------------------
 *  License
 *  This file is part of MiMMO.
 *
 *  MiMMO is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License v3 (LGPL)
 *  as published by the Free Software Foundation.
 *
 *  MiMMO is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 *  License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with MiMMO. If not, see <http://www.gnu.org/licenses/>.
 *
\*---------------------------------------------------------------------------*/
#ifndef __CHAIN_HPP__
#define __CHAIN_HPP__

#include "BaseManipulation.hpp"
#include "DofOut.hpp"

namespace mimmo{

/*!
 *	\date			22/feb/2016
 *	\authors		Rocco Arpa
 *	\authors		Edoardo Lombardi
 *
 *	\brief Chain is the class used to manage the execution chain of MiMMO objects.
 *
 *	Each object added to the chain is inserted with the correct position in the chain.
 *	An ID is assigned to a new chain and to every object in the chain, in order to give to the user a persistent
 *	information to recover or the position or the ID of the object in the chain.
 *	The execution is performed following the correct order of the object chain in order to avoid
 *	conflicts in parent/child dependencies.
 *	Loops in the chain are not allowed.
 *
 */
class Chain{
protected:
	//members
	uint8_t							m_id;				/**<ID of the chain.*/
	std::vector<BaseManipulation*>	m_objects;			/**<Pointers to manipulation objects placed in the current execution chain. */
	std::vector<int>				m_idObjects;		/**<ID (order of insertion) of the mimmo objects in the chain. */
	uint32_t						m_objcounter;		/**<Counter of objects inserted the chain.*/

	//static members
	static	uint8_t					sm_chaincounter;	/**<Current global number of chain in the instance. */

	//dof/out members
	std::vector<DofOut*>			m_dof;
	std::vector<DofOut*>			m_out;

public:
	Chain();
	~Chain();

	Chain(const Chain & other);
	Chain & operator=(const Chain & other);

	//get/set methods
	uint32_t	getNObjects();
	uint8_t		getID();
	uint8_t		getNChains();
	int			getID(int i);
	std::string	getName(int i);

	int			addObject(BaseManipulation* obj, int id_ = -1);

	bool		deleteObject(int idobj);
	void		clear();

	//relationship methods
	void 		exec();
	void 		exec(int idobj);

private:
	//check methods
	void		checkLoops();


public:
	//dof/out methods
	template<typename T, typename C, typename O>
	int addDofInput(O* obj, T (C::*fget) ());

	template<typename T, typename C, typename O>
	int addDofInput(O* obj, T* (C::*fget) ());

	template<typename T, typename C, typename O>
	int addDofInput(O* obj, T (C::*fget) (), int nglob, int nact, std::vector<bool> map = std::vector<bool>(0));

	template<typename T, typename C, typename O>
	int addDofInput(O* obj, T* (C::*fget) (), int nglob, int nact, std::vector<bool> map = std::vector<bool>(0));

	template<typename T, typename C, typename O>
	int addDofInput(O* obj, T (C::*fget) (), std::vector<bool> map);

	template<typename T, typename C, typename O>
	int addDofInput(O* obj, T* (C::*fget) (), std::vector<bool> map);

	void setNdofs(int i, int nglob, int nuse, std::vector<bool> map = std::vector<bool>(0));

	void activateDof(int i, int j);
	void activateDofs(int i);
	void disableDof(int i, int j);
	void disableDofs(int i);

	template<typename T, typename C, typename O>
	void activateDof(O* obj, T* (C::*fget) (), int j);

	template<typename T, typename C, typename O>
	void activateDofs(O* obj, T* (C::*fget) ());

	template<typename T, typename C, typename O>
	void activateDof(O* obj, T (C::*fget) (), int j);

	template<typename T, typename C, typename O>
	void activateDofs(O* obj, T (C::*fget) ());

	template<typename T, typename C, typename O>
	void disableDof(O* obj, T* (C::*fget) (), int j);

	template<typename T, typename C, typename O>
	void disableDofs(O* obj, T* (C::*fget) ());

	template<typename T, typename C, typename O>
	void disableDof(O* obj, T (C::*fget) (), int j);

	template<typename T, typename C, typename O>
	void disableDofs(O* obj, T (C::*fget) ());



	template<typename T, typename C, typename O>
	int			findDofInput(O* obj, T* (C::*fget) ());

	template<typename T, typename C, typename O>
	int			findDofInput(O* obj, T (C::*fget) ());

	//global getdof
	int 		getNdofs();
	dvector1D 	getDofs();
	double 		getDof(int i);

	//local getdof
	int 		getNdofs(int i);
	dvector1D	getDofs(int i);
	double		getDof(int i, int j);

	template<typename T, typename C, typename O>
	int			getNdofs(O* obj, T* (C::*fget) ());

	template<typename T, typename C, typename O>
	int			getNdofs(O* obj, T (C::*fget) ());

	template<typename T, typename C, typename O>
	dvector1D	getDofs(O* obj, T* (C::*fget) ());

	template<typename T, typename C, typename O>
	dvector1D	getDofs(O* obj, T (C::*fget) ());

	template<typename T, typename C, typename O>
	double	getDof(O* obj, T* (C::*fget) (), int j);

	template<typename T, typename C, typename O>
	double	getDof(O* obj, T (C::*fget) (), int j);



	bool		isActive(int i, int j);

};

}

#include "Chain.tpp"

#endif /* __CHAIN_HPP__ */
