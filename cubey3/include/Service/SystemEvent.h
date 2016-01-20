#pragma once

namespace cubey3 {
	struct StartUpEvent {
	};

	struct EarlyUpdateEvent {
		double delta_time;
	};

	struct UpdateEvent {
		double delta_time;
	};

	struct LateUpdateEvent {
		double delta_time;
	};

	struct PreRenderEvent {
	};

	struct RenderEvent {
	};

	struct PostRenderEvent {
	};

	struct ShutDownEvent {
	};
}