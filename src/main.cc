#include <zukou.h>

#include <iostream>

#include "floor-edge.h"
#include "floor.h"
#include "jpeg-texture.h"
#include "landscape.h"
#include "sphere.h"

namespace {
constexpr char greenBg1TexturePath[] = ZENNIST_ASSET_DIR "/green_bg_1.jpg";
constexpr char greenBg2TexturePath[] = ZENNIST_ASSET_DIR "/green_bg_2.jpg";
constexpr char greenBg3TexturePath[] = ZENNIST_ASSET_DIR "/green_bg_3.jpg";
}  // namespace

namespace zennist {

glm::vec4
RgbColor(float r, float g, float b)
{
  return glm::vec4(r / 255, g / 255, b / 255, 1);
}

class Application final : public zukou::IExpansiveDelegate
{
 public:
  DISABLE_MOVE_AND_COPY(Application);
  Application()
      : space_(&system_, this),
        landscape1_(&system_, &space_),
        landscape2_(&system_, &space_),
        landscape3_(&system_, &space_),
        floor_(&system_, &space_, 3.f),
        floorUnder_(&system_, &space_, 4.5f),
        floorEdge_(&system_, &space_),
        floorEdgeUnder_(&system_, &space_),
        bg_(&system_, &space_, 8, false){};

  bool Init()
  {
    if (!system_.Init()) return false;
    if (!space_.Init()) return false;
    if (!landscape1_.Render(.3f,
            glm::translate(glm::mat4(1), glm::vec3(0, -.4f, 0)),
            greenBg1TexturePath, 100.0f))
      return false;
    if (!landscape2_.Render(1.f,
            glm::translate(
                glm::rotate(glm::mat4(1), (float)M_PI / 4, glm::vec3(0, 1, 0)),
                glm::vec3(0, -.7f, 0)),
            greenBg2TexturePath, 200.0f))
      return false;
    if (!landscape3_.Render(2.f,
            glm::translate(
                glm::rotate(glm::mat4(1), (float)M_PI / 2, glm::vec3(0, 1, 0)),
                glm::vec3(0, -.9f, 0)),
            greenBg3TexturePath, 300.0f))
      return false;

    if (!bg_.Render(990, glm::mat4(1))) return false;
    if (!floor_.Render(1.f, glm::translate(glm::mat4(1), glm::vec3(0, 0, 0))))
      return false;
    if (!floorUnder_.Render(
            1.f, glm::translate(glm::mat4(1), glm::vec3(0, -.2f, 0))))
      return false;
    if (!floorEdge_.Render(
            3.f, glm::translate(glm::mat4(1), glm::vec3(0, .01f, 0))))
      return false;
    if (!floorEdgeUnder_.Render(
            4.5f, glm::translate(glm::mat4(1), glm::vec3(0, -.19f, 0))))
      return false;

    space_.Commit();

    return true;
  }

  int Run() { return system_.Run(); }

  void Shutdown() override { system_.Terminate(EXIT_SUCCESS); }

 private:
  zukou::System system_;
  zukou::Expansive space_;

  Landscape landscape1_;
  Landscape landscape2_;
  Landscape landscape3_;
  Floor floor_;
  Floor floorUnder_;
  FloorEdge floorEdge_;
  FloorEdge floorEdgeUnder_;
  Sphere bg_;
};

}  // namespace zennist

int
main()
{
  zennist::Application app;

  if (!app.Init()) return EXIT_FAILURE;

  return app.Run();
}
