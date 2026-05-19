/*
This file is part of Nameplate.
Copyright (C) 2024 BunnyBox Productions

Nameplate is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Nameplate is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Nameplate.
If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <inttypes.h>

#if !defined(WINDOZER_INTERFACE_VERSION)
#define WINDOZER_INTERFACE_VERSION 0x04070300
#endif

typedef uint8_t undefined;

class input_manager;
class TextHandler;
class PrimitiveHandler;
class PacketStreamHandler;
class FFXI;

struct MMFSettingsHandler {
    char ProfileName[256];
    char Branch[32];
    char ___pad120[16];
    char LauncherVersion[16];
    char HookVersion[16];
    char PlayOnlinePath[4096];
    char FfxiPath[4096];
    char WindowerPath[4096];
    char ConsoleKey[16];
    uint32_t Region;
    int Width;
    int Height;
    int UIWidth;
    int UIHeight;
    int XPosition;
    int YPosition;
    bool Fullscreen;
    bool Borderless;
    bool Debug;
    bool Loaded;
    bool AlwaysEnableGamepad;
    bool AllowWinKey;
    uint8_t ___pad3182;
    uint8_t ___pad3183;
};

class Console {
    public:
        virtual void __stdcall OpenConsole(bool);
        virtual bool __stdcall IsVisible();
        virtual void __stdcall SetPosition(float, float);
        virtual void __stdcall Write(const char *);
        virtual void __stdcall Clear();
        virtual void __stdcall SendCommand(const char *, bool);
};

#if WINDOZER_INTERFACE_VERSION == 0x40006
class PluginManager {
    public:
        virtual MMFSettingsHandler* __stdcall GetMMFSettingsHandler(MMFSettingsHandler *);
        virtual void * __stdcall GetHWND();
        virtual void * __stdcall GetDirect3D8Device();
        virtual Console* __stdcall GetConsole();
        virtual TextHandler* __stdcall GetTextHandler();
        virtual PrimitiveHandler* __stdcall GetPrimitiveHandler();
        virtual PacketStreamHandler* __stdcall GetPacketStreamHandler();
        virtual void * __stdcall _09_Return_Zero();
        virtual FFXI * __stdcall GetFFXI();
        virtual PluginManager* __thiscall Dtor(uint8_t);
};
#else
class PluginManager {
    public:
        virtual MMFSettingsHandler* __stdcall GetMMFSettingsHandler();
        virtual void * __stdcall GetHWND();
        virtual void * __stdcall GetDirect3D8Device();
        virtual Console* __stdcall GetConsole();
        virtual TextHandler* __stdcall GetTextHandler();
        virtual PrimitiveHandler* __stdcall GetPrimitiveHandler();
        virtual PacketStreamHandler* __stdcall GetPacketStreamHandler();
        virtual FFXI * __stdcall GetFFXI();
        virtual PluginManager* __thiscall Dtor(uint8_t);
};
#endif

#if WINDOZER_INTERFACE_VERSION == 0x40006
struct PluginMetadata {
    uint8_t Unknown0[0x100];
    char Author[0x100];
    uint8_t Unknown1[0x108];
    char Name[0x20];
};

class PluginBase {
    public:
        virtual void __stdcall Load(PluginManager* _manager) { pPluginManager = _manager; }
        virtual void __stdcall Unload() {}
        virtual void __stdcall Dealloc() {
            // if (this != nullptr) {
                this->Dtor(1);
            // }
        }
        virtual PluginMetadata* __stdcall GetMetadata(PluginMetadata* metadata) = 0;
        //{
        //    strncpy(metadata->Author, "Windozer");
        //    strncpy(metadata->Name, "pluginbase");
        //    return metadata;
        //}

        virtual void __stdcall PluginCommand(const char*, const char*) {}
        virtual bool __stdcall UnhandledCommand(const char*) { return false; }
        virtual void __stdcall PreReset() {}
        virtual void __stdcall PostReset() {}
        virtual void __stdcall PreRender() {}
        virtual void __stdcall PostRender() {}
        virtual void __stdcall IncomingText(void *, void *, void *) {}
        virtual void __stdcall OutgoingText(void *, void *, void *) {}
        virtual bool __stdcall IncomingChunk(void *, void *, void *, bool modified) { return modified; }
        virtual bool __stdcall OutgoingChunk(void *, void *, void *, bool modified) { return modified; }
        virtual void __stdcall _14(void *) {} // todo
        virtual bool __stdcall IgnoreUnload() { return false; }
        virtual void __stdcall Reset() {} // todo
        virtual bool __stdcall Mouse(void *, void *, void *, void *, bool modified) { return modified; }
        virtual bool __stdcall Keyboard(void *, void *, bool modified) { return modified; }
        virtual void __stdcall AddItem(void *, void *, void *, void *, void *) {} // todo
        virtual void __stdcall RemoveItem(void *, void *, void *, void *, void *) {} // todo
        virtual PluginBase* __thiscall Dtor(uint8_t) { return this; }

        PluginManager* GetPluginManager() const {
            return pPluginManager;
        }

    protected:
        PluginManager* pPluginManager;
};
#else
class PluginBase {
    public:
        virtual const char* __stdcall GetPluginAuthor() = 0;
        virtual const char* __stdcall GetPluginName() = 0;
        virtual void __stdcall Load(PluginManager* _manager) { pPluginManager = _manager; }
        virtual void __stdcall Unload() {}
        virtual bool __stdcall IgnoreUnload() { return false; }
        virtual void __stdcall PreRender() {}
        virtual void __stdcall PostRender() {}
        virtual void __stdcall PluginCommand(const char*) {}
        virtual bool __stdcall UnhandledCommand(const char*) { return false; }
        virtual void __stdcall IncomingText(void *, void *, void *) {}
        virtual void __stdcall OutgoingText(void *, void *, void *) {}
        virtual bool __stdcall IncomingChunk(void *, void *, void *, bool modified) { return modified; }
        virtual bool __stdcall OutgoingChunk(void *, void *, void *, bool modified) { return modified; }
        virtual bool __stdcall Mouse(void *, void *, void *, void *, bool modified) { return modified; }
        virtual bool __stdcall Keyboard(void *, void *, bool modified) { return modified; }
        virtual void __stdcall AddItem(void *, void *, void *, void *) {} // todo
        virtual void __stdcall RemoveItem(void *, void *, void *, void *) {} // todo
        virtual PluginBase* __thiscall Dtor(uint8_t) { return this; }

        PluginManager* GetPluginManager() const {
            return pPluginManager;
        }

    protected:
        PluginManager* pPluginManager;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define DllExport /*__declspec(dllexport)*/

DllExport uint32_t GetInterfaceVersion();
DllExport PluginBase* CreateInstance();

#ifdef __cplusplus
};
#endif
