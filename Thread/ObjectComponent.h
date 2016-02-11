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
#include "Object.h"
#include "Noncopyable.h"
#include "TypeInfo.h"

class ObjectComponent : Noncopyable
{
    /***** Public Members *****/
public:
    //typedef Object ObjectPtr;
    Object *		OwningObject;
    /***** Public Methods *****/
public:
    //! Protected constructor.
    //! We only want the ObjectComponentManager instantiating this.
    ObjectComponent();
    // Destructor.
    virtual ~ObjectComponent();
    //! ObjectComponent initialisation method.
    //! Called by the ObjectComponent manager when created.
    virtual void Initialise(void);
    //! ObjectComponent shutdown method.
    //! Called by the ObjectComponent manager when destroyed.
    virtual void Shutdown(void);

    /***** Private Members *****/
private:
    bool			mInitialised;		//!< Checks if object component has already been initialised.

    DECLARE_TYPE(ObjectComponent);

    friend class Object;
    friend class ObjectManager;
};

