#include <Pyx/Scripting/ScriptingContext.h>
#include <Pyx/Graphics/Gui/ImGuiImpl.h>
#include <Pyx/Graphics/Renderer/D3D9Renderer.h>
#include <Pyx/Graphics/Renderer/D3D11Renderer.h>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx9.h>
#include <ImGui/imgui_impl_dx11.h>
#include <Roboto/Font.h>
#include <MaterialDesign/Font.h>
#include <MaterialDesign/IconsMaterialDesign.h>
#include <Pyx/Input/InputContext.h>
#include <ImGui/imgui_internal.h>

Pyx::Graphics::Gui::ImGuiImpl& Pyx::Graphics::Gui::ImGuiImpl::GetInstance()
{
    static ImGuiImpl instance;
    return instance;
}

Pyx::Graphics::Gui::ImGuiImpl::ImGuiImpl()
    : IGui(), m_isResourcesCreated(false), m_isInitialized(false), m_showDebugWindow(false)
{
    m_showDebugWindow = true;
}

Pyx::Graphics::Gui::ImGuiImpl::~ImGuiImpl()
{
}

void Pyx::Graphics::Gui::ImGuiImpl::Initialize()
{
    
    if (m_isInitialized)
        Shutdown();

    auto& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;

    auto* pRenderer = GraphicsContext::GetInstance().GetMainRenderer();
    if (pRenderer)
    {
        switch (pRenderer->GetRendererType())
        {
        case RendererType::D3D9:
        {
            auto* pD3D9Renderer = reinterpret_cast<Renderer::D3D9Renderer*>(pRenderer);
            auto* pDevice9 = pD3D9Renderer->GetDevice();
            if (pDevice9)
            {
                ImGui_ImplDX9_Init(pD3D9Renderer->GetAttachedWindow(), pDevice9);
                if (!m_isResourcesCreated) CreateResources();
                m_isInitialized = true;
            }
            break;
        }
        case RendererType::D3D11:
        {
            auto* pD3D11Renderer = reinterpret_cast<Renderer::D3D11Renderer*>(pRenderer);
            auto* pDevice11 = pD3D11Renderer->GetDevice();
            ID3D11DeviceContext* pDevice11Context = nullptr;
            if (pDevice11)
            {
                pDevice11->GetImmediateContext(&pDevice11Context);
                ImGui_ImplDX11_Init(pD3D11Renderer->GetAttachedWindow(), pDevice11, pDevice11Context);
                pDevice11Context->Release();
                if (!m_isResourcesCreated) CreateResources();
                m_isInitialized = true;
            }
            break;
        }
        default:
            return;
        }
    }

    SetupStyle(true);
    
}

void Pyx::Graphics::Gui::ImGuiImpl::Shutdown()
{
    if (m_isInitialized)
    {

        if (m_isResourcesCreated)
            ReleaseResources();

        m_isInitialized = false;
    }
}

void Pyx::Graphics::Gui::ImGuiImpl::ReleaseResources()
{
    if (m_isResourcesCreated)
    {
        auto* pRenderer = GraphicsContext::GetInstance().GetMainRenderer();
        if (pRenderer)
        {
            switch (pRenderer->GetRendererType())
            {
            case RendererType::D3D9:
            {
                ImGui_ImplDX9_InvalidateDeviceObjects();
                m_isResourcesCreated = false;
                break;
            }
            case RendererType::D3D11:
            {
                ImGui_ImplDX11_InvalidateDeviceObjects();
                m_isResourcesCreated = false;
                break;
            }
            default:
                return;
            }
        }
    }
}

void Pyx::Graphics::Gui::ImGuiImpl::CreateResources()
{
    if (!m_isResourcesCreated)
    {

        ImGuiIO& io = ImGui::GetIO();
        ImFontConfig font_cfg;
        font_cfg.FontDataOwnedByAtlas = false;
        font_cfg.MergeMode = false;
        font_cfg.MergeGlyphCenterV = true;
        io.Fonts->AddFontFromMemoryTTF(Roboto_TTF_Data, RobotoFont_TTF_DataSize, 18.0f, &font_cfg);
        font_cfg.MergeMode = true;
        font_cfg.PixelSnapH = true;
        font_cfg.MergeGlyphCenterV = true;
        static const ImWchar icons_ranges_md[] = { ICON_MIN_MD, ICON_MAX_MD, 0 };
        io.Fonts->AddFontFromMemoryTTF(Material_TTF_Data, MaterialFont_TTF_DataSize, 18.0f, &font_cfg, icons_ranges_md);

        auto* pRenderer = GraphicsContext::GetInstance().GetMainRenderer();
        if (pRenderer)
        {
            switch (pRenderer->GetRendererType())
            {
            case RendererType::D3D9:
            {
                m_isResourcesCreated = ImGui_ImplDX9_CreateDeviceObjects();
                break;
            }
            case RendererType::D3D11:
            {
                m_isResourcesCreated = ImGui_ImplDX11_CreateDeviceObjects();
                break;
            }
            default:
                return;
            }
        }
    }
}

void Pyx::Graphics::Gui::ImGuiImpl::OnFrame()
{
    if (m_isInitialized)
    {

        if (!m_isResourcesCreated)
            CreateResources();

        if (m_isResourcesCreated)
        {
            auto* pRenderer = GraphicsContext::GetInstance().GetMainRenderer();

            if (pRenderer)
            {

                auto& io = ImGui::GetIO();

                if (Input::InputContext::GetInstance().CursorIsVisible())
                {
                    auto cursorPos = Input::InputContext::GetInstance().GetCursorPosition();
                    ScreenToClient(pRenderer->GetAttachedWindow(), &cursorPos);
                    io.MousePos.x = cursorPos.x;
                    io.MousePos.y = cursorPos.y;

                    BYTE keyboardState[256];
                    ::GetKeyboardState(keyboardState);
                    io.MouseDown[0] = GetAsyncKeyState(VK_LBUTTON) != 0;
                    io.MouseDown[1] = GetAsyncKeyState(VK_RBUTTON) != 0;
                    io.MouseDown[2] = GetAsyncKeyState(VK_MBUTTON) != 0;
                }

                switch (pRenderer->GetRendererType())
                {
                case RendererType::D3D9:
                {
                    ImGui_ImplDX9_NewFrame();
                    break;
                }
                case RendererType::D3D11:
                {
                    ImGui_ImplDX11_NewFrame();
                    break;
                }
                default:
                    return;
                }

				if (m_isVisible)
				{

					BuildMainMenuBar();

					if (m_showConsole)
						BuildLogsWindow();

					if (m_showDebugWindow)
						BuildDebugWindow();

					GetOnRenderCallbacks().Run(this);
					Scripting::ScriptingContext::GetInstance().FireCallbacks(L"ImGui.OnRender");

					ImGui::Render();

				}

            }

			static int lastToggleVisibilityTick = 0;
			if (GetTickCount() - lastToggleVisibilityTick > 250)
			{

				bool shouldToggle = true;
				for (auto vKey : PyxContext::GetInstance().GetSettings().GuiToggleVisibilityHotkeys)
				{
					if (GetAsyncKeyState(vKey) == NULL)
					{
						shouldToggle = false;
						break;
					}
				}

				if (shouldToggle)
				{
					ToggleVisibility(!IsVisible());
					lastToggleVisibilityTick = GetTickCount();
				}

			}

        }

    }

}

bool Pyx::Graphics::Gui::ImGuiImpl::OnWindowMessage(const MSG* lpMsg)
{
    if (!Input::InputContext::GetInstance().CursorIsVisible() || !IsVisible())
        return false;

    if (m_isInitialized && lpMsg)
    {
        auto* pRenderer = GraphicsContext::GetInstance().GetMainRenderer();
        ImGuiIO& io = ImGui::GetIO();
        if (pRenderer && pRenderer->GetAttachedWindow() == lpMsg->hwnd)
        {
            switch (lpMsg->message)
            {
            case WM_LBUTTONDOWN:
                return io.WantCaptureMouse;
            case WM_LBUTTONUP:
                return io.WantCaptureMouse;
            case WM_RBUTTONDOWN:
                return io.WantCaptureMouse;
            case WM_RBUTTONUP:
                return io.WantCaptureMouse;
            case WM_MBUTTONDOWN:
                return io.WantCaptureMouse;
            case WM_MBUTTONUP:
                return io.WantCaptureMouse;
            case WM_MOUSEWHEEL:
                io.MouseWheel += GET_WHEEL_DELTA_WPARAM(lpMsg->wParam) > 0 ? +1.0f : -1.0f;
                return io.WantCaptureMouse;
            case WM_MOUSEMOVE:
                return io.WantCaptureMouse;
            case WM_KEYDOWN:
                if (lpMsg->wParam < 256)
                    io.KeysDown[lpMsg->wParam] = 1;
                return io.WantCaptureKeyboard || io.WantTextInput;
            case WM_KEYUP:
                if (lpMsg->wParam < 256)
                    io.KeysDown[lpMsg->wParam] = 0;
                return io.WantCaptureKeyboard || io.WantTextInput;
            case WM_CHAR:
                if (lpMsg->wParam > 0 && lpMsg->wParam < 0x10000)
                    io.AddInputCharacter((unsigned short)lpMsg->wParam);
                return io.WantCaptureKeyboard || io.WantTextInput;
            }
        }
    }

    return false;
}

void Pyx::Graphics::Gui::ImGuiImpl::Logger_OnWriteLine(const std::wstring& line)
{
    if (m_logsItems.size() > 100)
        m_logsItems.erase(m_logsItems.begin());

    m_logsItems.push_back(Utility::String::utf8_encode(line));
    m_logScrollToEnd = true;
}

bool Pyx::Graphics::Gui::ImGuiImpl::OnGetCursorPos(LPPOINT lpPoint)
{
    if (lpPoint == nullptr)
        return false;

    auto& io = ImGui::GetIO();

    if (io.WantCaptureMouse)
    {
        *lpPoint = m_lastValidMousePosition;
        return true;
    }
    
    m_lastValidMousePosition = *lpPoint;
    return false;
}

void Pyx::Graphics::Gui::ImGuiImpl::SetupStyle(bool bDarkStyle) const
{

    ImGuiStyle& style = ImGui::GetStyle();

    ImVec4 Full = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    style.FrameRounding = 3.0f;
    style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
    style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
    style.Colors[ImGuiCol_ComboBg] = ImVec4(0.86f, 0.86f, 0.86f, 0.99f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
    style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    style.Colors[ImGuiCol_CloseButton] = ImVec4(0.59f, 0.59f, 0.59f, 0.50f);
    style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
    style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
    style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

    if (bDarkStyle)
    {
        for (int i = 0; i <= ImGuiCol_COUNT; i++)
        {
            ImVec4& col = style.Colors[i];
            float H, S, V;
            ImGui::ColorConvertRGBtoHSV(col.x, col.y, col.z, H, S, V);

            if (S < 0.1f)
            {
                V = 1.0f - V;
            }
            ImGui::ColorConvertHSVtoRGB(H, S, V, col.x, col.y, col.z);
        }
    }

}

void Pyx::Graphics::Gui::ImGuiImpl::ToggleVisibility(bool bVisible)
{
	m_isVisible = bVisible;
}

void Pyx::Graphics::Gui::ImGuiImpl::BuildMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {

        if (ImGui::BeginMenu((std::string(ICON_MD_HOME) + XorStringA(" Pyx")).c_str()))
        {
			ImGui::MenuItem((std::string(ICON_MD_FORMAT_LIST_BULLETED) + XorStringA(" Show console")).c_str(), nullptr, &m_showConsole);
			ImGui::MenuItem((std::string(ICON_MD_BUILD) + XorStringA(" Show debug window")).c_str(), nullptr, &m_showDebugWindow);
			ImGui::Separator();
            if (ImGui::MenuItem((std::string(ICON_MD_EXIT_TO_APP) + XorStringA(" Unload")).c_str())) { PyxContext::GetInstance().RequestShutdown(); }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu((std::string(ICON_MD_EXTENSION) + XorStringA(" Scripts")).c_str()))
        {

            for (auto* pScript : Scripting::ScriptingContext::GetInstance().GetScripts())
                if (pScript->IsRunning())
                {
                    auto& name = pScript->GetName();
                    if (ImGui::MenuItem((std::string(ICON_MD_CLEAR) + " " + Utility::String::utf8_encode(name)).c_str(), XorStringA("(running)")))
                    {
                        pScript->Stop();
                    }
                }            
            
            for (auto* pScript : Scripting::ScriptingContext::GetInstance().GetScripts())
                    if (!pScript->IsRunning())
                    {
                        auto& name = pScript->GetName();
                        if (ImGui::MenuItem((std::string(ICON_MD_PLAY_CIRCLE_OUTLINE) + " " + Utility::String::utf8_encode(name)).c_str(), "(stopped)"))
                        {
                            pScript->Start();
                        }
                    }

            ImGui::Separator();
            if (ImGui::MenuItem((std::string(ICON_MD_REPLAY) + XorStringA(" Reload scripts")).c_str())) { Scripting::ScriptingContext::GetInstance().ReloadScripts(); }
            ImGui::EndMenu();
        }
        
        GetOnDrawMainMenuBarCallbacks().Run(this);
        Scripting::ScriptingContext::GetInstance().FireCallbacks(L"ImGui.OnRenderMainMenuBar");

        ImGui::EndMainMenuBar();
    }
}

void Pyx::Graphics::Gui::ImGuiImpl::BuildDebugWindow()
{
    if (GImGui)
    {
        ImGuiState& g = *GImGui;
        if (ImGui::Begin("Pyx - Debug##pyx_debug_window", &m_showDebugWindow))
        {
            auto& io = ImGui::GetIO();
            ImGui::Text("Performance : %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::Text("Renderer : %s", GraphicsContext::GetInstance().GetMainRenderer()->GetRendererTypeString());
            ImGui::Text("Cursor visible : %d", Input::InputContext::GetInstance().CursorIsVisible());
            ImGui::Text("Cursor position : %.0f, %.0f", io.MousePos.x, io.MousePos.y);
            ImGui::Text("WantCaptureMouse : %d", io.WantCaptureMouse);
            ImGui::Text("WantCaptureKeyboard : %d", io.WantCaptureKeyboard);
            ImGui::Text("WantTextInput : %d", io.WantTextInput);
            ImGui::Text("HoveredWindow : %s", g.HoveredWindow ? g.HoveredWindow->Name : "<null>");
        }
        ImGui::End();
    }
}

void Pyx::Graphics::Gui::ImGuiImpl::BuildLogsWindow()
{
    static bool logVisible = true;
    if (GImGui)
    {
        ImGuiState& g = *GImGui;
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.8f);
        if (ImGui::Begin("##pyx_console_logs", &logVisible, ImVec2(ImGui::GetIO().DisplaySize.x, 155), -1, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
        {
            ImGui::SetWindowPos(ImVec2(0, g.FontBaseSize + g.Style.FramePadding.y * 2.0f));
            ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetWindowHeight()));

            for (std::string& item : m_logsItems)
            {
                ImVec4 col = ImColor(255, 255, 255);
                ImGui::PushStyleColor(ImGuiCol_Text, col);
                ImGui::TextUnformatted(item.c_str());
                ImGui::PopStyleColor();
            }

            if (m_logScrollToEnd) ImGui::SetScrollHere();
            m_logScrollToEnd = false;


        }
        ImGui::End();
		ImGui::PopStyleVar(3);
    }
}
