#pragma once
#include "Component.h"

class AutoDestroyComponent : public Component {
 public:
  float seconds;  // İ’è•b”
  float remain;   // c‚èŠÔ

  /**
   * @brief w’è‚µ‚½•b”‚ÌŒãC©“®‚ÅDestroy‚ğÀs‚·‚é
   * @param _seconds •b”
   */
  AutoDestroyComponent(float _seconds) : seconds(_seconds), remain(_seconds) {}

  void Update() override;
};
