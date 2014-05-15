#pragma once

#include <memory>
#include <vector>
#include <stack>
#include <d3d11.h>
#include "Timer.h"
#include "Delegate.h"
#include "Events.h"
#include "SceneCameraNode.h"
#include "ViewInterfaces.h"

namespace engiX
{
    class SceneCameraNode;

    class GameScene
    {
    public:
        GameScene();
        ~GameScene();
        void OnUpdate(_In_ const Timer& time);
        void OnRender();
        HRESULT OnConstruct();
        void OnActorCreated(_In_ EventPtr pEvt);
        void OnActorDestroyed(_In_ EventPtr pEvt);
        void OnToggleCamera(_In_ EventPtr pEvt);
        bool Init();
        std::shared_ptr<SceneCameraNode> Camera() { return m_pCameraNodes[m_currCameraIdx]; }
        void PushTransformation(_In_ const Mat4x4& t);
        void PopTransformation();
        const Mat4x4 TopTransformation() const { return m_worldTransformationStack.top(); }

    protected:
        ISceneNode* m_pSceneRoot;
        std::vector<std::shared_ptr<SceneCameraNode>> m_pCameraNodes;
        std::stack<Mat4x4> m_worldTransformationStack;
        ID3D11RasterizerState* m_pWireframeRS;
        size_t m_currCameraIdx;
    };
    
    typedef std::shared_ptr<GameScene> StrongGameScenePtr;
}