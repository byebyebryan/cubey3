#pragma once

namespace cubey3 {
	template<typename ServiceInterfaceT>
	class ServiceLocator {
	public:
		static ServiceInterfaceT* service() {
			return service_;
		}

		static void set_service(ServiceInterfaceT* service) {
			service_ = service;
		}
	private:
		static ServiceInterfaceT* service_;
	};

	template<typename ServiceInterfaceT>
	ServiceInterfaceT* ServiceLocator<ServiceInterfaceT>::service_ = nullptr;
}