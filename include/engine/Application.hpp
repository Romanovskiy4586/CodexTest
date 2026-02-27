#pragma once

namespace engine {

class Engine;

class IClientLayer {
public:
  virtual ~IClientLayer() = default;
  virtual void onAttach(Engine& engine) = 0;
  virtual void onUpdate(Engine& engine, float deltaTime, float timeSeconds) = 0;
  virtual void onRender(Engine& engine, float aspectRatio, float timeSeconds) = 0;
};

class Application {
public:
  explicit Application(IClientLayer& clientLayer);
  void run();

private:
  IClientLayer& m_clientLayer;
};

} // namespace engine
