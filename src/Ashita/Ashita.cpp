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

#include <windows.h>
#include <strsafe.h>

#include "Ashita.h"

#include "../Nameplate.h"

#include "exports.h"


#define LogLevel_Info ((uint32_t) Ashita::LogLevel::Info)
#define LogLevel_Critcal ((uint32_t) Ashita::LogLevel::Critical)


class AshitaNameplate : public IPlugin, private Nameplate {
private:
    IAshitaCore* m_AshitaCore;
    ILogManager* m_LogManager;
    uint32_t m_PluginId;

public:
	AshitaNameplate();

    virtual const char* GetName(void) const override;
    virtual const char* GetAuthor(void) const override;
    virtual const char* GetDescription(void) const override;
    virtual const char* GetLink(void) const override;
    virtual double GetVersion(void) const override;
    virtual double GetInterfaceVersion(void) const override;
    virtual int32_t GetPriority(void) const override;
    virtual uint32_t GetFlags(void) const override;

    virtual bool Initialize(IAshitaCore* core, ILogManager* log, uint32_t id) override;
    virtual void Release(void) override;

    virtual void Debug(const char* text) override {
        m_AshitaCore->GetChatManager()->Write(0, false, text);
    }

    virtual bool GetConfigPath(wchar_t path[UNICODE_MAX_PATH]) override {
        const char* installPath = m_AshitaCore->GetInstallPath();

        StringCchPrintfW(path, UNICODE_MAX_PATH, L"%S\\config", installPath);
        return true;
    }

    bool HandleCommand(int32_t mode, const char* command, bool injected) override;

    virtual void ShowMessage(MESSAGE message, int param) override;
};

AshitaNameplate::AshitaNameplate() : m_AshitaCore(nullptr), m_LogManager(nullptr), m_PluginId(0) {
}

const char* AshitaNameplate::GetName(void) const {
    return "Nameplate";
}

const char* AshitaNameplate::GetAuthor(void) const {
    return "BunnyBox Productions";
}

const char* AshitaNameplate::GetDescription(void) const {
    return "Corrects defects in nameplate rendering.";
}

const char* AshitaNameplate::GetLink(void) const {
    return "https://www.github.com/Shirk/Nameplate";
}

double AshitaNameplate::GetVersion(void) const {
    return 0.60;
}

double AshitaNameplate::GetInterfaceVersion(void) const {
    return ASHITA_INTERFACE_VERSION;
}

int32_t AshitaNameplate::GetPriority(void) const {
    return 0;
}

uint32_t AshitaNameplate::GetFlags(void) const {
    return static_cast<uint32_t>(Ashita::PluginFlags::UseCommands);
}

bool AshitaNameplate::Initialize(IAshitaCore* core, ILogManager* log, uint32_t id) {
    m_AshitaCore = core;
    m_LogManager = log;
    m_PluginId = id;

    int ret = this->Init();
    if (ret < 0) {
        m_LogManager->Logf(LogLevel_Critcal, "Nameplate", "Plugin Load Error: \"%d\"", ret);
        ShowMessage(MESSAGE::PLUGIN_LOAD_ERROR, ret);
        return false;
    }

	return true;
}

void AshitaNameplate::Release(void) {

    int ret = this->Deinit();
    if (ret < 0) {
        m_LogManager->Logf(LogLevel_Critcal, "Nameplate", "Plugin Unload Error: \"%d\"", ret);
        ShowMessage(MESSAGE::PLUGIN_UNLOAD_ERROR, ret);
    }

    IPlugin::Release();
}

bool AshitaNameplate::HandleCommand([[maybe_unused]] int32_t mode, const char* command, [[maybe_unused]] bool injected) {
    return ParseCommand(command, true);
}

void AshitaNameplate::ShowMessage(MESSAGE message, int param) {
    auto* chat = m_AshitaCore->GetChatManager();

    switch (message) {
        case MESSAGE::PLUGIN_LOAD_ERROR: {
            chat->Writef(0, false, "\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x44Plugin load failed with error code \x1e\x05%d\x1e\x44!", param);
        }
        break;

        case MESSAGE::PLUGIN_UNLOAD_ERROR: {
            chat->Writef(0, false, "\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x44Plugin unload failed with error code \x1e\x05%d\x1e\x44!", param);
        }
        break;

        case MESSAGE::SHORT_HELP: {
            chat->Write(0, false, "\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x44Unknown command, please consult \x1e\x6a/nameplate help\x1e\x44 for more information.");
        }
        break;

        case MESSAGE::LONG_HELP: {
            chat->Write(0, false, "\x1e\x05Nameplate v0.60");
            chat->Write(0, false, "\x1e\x05https://www.github.com/Shirk/Nameplate");
            chat->Write(0, true, "Please visit the Nameplate website");
            chat->Write(0, true, "for the latest information on how to use the plugin");
            chat->Write(0, false, "\x1e\x05Use \x1e\x6a/nameplate commands\x1e\x44 to see the list of commands");
        }
        break;

        case MESSAGE::COMMAND_HELP: {
            chat->Write(0, false, "\x1e\x6a/nameplate commands");
            chat->Write(0, true , "You're reading it!");
            chat->Write(0, false, "\x1e\x6a/nameplate load");
            chat->Write(0, true , "Load configuration from\x1e\x6a config\\nameplate\\defaults.ini");
            chat->Write(0, false, "\x1e\x6a/nameplate save");
            chat->Write(0, true , "Save current configuration to\x1e\x6a config\\nameplate\\defaults.ini");
            chat->Write(0, false, "\x1e\x6a/nameplate fontsize\x1e\x6a <number>");
            chat->Write(0, true , "Set the nameplate font size to <number> pixels");
            chat->Write(0, false, "\x1e\x6a/nameplate damagefontsize\x1e\x6a <number>");
            chat->Write(0, true , "Set the damage font size to <number> pixels");
            chat->Write(0, false, "\x1e\x6a/nameplate fontscalex\x1e\x6a <number>");
            chat->Write(0, true , "Set the nameplate font X-scale factor to <number>");
            chat->Write(0, false, "\x1e\x6a/nameplate fontscaley\x1e\x6a <number>");
            chat->Write(0, true , "Set the nameplate font Y-scale factor to <number>");
            chat->Write(0, false, "\x1e\x6a/nameplate damagefontscalex\x1e\x6a <number>");
            chat->Write(0, true , "Set the damage font X-scale factor to <number>");
            chat->Write(0, false, "\x1e\x6a/nameplate damagefontscaley\x1e\x6a <number>");
            chat->Write(0, true , "Set the damage font Y-scale factor to <number>");
            chat->Write(0, false, "\x1e\x6a/nameplate hidestars");
            chat->Write(0, true , "Hide all Job Mastery stars");
            chat->Write(0, false, "\x1e\x6a/nameplate showstars");
            chat->Write(0, true , "Re-enable displaying Job Mastery stars");
            chat->Write(0, false, "\x1e\x6a/nameplate mode all");
            chat->Write(0, true , "Show all nameplates");
            chat->Write(0, false, "\x1e\x6a/nameplate mode none");
            chat->Write(0, true , "Hide all nameplates");
            chat->Write(0, false, "\x1e\x6a/nameplate mode hideself");
            chat->Write(0, true , "Hide your own nameplate");
            chat->Write(0, false, "\x1e\x6a/nameplate mode hidepc");
            chat->Write(0, true , "Hide all player nameplates, except when charmed");
            chat->Write(0, false, "\x1e\x6a/nameplate mode hidepcself");
            chat->Write(0, true , "Hide all player nameplates, except when charmed, but also keep yours always hidden");
            chat->Write(0, false, "\x1e\x6a/nameplate mode hidenpc");
            chat->Write(0, true , "Hide all non-player nameplates");
            chat->Write(0, false, "\x1e\x6a/nameplate mode hidenpcself");
            chat->Write(0, true , "Hide all non-player nameplates, but also keep yours always hidden");
            chat->Write(0, false, "\x1e\x6a/nameplate scalemode pixel");
            chat->Write(0, true , "Use the original pixel-based scaling mode for the nameplate and damage fonts");
            chat->Write(0, false, "\x1e\x6a/nameplate scalemode scale");
            chat->Write(0, true , "Use the X/Y scale factors for the nameplate and damage fonts");
        }
        break;

        case MESSAGE::CURRENT_SETTINGS: {
            chat->Write(0, false, "\x1e\x05Nameplate v0.60");
            chat->Write(0, false, "\x1e\x05https://www.github.com/Shirk/Nameplate");
            if (Settings.GetScaleMode() == FONT_SCALE_MODE::PIXEL) {
                chat->Writef(0, true, "Font Size: \x1e\x05%.1f\x1e\x44 px", Settings.GetFontSize());
                chat->Writef(0, true, "Damage Font Size: \x1e\x05%.1f\x1e\x44 px", Settings.GetDamageFontSize());
            } else {
                chat->Writef(0, true, "Font Scale X: \x1e\x05%.2f", Settings.GetFontScaleX());
                chat->Writef(0, true, "Font Scale Y: \x1e\x05%.2f", Settings.GetFontScaleY());
                chat->Writef(0, true, "Damage Font Scale X: \x1e\x05%.2f", Settings.GetDamageScaleX());
                chat->Writef(0, true, "Damage Font Scale Y: \x1e\x05%.2f", Settings.GetDamageScaleY());
                chat->Writef(0, true, "Scale Mode: \x1e\x05%s", Settings.GetScaleMode() == FONT_SCALE_MODE::PIXEL ? "pixel" : "scale");
                chat->Writef(0, true, "Hide Stars: \x1e\x05%s", Settings.GetHideStars() ? "yes" : "no");
            }

            const char* mode = "unknown";
            switch (Settings.GetNameMode()) {
                case NAME_MODE::ALL:
                    mode = "all";
                    break;
                case NAME_MODE::NONE:
                    mode = "none";
                    break;
                case NAME_MODE::HIDE_SELF:
                    mode = "hideself";
                    break;
                case NAME_MODE::HIDE_PC:
                    mode = "hidepc";
                    break;
                case NAME_MODE::HIDE_PCSELF:
                    mode = "hidepcself";
                    break;
                case NAME_MODE::HIDE_NPC:
                    mode = "hidenpc";
                    break;
                case NAME_MODE::HIDE_NPCSELF:
                    mode = "hidenpcself";
                    break;
            }
            chat->Writef(0, true, "Display Mode: \x1e\x05%s", mode);
        }
        break;

        case MESSAGE::LOAD_ERROR: {
            chat->Writef(0, false, "\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x44Loading\x1e\x6a config\\nameplate\\defaults.ini\x1e\x44 failed with error code \x1e\x05%d\x1e\x44!", param);
        }
        break;

        case MESSAGE::LOAD_COMMAND_ERROR: {
            chat->Write(0, false, "\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate load\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::SAVE_ERROR: {
            chat->Writef(0, false, "\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x44Saving\x1e\x6a config\\nameplate\\defaults.ini\x1e\x44 failed with error code \x1e\x05%d\x1e\x44!", param);
        }
        break;

        case MESSAGE::SAVE_COMMAND_ERROR: {
            chat->Write(0, false, "\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate save\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::FONT_SIZE_COMMAND_ERROR: {
            chat->Write(0, false, "\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate fontsize\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::DAMAGE_FONT_SIZE_COMMAND_ERROR: {
            chat->Write(0, false, "\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate damagefontsize\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::FONT_SCALE_X_COMMAND_ERROR: {
            chat->Write(0, false, "\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate fontscalex\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::FONT_SCALE_Y_COMMAND_ERROR: {
            chat->Write(0, false, "\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate fontscaley\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::DAMAGE_FONT_SCALE_X_COMMAND_ERROR: {
            chat->Write(0, false, "\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate damagefontscalex\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::DAMAGE_FONT_SCALE_Y_COMMAND_ERROR: {
            chat->Write(0, false, "\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate damagefontscaley\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::SHOW_STARS_COMMAND_ERROR: {
            chat->Write(0, false, "\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate showstars\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::HIDE_STARS_COMMAND_ERROR: {
            chat->Write(0, false, "\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate hidestars\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::MODE_COMMAND_ERROR: {
            chat->Write(0, false, "\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate mode\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::FONT_SCALE_MODE_COMMAND_ERROR: {
            chat->Write(0, false, "\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate scalemode\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        default: {
            m_AshitaCore->GetChatManager()->Writef(0, false, "\x1e\x44Unknown message %u (%d)", (uint32_t) message, param);
        }
        break;
    }
}

DllExport double __stdcall expGetInterfaceVersion(void) {
    return ASHITA_INTERFACE_VERSION;
}

DllExport IPlugin* __stdcall expCreatePlugin([[maybe_unused]] const char* args) {
    return new AshitaNameplate();
}

DllExport void __stdcall expDestroyPlugin(void* instance) {
    delete reinterpret_cast<AshitaNameplate*>(instance);
}
