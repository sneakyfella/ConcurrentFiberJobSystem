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
#include "ObjectComponent.h"
#include "TypeInfo.h"


class Object : Noncopyable
{
    /***** Public Methods *****/
public:
    //! constructor.
    //! @param	hashName	Object's hash name.
    Object();
    // Destructor.
    virtual ~Object();
    //! Object initialisation method.
    //! Called by the object manager when created.
    virtual void Initialise(void);
    //! Object shutdown method.
    //! Called by the object manager when destroyed.
    virtual void Shutdown(void);

    template< typename T >
    T* AddComponent(void)
    {
        // Compile time check if adding anything that's not a object comp
        static_cast< ObjectComponent* >(static_cast< T* >(nullptr));
        T* ptr = new T();
        if (ComponentTable.find(typeid(std::decay<T>).name()) == ComponentTable.end())
            ComponentTable.emplace(typeid(std::decay<T>).name(), ptr);

        ptr->OwningObject = this;

        return ptr;
    }

    template< typename T >
    void RemoveComponent(void)
    {
        // Compile time check if adding anything that's not a object comp
        static_cast< ObjectComponent* >(static_cast< T* >(nullptr));

        if (ComponentTable.find(typeid(std::decay<T>).name()) != ComponentTable.end())
            ComponentTable.erase(typeid(std::decay<T>).name());
    }
    template< typename T >
    T* GetComponent(void)
    {
        static_cast< ObjectComponent* >(static_cast< T* >(nullptr));

        if (ComponentTable.find(typeid(std::decay<T>).name()) == ComponentTable.end())
            return nullptr;

        return static_cast<T*>(ComponentTable[typeid(std::decay<T>).name()]);
    }

private:
    //typedef std::unordered_map< ObjectComponent* >	ComponentTable;

    String mName;
    std::unordered_map< String, ObjectComponent* > ComponentTable;

    DECLARE_TYPE(Object);

    friend class ObjectManager;
};
