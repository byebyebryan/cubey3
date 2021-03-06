#pragma once

#include "ServiceLocator.h"

namespace cubey3 {
	template<typename ServiceInterfaceT>
	class IService {
	public:
		virtual ~IService() {}

		virtual void OnCreate() {}
		virtual void OnDestroy() {}

		static ServiceInterfaceT* GetService() {
			return ServiceLocator<ServiceInterfaceT>::service();
		}

		template<typename ServiceT = ServiceInterfaceT>
		static void CreateService(ServiceT* new_service = nullptr) {
			DestroyService();

			if(!new_service) {
				new_service = new ServiceT();
			}

			ServiceLocator<ServiceInterfaceT>::set_service(new_service);

			new_service->OnCreate();
		}

		static void DestroyService() {
			ServiceInterfaceT* current_service = GetService();

			if (current_service) {
				current_service->OnDestroy();
				delete current_service;
			}

			ServiceLocator<ServiceInterfaceT>::set_service(nullptr);
		}
	};
}