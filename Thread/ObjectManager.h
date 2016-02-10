/* This source file is part of the concurrent Fiber based Framework.
*
* Copyright (c) 2015-2016 Joshua Chew
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#pragma once
#include "ForwardDeclarations.h"
#include "Noncopyable.h"
#include "TypeInfo.h"
#include "Singleton.h"
#include "Assert.h"
#include "Object.h"

class ObjectManager
{
public:
    //! Constructor.
    ObjectManager();
    //! Destructor.
    ~ObjectManager();
    //! Create an object (used for custom object manipulation before initialisation).
    //! @tparam	OBJECT_TYPE	Uninitialised object type.
    //! @param	name		Object name.
    //! @param	init		Initialise object.
    //! @return				Pointer to the newly created object. NULL if error creating object.
    template< typename OBJECT_TYPE >
    OBJECT_TYPE* Create(const char* name, bool init = true)
    {
        static_cast<Object*>(static_cast<OBJECT_TYPE*>(nullptr));

        if (ObjectTable.find(name) != ObjectTable.end())
        {
            //std::string msg(name + "already exists");
            ASSERT(false, name + "already exists");
            return nullptr;
        }

        Object * ptr = new OBJECT_TYPE();

        ptr->mName = name;

        ObjectTable.emplace(name, ptr);

        if (init)
            ptr->Initialise();

        return static_cast<OBJECT_TYPE*>(ptr);
    }
    //! Get an existing object by its name.
    //! @tparam	OBJECT_TYPE	Object type.
    //! @param	name		Object name.
    //! @return				Pointer to the existing object (NULL if non-existent).
    template< typename OBJECT_TYPE >
    OBJECT_TYPE* Get(const char * name) const
    {
        //Stdout << name Stdendl;
        if (ObjectTable.find(name) == ObjectTable.end())
            return nullptr;

        return static_cast<OBJECT_TYPE*>(ObjectTable.at(name));
    }
    //! Get an existing object by its name.
    //! @param	name		Object name.
    //! @return				Pointer to the existing object (NULL if non-existent).
    Object* Get(const char * name) const;

    //! Destroy an existing object by its hashed name. Logs an error if object does not exist.
    //! @param	name		Object name.
    void Destroy(const char * name);


    //! Perform the actual destruction on objects to be destroyed.
    void Purge(void);
    //! Force a full object purge (REMOVES ALL OBJECTS FROM OBJECT MANAGER).
    void ForceFullPurge(void);

private:

    std::unordered_map <String, Object *>      ObjectTable;
    std::vector <String>                       mObjectsToDestroy;


    DECLARE_SINGLETON(ObjectManager)
};


#define CREATEOBJ(type, name)\
ObjectManager::Instance().Create<type>(##name);
#define GETBASEOBJ(name)\
ObjectManager::Instance().Get(##name);
#define GETOBJ(type, name)\
ObjectManager::Instance().Get<type>(##name);