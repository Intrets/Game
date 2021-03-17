#include "UIBackgroundRenderer.h"

#include "infos/RenderInfo.h"
#include "infos/CameraInfo.h"
#include "GLEnabler.h"

namespace render
{
	void UIBackgroundRenderer::render(UIRenderInfo const& renderInfo, GLuint target, CameraInfo const& cameraInfo) {
		if (renderInfo.data.empty()) {
			return;
		}
		this->VAO.bind();
		this->program.use();

		GLEnabler glEnabler;
		glEnabler.enable(GL_DEPTH_TEST).enable(GL_BLEND);
		glDepthFunc(GL_LESS);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindFramebuffer(GL_FRAMEBUFFER, target);
		glViewport(0, 0, cameraInfo.x, cameraInfo.y);

		this->infos.set(renderInfo.data);

		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, static_cast<int32_t>(renderInfo.data.size()));
	}

	UIBackgroundRenderer::UIBackgroundRenderer() {
		static const GLfloat g_quad_vertex_buffer_data[] = {
			0.0f,  0.0f,  0.0f,
			1.0f,  0.0f,  0.0f,
			0.0f,  1.0f,  0.0f,
			0.0f,  1.0f,  0.0f,
			1.0f,  0.0f,  0.0f,
			1.0f,  1.0f,  0.0f,
		};

		this->quad.setRaw(sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data);
	}

	UIBackgroundRenderer::~UIBackgroundRenderer() {
	}
}