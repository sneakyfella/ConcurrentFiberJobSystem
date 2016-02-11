#pragma once
#include "ForwardDeclarations.h"
#include "Noncopyable.h"
#include "Singleton.h"

    class ServiceRegistry : Noncopyable
    {
        /***** Types *****/
    public:
        typedef std::unordered_map<std::string, void*>	ServiceMap;		//!< Service table type.

                                                                        /***** Public Methods *****/
    public:
        ServiceRegistry(void);
        ~ServiceRegistry(void);
        //! Add service to container.
        //! @see J_SERVICE_TYPE
        //! @param	type	Service class type.
        //! @param	service	Service to object add.
        template< typename SERVICE_TYPE >
        void Add(SERVICE_TYPE* service)
        {
            if (mServices.find(typeid(std::decay<SERVICE_TYPE>).name()) == mServices.end())
                mServices.emplace(typeid(std::decay<SERVICE_TYPE>).name(), service);
        }
        //! Remove service from container.
        //! @param	type	Service class type.
        template< typename SERVICE_TYPE >
        void Remove(void)
        {
            if (mServices.find(typeid(std::decay<SERVICE_TYPE>).name()) != mServices.end())
                mServices.erase(typeid(std::decay<SERVICE_TYPE>).name());
        }
        //! Get service from container.
        //! @tparam	T		Type to return.
        //! @param	type	Type to search for.
        //! @return			Pointer to object of type T or NULL if service doesn't exist.
        template< typename SERVICE_TYPE >
        SERVICE_TYPE* Get(void) const
        {
            if (mServices.find(typeid(std::decay<SERVICE_TYPE>).name()) != mServices.end())
                return static_cast<SERVICE_TYPE*>(mServices[typeid(std::decay<SERVICE_TYPE>).name()]);

            return nullptr;
        }
        /***** Private Members *****/
    private:
        ServiceMap				mServices;	//!< List of services.

        DECLARE_SINGLETON(ServiceRegistry)
    };


#define GET_SERVICE(service)\
ServiceRegistry::Instance().Get<service>()
#define ADD_SERVICE(service, servicePtr)\
ServiceRegistry::Instance().Add<service>(servicePtr);
#define REMOVE_SERVICE(service)\
ServiceRegistry::Instance().Remove<service>();