#pragma once
#include <Windows.h>

namespace Pyx
{
    namespace Input
    {
        
        class InputContext
        {
            
        public:
            static InputContext& GetInstance();

        private:
            int m_showCursorCount = 0;
            POINT m_cursorPosition;

        public:
            void Initialize();
            void Shutdown();
            bool OnWindowMessage(LPMSG lpMsg);
            bool OnShowCursor(BOOL bShow, int* pReturnValue);
            bool OnGetCursorPos(LPPOINT lpPoint);
            bool CursorIsVisible() const { return m_showCursorCount >= 0 && GetCursor() != nullptr; }
            int  GetShowCursorCount() const { return m_showCursorCount; }
            POINT GetCursorPosition();

        };

    }
}