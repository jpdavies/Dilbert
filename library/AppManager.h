/*! @file */

#ifndef _APPMANAGER_H_
#define _APPMANAGER_H_

#include <Arduino.h>
#include <UniversalInputTypes.h>
#include <IInputDevice.h>
#include <IUniversalInputCallback.h>

#include "Dilbert.h"

/**
 * @brief Maximum number of apps that can be registered with the manager.
 */
#define MAX_NUM_APPS 16

class App;

/**
 * @class AppManager
 * @author Dan Nixon
 * @brief Used to manage several applications on the badge.
 */
class AppManager : public IUniversalInputCallback
{
public:
  AppManager(Dilbert *badge);
  virtual ~AppManager();

  void begin();

  uint8_t addApp(App *app);

  bool activateAppByName(char *name);
  bool activateAppByIdx(uint8_t idx);

  uint8_t appIdx(char *name);
  uint8_t appIdx(App *app) const;

  /**
   * @brief Gets an application given it's index.
   * @param idx Application index
   * @return Pointer to application
   */
  inline App *app(uint8_t idx)
  {
    return m_apps[idx];
  }

  size_t numApps() const;

  /**
   * @brief Gets the active application.
   * @return Pointer to active application
   */
  inline App *activeApp()
  {
    return m_apps[m_activeAppIdx];
  }

  void run();

  void handleUniversalInputEvent(inputtype_t type, IInputDevice *device);

private:
  Dilbert *m_badge;
  App *m_apps[MAX_NUM_APPS];
  char *m_appNames[MAX_NUM_APPS];
  uint8_t m_activeAppIdx;
};

#endif