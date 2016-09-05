/*
 *
 * Awaken - Keep your PC awake
 * Copyright 2016 Daniel Sage
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

// Include the SDK-defined version constants
#include <sdkddkver.h>

// Clear the Windows API version
#undef NTDDI_VERSION
#undef _WIN32_WINNT

// Enable all Windows Vista SP2 and later APIs
#define NTDDI_VERSION NTDDI_VISTASP2
#define _WIN32_WINNT  _WIN32_WINNT_VISTA
#define WINVER        _WIN32_WINNT

// Include the Windows API headers
#include <Windows.h>

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
  INPUT input = { 0 };
  MOUSEINPUT mouse = { 0 };

  // Set the event type to "mouse moved"
  mouse.dwFlags = MOUSEEVENTF_MOVE;

  // Set the input type to "mouse"
  input.type = INPUT_MOUSE;

  // Point to the mouse input structure
  input.mi = mouse;

  // Let the user know that Awaken has started
  ::MessageBox(NULL, L"Awaken has started - your system will not enter sleep!", L"Awaken - Keep your PC awake", MB_ICONINFORMATION | MB_OK);

  do
  {
    // Prevent Windows from putting the display/system to sleep
    ::SetThreadExecutionState(ES_DISPLAY_REQUIRED | ES_SYSTEM_REQUIRED);

    // Send a fake mouse movement to prevent screen saver from turning on
    ::SendInput(1, &input, sizeof(INPUT));

    // Wait for 30 seconds
    ::Sleep(30000);
  } while (true);

  // Nothing to see here, quite yet!
  return S_OK;
}
