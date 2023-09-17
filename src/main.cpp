

#include <Windows.h>

#include <dwmapi.h>


#include "../imgui/imgui.h"

#include "../imgui/imgui_impl_dx11.h"

#include "../imgui/imgui_impl_win32.h"

#include "globals.h"
#include "gui/gui.h"

#include <d3d11.h>

#include "memory/memory.h"
#include "atlstr.h"

#include "hack.h"

int windowstate = 1;

Hack* hack = nullptr;

void ChangeClickability(bool canclick, HWND ownd)
{
	long style = GetWindowLong(
		ownd, GWL_EXSTYLE);
	if (canclick) {
		style &= ~WS_EX_LAYERED;
		SetWindowLong(ownd,
			GWL_EXSTYLE, style);
		SetForegroundWindow(ownd);
		windowstate = 1;
	}
	else {
		style |= WS_EX_LAYERED;
		SetWindowLong(ownd,
			GWL_EXSTYLE, style);
		windowstate = 0;
	}
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK window_procedure(HWND window, UINT message, WPARAM w_param, LPARAM l_param) {
	if (ImGui_ImplWin32_WndProcHandler(window, message, w_param, l_param) && gui::open) {
		ImGuiIO& io = ImGui::GetIO();
		switch (message) {
		case WM_LBUTTONDOWN:
			io.MouseDown[0] = true;
			return true;
		case WM_LBUTTONUP:
			io.MouseDown[0] = false;
			return true;
		case WM_RBUTTONDOWN:
			io.MouseDown[1] = true;
			return true;
		case WM_RBUTTONUP:
			io.MouseDown[1] = false;
			return true;
		case WM_MBUTTONDOWN:
			io.MouseDown[2] = true;
			return true;
		case WM_MBUTTONUP:
			io.MouseDown[2] = false;
			return true;
		case WM_XBUTTONDOWN:
			if ((GET_KEYSTATE_WPARAM(w_param) & MK_XBUTTON1) == MK_XBUTTON1)
				io.MouseDown[3] = true;
			else if ((GET_KEYSTATE_WPARAM(w_param) & MK_XBUTTON2) == MK_XBUTTON2)
				io.MouseDown[4] = true;
			return true;
		case WM_XBUTTONUP:
			if ((GET_KEYSTATE_WPARAM(w_param) & MK_XBUTTON1) == MK_XBUTTON1)
				io.MouseDown[3] = false;
			else if ((GET_KEYSTATE_WPARAM(w_param) & MK_XBUTTON2) == MK_XBUTTON2)
				io.MouseDown[4] = false;
			return true;
		case WM_MOUSEWHEEL:
			io.MouseWheel += GET_WHEEL_DELTA_WPARAM(w_param) > 0 ? +1.0f : -1.0f;
			return true;
		case WM_MOUSEMOVE:
			io.MousePos.x = (signed short)(l_param);
			io.MousePos.y = (signed short)(l_param >> 16);
			return true;
		case WM_KEYDOWN:
			if (w_param < 256)
				io.KeysDown[w_param] = 1;
			return true;
		case WM_KEYUP:
			if (w_param < 256)
				io.KeysDown[w_param] = 0;
			return true;
		case WM_CHAR:
			if (w_param > 0 && w_param < 0x10000) {
				io.AddInputCharacter((unsigned short)w_param);
			}
				
			return true;
		}
		return 0L;
	}

	if (message == WM_DESTROY) {
		PostQuitMessage(0);
		return 0l;
	}

	return DefWindowProc(window, message, w_param, l_param);
}			



INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE, PSTR, INT cmd_show) {

	WNDCLASSEXW wc{};
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = window_procedure;
	wc.hInstance = instance;
	wc.lpszClassName = L"External Overlay";

	RegisterClassExW(&wc);

	HWND targetwindow = FindWindow(NULL, L"Counter-Strike: Global Offensive - Direct3D 9");
	
	if (!targetwindow) {
		exit(0);
	}

	GetWindowThreadProcessId(targetwindow, &memory::pID);
	if (!memory::pID) {
		exit(0);
	}

	memory::hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, (DWORD)memory::pID);
	
	if (memory::hProcess == INVALID_HANDLE_VALUE || memory::hProcess == NULL) {
		exit(0);
	}

	


	const HWND window = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE | WS_EX_LAYERED,
		wc.lpszClassName,
		L"Overlay",
		WS_POPUP,
		1, 1, 1920, 1080, 
		nullptr, nullptr, wc.hInstance, nullptr);

	//SetLayeredWindowAttributes(window, 0, 1.0f, LWA_ALPHA);
	SetLayeredWindowAttributes(window, RGB(0, 0, 0), BYTE(255), LWA_ALPHA);

	{
		RECT client_area{};
		GetClientRect(window, &client_area);

		RECT window_area{};
		GetWindowRect(window, &window_area);

		POINT diff{};
		ClientToScreen(window, &diff);

		const MARGINS margins{
			window_area.left + (diff.x - window_area.left),
			window_area.top + (diff.y - window_area.top),
			client_area.right,
			client_area.bottom
		};

		DwmExtendFrameIntoClientArea(window, &margins);
	}

	DXGI_SWAP_CHAIN_DESC sd{};
	sd.BufferDesc.RefreshRate.Numerator = 144U;
	sd.BufferDesc.RefreshRate.Denominator = 1U;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.SampleDesc.Count = 1U; 
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2U;
	sd.OutputWindow = window;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	constexpr D3D_FEATURE_LEVEL levels[2]{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0

	};

	ID3D11Device* device{ nullptr };
	ID3D11DeviceContext* device_context{ nullptr };
	IDXGISwapChain* swap_chain{ nullptr };
	ID3D11RenderTargetView* render_target_view{ nullptr };
	D3D_FEATURE_LEVEL level{};

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0U,
		levels,
		2U,
		D3D11_SDK_VERSION,
		&sd,
		&swap_chain,
		&device,
		&level,
		&device_context);
	
	ID3D11Texture2D* back_buffer{ nullptr };

	swap_chain->GetBuffer(0U, IID_PPV_ARGS(&back_buffer));

	if (!back_buffer) {
		return 1;
	}
	device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view);
	back_buffer->Release();

	ShowWindow(window, cmd_show);
	UpdateWindow(window);

	ImGui::CreateContext();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(device, device_context);
	
	while (globals::active) {

		HWND backwindow = GetForegroundWindow();

		bool focus = false;

		if (backwindow == targetwindow || backwindow == window) {
			focus = true;
		}
		
		MSG msg;
		while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {

			
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				globals::active = false;
			}
		}
		
		if (!globals::active) {
			break;
		}


		gui::Setup();

		hack->Update();

		if (focus) {
			hack->MainLoop();
		}
		

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();

		ImDrawList* draw = ImGui::GetBackgroundDrawList();

		if (GetAsyncKeyState(VK_F1)) {	
			globals::active = false;
			break;
		}
		
		if (gui::open && focus) //You might need to remove this check and call it every time to get keyboard input working. Mouse input works anyway.
		{
			ChangeClickability(true, window);
			
		}
		else
		{
			
			if (windowstate != 0)
			{
				ChangeClickability(false, window);
		

			}
		}

		

		if (focus) {
			gui::OnPaint(draw);
		}
		
		
		ImGui::Render();
		

		constexpr float color[4]{ 0.f,0.f,0.f,0.f };
		device_context->OMSetRenderTargets(1U, &render_target_view, nullptr);
		device_context->ClearRenderTargetView(render_target_view, color);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		swap_chain->Present(1U, 0U);


	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	if (swap_chain) {
		swap_chain->Release();
	}

	if (device_context) {
		device_context->Release();
	}

	if (device) {
		device->Release();
	}

	if (render_target_view) {
		render_target_view->Release();
	}

	DestroyWindow(window);
	UnregisterClassW(wc.lpszClassName, wc.hInstance);

	return 0;
}