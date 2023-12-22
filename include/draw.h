/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-22 22:44:50
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2023-12-22 22:52:35
 */


#ifndef DRAW_H
#define DRAW_H

#define GLFW_INCLUDE_NONE
#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "box2d/box2d.h"


struct b2AABB;
struct GLRenderPoints;
struct GLRenderLines;
struct GLRenderTriangles;
struct GLFWwindow;


struct Camera
{
	Camera();

	void ResetView();
	b2Vec2 ConvertScreenToWorld(const b2Vec2 &screenPoint);
	b2Vec2 ConvertWorldToScreen(const b2Vec2 &worldPoint);
	void BuildProjectionMatrix(float *m, float zBias);

	b2Vec2 m_center;
	float m_zoom;
	int32 m_width;
	int32 m_height;
};

// This class implements debug drawing callbacks that are invoked
// inside b2World::Step.
class DebugDraw : public b2Draw
{
public:
	DebugDraw();
	~DebugDraw();

	void Create();
	void Destroy();

	void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;

	void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;

	void DrawCircle(const b2Vec2 &center, float radius, const b2Color &color) override;

	void DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color) override;

	void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) override;

	void DrawTransform(const b2Transform &xf) override;

	void DrawPoint(const b2Vec2 &p, float size, const b2Color &color) override;

	void DrawString(int x, int y, const char *string, ...);

	void DrawString(const b2Vec2 &p, const char *string, ...);

	void DrawAABB(b2AABB *aabb, const b2Color &color);

	void Flush();

	bool m_showUI;
	GLRenderPoints *m_points;
	GLRenderLines *m_lines;
	GLRenderTriangles *m_triangles;
};

extern DebugDraw g_debugDraw;
extern Camera g_camera;

#endif
