#pragma once

#include <memory>
#include "DXUT.h"
#include "engiXDefs.h"
#include "WinInputManager.h"
#include "GameLogic.h"
#include "GameView.h"
#include "D3d11Renderer.h"

namespace engiX
{
    class WinGameApp
    {
    public:
        static const int DEFAULT_SCREEN_WIDTH = 1024;
        static const int DEFAULT_SCREEN_HEIGHT = 768;

        static int Main(
            WinGameApp* pGameInst,
            HINSTANCE hInstance,
            HINSTANCE hPrevInstance,
            LPWSTR    lpCmdLine,
            int       nCmdShow);

        static WinGameApp* Inst();

        WinGameApp();
        void Init(HINSTANCE hInstance, LPWSTR lpCmdLine);
        void Deinit();
        void Run();
        int ExitCode() const { return DXUTGetExitCode(); }
        const SIZE& ScreenSize() const { return m_screenSize; }
        const Timer& GameTime() const { return m_gameTime; }

    protected:
        virtual const wchar_t* VGameAppTitle() const = 0;
        HWND WindowHandle() const { return DXUTGetHWND(); }
        virtual GameLogic* VCreateLogic() const = 0;
        virtual GameView* VCreateStartView() const = 0;

    private:
        // DXUT General Handlers
        static LRESULT CALLBACK OnMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void *pUserContext );
        static bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext );
        static void CALLBACK OnUpdateGame( double fTime, float fElapsedTime, void *pUserContext );

        // DXUT DirectX11 Handlers
        static bool CALLBACK IsD3D11DeviceAcceptable( const CD3D11EnumAdapterInfo *AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo *DeviceInfo, DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext ) { return true; }
        static HRESULT CALLBACK OnD3D11CreateDevice( ID3D11Device* pd3dDevice, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext ) { return S_OK; }
        static HRESULT CALLBACK OnD3D11ResizedSwapChain( ID3D11Device* pd3dDevice, IDXGISwapChain* pSwapChain, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext ) { return S_OK; }
        static void CALLBACK OnD3D11ReleasingSwapChain( void* pUserContext ) {}
        static void CALLBACK OnD3D11DestroyDevice( void* pUserContext ) {}
        static void CALLBACK OnD3D11FrameRender( ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dImmediateContext, double fTime, float fElapsedTime, void* pUserContext ) {}

        WinInputManager m_inputMgr;
        SIZE m_screenSize;
        Timer m_gameTime;
        bool m_firstUpdate;
        std::shared_ptr<GameLogic> m_gameLogic;
        std::shared_ptr<GameView> m_gameView;
        std::shared_ptr<D3d11Renderer> m_pRenderer;
   };

#define g_pApp engiX::WinGameApp::Inst() 
}