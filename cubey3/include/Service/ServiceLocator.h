#pragma once

namespace cubey3 {
	template<typename ServiceInterfaceT>
	class ServiceLocator {
	public:
		static ServiceInterfaceT* service() {
			return service_;
		}

		static void set_service(ServiceInterfaceT* _service) {
			service_ = _service;
		}
	private:
		static ServiceInterfaceT* service_;
	};

	template<typename ServiceInterfaceT>
	ServiceInterfaceT* ServiceLocator<ServiceInterfaceT>::service_ = nullptr;
}