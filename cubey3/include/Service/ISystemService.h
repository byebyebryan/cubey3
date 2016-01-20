#pragma once

#include "SystemEvent.h"
#include "SystemEventListener.h"

namespace cubey3 {
	class ISystemService {
	public:
		ISystemService() :
			start_up_lisenter_(std::bind(&ISystemService::StartUp, this, std::placeholders::_1)),
			early_update_lisenter_(std::bind(&ISystemService::EarlyUpdate, this, std::placeholders::_1)),
			update_lisenter_(std::bind(&ISystemService::Update, this, std::placeholders::_1)),
			late_update_lisenter_(std::bind(&ISystemService::LateUpdate, this, std::placeholders::_1)),
			pre_render_lisenter_(std::bind(&ISystemService::PreRender, this, std::placeholders::_1)),
			render_lisenter_(std::bind(&ISystemService::Render, this, std::placeholders::_1)),
			post_render_lisenter_(std::bind(&ISystemService::PostRender, this, std::placeholders::_1)),
			shut_down_lisenter_(std::bind(&ISystemService::ShutDown, this, std::placeholders::_1)) {
		}

		virtual ~ISystemService() {}

		virtual void Init() {}

		virtual void StartUp(const StartUpEvent& event) {}
		virtual void EarlyUpdate(const EarlyUpdateEvent& event) {}
		virtual void Update(const UpdateEvent& event) {}
		virtual void LateUpdate(const LateUpdateEvent& event) {}
		virtual void PreRender(const PreRenderEvent& event) {}
		virtual void Render(const RenderEvent& event) {}
		virtual void PostRender(const PostRenderEvent& event) {}
		virtual void ShutDown(const ShutDownEvent& event) {}

	protected:
		SystemEventLisenter<StartUpEvent> start_up_lisenter_;
		SystemEventLisenter<EarlyUpdateEvent> early_update_lisenter_;
		SystemEventLisenter<UpdateEvent> update_lisenter_;
		SystemEventLisenter<LateUpdateEvent> late_update_lisenter_;
		SystemEventLisenter<PreRenderEvent> pre_render_lisenter_;
		SystemEventLisenter<RenderEvent> render_lisenter_;
		SystemEventLisenter<PostRenderEvent> post_render_lisenter_;
		SystemEventLisenter<ShutDownEvent> shut_down_lisenter_;

	};
}