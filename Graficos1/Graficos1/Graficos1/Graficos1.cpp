#include <windows.h>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "GraphicModule.h"

// -----------------Global var-----------------------------------------------------------------
HWND g_hwnd;
GraphicsModule::test MiObj;

/**
 * @brief   Forward declare message handler from imgui_impl_win32.cpp
 * @param   #HWND: A handle to the window.
 * @param   #UINT: The message.
 * @param   #WPARAM: Additional message information. The contents of this parameter depend on the value of the uMsg parameter.
 * @param   #LPARAM: Additional message information. The contents of this parameter depend on the value of the uMsg parameter.
 * @return  #LRESULT: The return value is the result of the message processing and depends on the message sent..
 * @bug     No know Bugs.
 * @return  #LRESULT: Status code.
 */
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

/**
 * @brief   Message bomb.
 * @param   #HWND: A handle to the window.
 * @param   #UINT: The message.
 * @param   #WPARAM: Additional message information. The contents of this parameter depend on the value of the uMsg parameter.
 * @param   #LPARAM: Additional message information. The contents of this parameter depend on the value of the uMsg parameter.
 * @return  #LRESULT: The return value is the result of the message processing and depends on the message sent..
 */
LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
  // Handle UI inputs
  if (ImGui_ImplWin32_WndProcHandler(_hwnd, _msg, _wParam, _lParam))
    return 1;

  // Handle Window inputs
  switch (_msg)
  {
  case WM_SIZE:
    //if (g_pd3dDevice != NULL && _wParam != SIZE_MINIMIZED)
    {
    }
    return 0;
    break;

  case WM_SYSCOMMAND:
    if ((_wParam & 0xfff0) == SC_KEYMENU)
    {
      return 0;
    }
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  }
  return ::DefWindowProc(_hwnd, _msg, _wParam, _lParam);
}

/**
 * @brief   Set the style for the main window and init it.
 * @param   #unsigned int: First window width.
 * @param   #unsigned int: First window height.
 * @bug     No know Bugs.
 * @return  #HRESULT: Status code.
 */
HRESULT InitWindow(LONG _width, LONG _height)
{
  // Register class
  WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = nullptr;
  wcex.hIcon = nullptr;
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = "TutorialWindowClass";
  wcex.hIconSm = nullptr;
  if (!RegisterClassEx(&wcex))
  {
    return E_FAIL;
  }

  // Create window
  RECT rc = { 0, 0, _width, _height };
  AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
  g_hwnd = CreateWindow("TutorialWindowClass", "Graficos 1", WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, CW_USEDEFAULT, _width, _height, NULL, NULL, NULL, NULL);
  if (!g_hwnd)
  {
    return E_FAIL;
  }
  ShowWindow(g_hwnd, SW_SHOWNORMAL);

  return S_OK;
}

/**
 * @brief   Init the UI.
 * @bug     No know Bugs.
 * @return  #HRESULT: Status code.
 */

HRESULT InitImgUI()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer back ends
    
    ImGui_ImplWin32_Init(MiObj.m_hwnd);
    ImGui_ImplDX11_Init( MiObj.getdevice(), MiObj.getcontext());

    return S_OK;
}
void UIrender() {

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // example window
    if (ImGui::Begin("Another Window", nullptr))
    {
        ImGui::Text("Hello from another window!");
    }
    ImGui::End();

    // render UI
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}


/**
 * @brief   Entry point.
 * @bug     No know Bugs.
 * @return  #int: Status code.
 */
int main()
{
  // create the window and console
  if (FAILED(InitWindow(1280, 720)))
  {
    DestroyWindow(g_hwnd);
    return 0;
  }
  
  // create Graphic API interface
  if (FAILED(MiObj.InitDevice(g_hwnd)))
  {
    MiObj.CleanupDevice();
    return 0;
  }

  // create UI
  if (FAILED(InitImgUI()))
  {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    return 0;
  }

  // main loop
  MSG msg = { 0 };
  while (WM_QUIT != msg.message)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
    
        MiObj.Updeate();
        MiObj.Render(UIrender);
     
    }
  }
  // clean resources
  //ImGui_ImplDX11_Shutdown();
  //ImGui_ImplWin32_Shutdown();
  //ImGui::DestroyContext();
  MiObj.CleanupDevice();
  DestroyWindow(g_hwnd);
  return (int)msg.wParam;
}