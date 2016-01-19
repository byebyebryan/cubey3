#pragma once

#include "ServiceLocator.h"

namespace cubey3 {
	template<typename ServiceInterfaceT>
	class IService {
	public:
		virtual ~IService() {}

		virtual void Init() {}
		virtual void StartUp() {}
		virtual void Pause() {}
		virtual void Resume() {}
		virtual void ShutDown() {}
		virtual void Destroy() {}

		static ServiceInterfaceT* GetInstance() {
			return ServiceLocator<ServiceInterfaceT>::service();
		}

		template<typename ServiceT = ServiceInterfaceT>
		static void InitService(ServiceT* _new_service = nullptr) {
			DestroyService();

			if(!_new_service) {
				_new_service = new ServiceT();
			}

			ServiceLocator<ServiceInterfaceT>::set_service(_new_service);

			_new_service->Init();
		}

		static void StartUpService() {
			if (GetInstance()) {
				GetInstance()->StartUp();
			}
		}

		static void PauseService() {
			if (GetInstance()) {
				GetInstance()->Pause();
			}
		}
		static void ResumeService() {
			if (GetInstance()) {
				GetInstance()->Resume();
			}
		}

		static void ShutDownService() {
			if (GetInstance()) {
				GetInstance()->ShutDown();
			}
		}

		static void DestroyService() {
			ServiceInterfaceT* current_service = GetInstance();

			if (current_service) {
				current_service->Destroy();
				delete current_service;
			}

			ServiceLocator<ServiceInterfaceT>::set_service(nullptr);
		}
	};
}