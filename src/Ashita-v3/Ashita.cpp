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

#include "ADK/Ashita.h"

#include "../Nameplate.h"

#include "exports.h"


#define LogLevel_Info ((uint32_t) Ashita::LogLevel::Info)
#define LogLevel_Critcal ((uint32_t) Ashita::LogLevel::Error)


class AshitaV3Nameplate : public IPlugin, private Nameplate {
private:
    IAshitaCore* m_AshitaCore;
    ILogManager* m_LogManager;
    uint32_t m_PluginId;

public:
	AshitaV3Nameplate();

    plugininfo_t GetPluginInfo(void) override {
        return plugininfo_t("Nameplate", "BunnyBox Productions", ASHITA_INTERFACE_VERSION, 0.60, 0);
    }

    virtual bool Initialize(IAshitaCore* core, ILogManager* log, uint32_t id) override;
    virtual void Release(void) override;

    virtual void Debug(const char* text) override {
        m_AshitaCore->GetChatManager()->Write(text);
    }

    virtual bool GetConfigPath(wchar_t path[UNICODE_MAX_PATH]) override {
        const char* installPath = m_AshitaCore->GetAshitaInstallPathA();

        StringCchPrintfW(path, UNICODE_MAX_PATH, L"%S\\config", installPath);
        return true;
    }

    bool HandleCommand(const char* command, int32_t type) override;

    virtual void ShowMessage(MESSAGE message, int param) override;
};

AshitaV3Nameplate::AshitaV3Nameplate() : m_AshitaCore(nullptr), m_LogManager(nullptr), m_PluginId(0) {
}

bool AshitaV3Nameplate::Initialize(IAshitaCore* core, ILogManager* log, uint32_t id) {
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

void AshitaV3Nameplate::Release(void) {

    int ret = this->Deinit();
    if (ret < 0) {
        m_LogManager->Logf(LogLevel_Critcal, "Nameplate", "Plugin Unload Error: \"%d\"", ret);
        ShowMessage(MESSAGE::PLUGIN_UNLOAD_ERROR, ret);
    }

    IPlugin::Release();
}

bool AshitaV3Nameplate::HandleCommand(const char* command, [[maybe_unused]] int32_t type) {
    return ParseCommand(command, true);
}

void AshitaV3Nameplate::ShowMessage(MESSAGE message, int param) {
    auto* chat = m_AshitaCore->GetChatManager();

    switch (message) {
        case MESSAGE::PLUGIN_LOAD_ERROR: {
            chat->Writef("\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x44Plugin load failed with error code \x1e\x05%d\x1e\x44!", param);
        }
        break;

        case MESSAGE::PLUGIN_UNLOAD_ERROR: {
            chat->Writef("\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x44Plugin unload failed with error code \x1e\x05%d\x1e\x44!", param);
        }
        break;

        case MESSAGE::SHORT_HELP: {
            chat->Write("\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x44Unknown command, please consult \x1e\x6a/nameplate help\x1e\x44 for more information.");
        }
        break;

        case MESSAGE::LONG_HELP: {
            chat->Write("\x1e\x05Nameplate v0.60");
            chat->Write("\x1e\x05https://www.github.com/Shirk/Nameplate");
            chat->Write("Please visit the Nameplate website");
            chat->Write("for the latest information on how to use the plugin");
            chat->Write("\x1e\x05Use \x1e\x6a/nameplate commands\x1e\x44 to see the list of commands");
        }
        break;

        case MESSAGE::COMMAND_HELP: {
            chat->Write("\x1e\x6a/nameplate commands");
            chat->Write("You're reading it!");
            chat->Write("\x1e\x6a/nameplate load");
            chat->Write("Load configuration from\x1e\x6a config\\nameplate\\defaults.ini");
            chat->Write("\x1e\x6a/nameplate save");
            chat->Write("Save current configuration to\x1e\x6a config\\nameplate\\defaults.ini");
            chat->Write("\x1e\x6a/nameplate fontsize\x1e\x6a <number>");
            chat->Write("Set the nameplate font size to <number> pixels");
            chat->Write("\x1e\x6a/nameplate damagefontsize\x1e\x6a <number>");
            chat->Write("Set the damage font size to <number> pixels");
            chat->Write("\x1e\x6a/nameplate fontscalex\x1e\x6a <number>");
            chat->Write("Set the nameplate font X-scale factor to <number>");
            chat->Write("\x1e\x6a/nameplate fontscaley\x1e\x6a <number>");
            chat->Write("Set the nameplate font Y-scale factor to <number>");
            chat->Write("\x1e\x6a/nameplate damagefontscalex\x1e\x6a <number>");
            chat->Write("Set the damage font X-scale factor to <number>");
            chat->Write("\x1e\x6a/nameplate damagefontscaley\x1e\x6a <number>");
            chat->Write("Set the damage font Y-scale factor to <number>");
            chat->Write("\x1e\x6a/nameplate hidestars");
            chat->Write("Hide all Job Mastery stars");
            chat->Write("\x1e\x6a/nameplate showstars");
            chat->Write("Re-enable displaying Job Mastery stars");
            chat->Write("\x1e\x6a/nameplate mode all");
            chat->Write("Show all nameplates");
            chat->Write("\x1e\x6a/nameplate mode none");
            chat->Write("Hide all nameplates");
            chat->Write("\x1e\x6a/nameplate mode hideself");
            chat->Write("Hide your own nameplate");
            chat->Write("\x1e\x6a/nameplate mode hidepc");
            chat->Write("Hide all player nameplates, except when charmed");
            chat->Write("\x1e\x6a/nameplate mode hidepcself");
            chat->Write("Hide all player nameplates, except when charmed, but also keep yours always hidden");
            chat->Write("\x1e\x6a/nameplate mode hidenpc");
            chat->Write("Hide all non-player nameplates");
            chat->Write("\x1e\x6a/nameplate mode hidenpcself");
            chat->Write("Hide all non-player nameplates, but also keep yours always hidden");
            chat->Write("\x1e\x6a/nameplate scalemode pixel");
            chat->Write("Use the original pixel-based scaling mode for the nameplate and damage fonts");
            chat->Write("\x1e\x6a/nameplate scalemode scale");
            chat->Write("Use the X/Y scale factors for the nameplate and damage fonts");
        }
        break;

        case MESSAGE::CURRENT_SETTINGS: {
            chat->Write("\x1e\x05Nameplate v0.60");
            chat->Write("\x1e\x05https://www.github.com/Shirk/Nameplate");
            if (Settings.GetScaleMode() == FONT_SCALE_MODE::PIXEL) {
                chat->Writef("Font Size: \x1e\x05%.1f\x1e\x44 px", Settings.GetFontSize());
                chat->Writef("Damage Font Size: \x1e\x05%.1f\x1e\x44 px", Settings.GetDamageFontSize());
            } else {
                chat->Writef("Font Scale X: \x1e\x05%.2f", Settings.GetFontScaleX());
                chat->Writef("Font Scale Y: \x1e\x05%.2f", Settings.GetFontScaleY());
                chat->Writef("Damage Font Scale X: \x1e\x05%.2f", Settings.GetDamageScaleX());
                chat->Writef("Damage Font Scale Y: \x1e\x05%.2f", Settings.GetDamageScaleY());
                chat->Writef("Scale Mode: \x1e\x05%s", Settings.GetScaleMode() == FONT_SCALE_MODE::PIXEL ? "pixel" : "scale");
                chat->Writef("Hide Stars: \x1e\x05%s", Settings.GetHideStars() ? "yes" : "no");
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
            chat->Writef("Display Mode: \x1e\x05%s", mode);
        }
        break;

        case MESSAGE::LOAD_ERROR: {
            chat->Writef("\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x44Loading\x1e\x6a config\\nameplate\\defaults.ini\x1e\x44 failed with error code \x1e\x05%d\x1e\x44!", param);
        }
        break;

        case MESSAGE::LOAD_COMMAND_ERROR: {
            chat->Write("\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate load\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::SAVE_ERROR: {
            chat->Writef("\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x44Saving\x1e\x6a config\\nameplate\\defaults.ini\x1e\x44 failed with error code \x1e\x05%d\x1e\x44!", param);
        }
        break;

        case MESSAGE::SAVE_COMMAND_ERROR: {
            chat->Write("\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate save\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::FONT_SIZE_COMMAND_ERROR: {
            chat->Write("\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate fontsize\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::DAMAGE_FONT_SIZE_COMMAND_ERROR: {
            chat->Write("\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate damagefontsize\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::FONT_SCALE_X_COMMAND_ERROR: {
            chat->Write("\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate fontscalex\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::FONT_SCALE_Y_COMMAND_ERROR: {
            chat->Write("\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate fontscaley\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::DAMAGE_FONT_SCALE_X_COMMAND_ERROR: {
            chat->Write("\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate damagefontscalex\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::DAMAGE_FONT_SCALE_Y_COMMAND_ERROR: {
            chat->Write("\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate damagefontscaley\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::SHOW_STARS_COMMAND_ERROR: {
            chat->Write("\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate showstars\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::HIDE_STARS_COMMAND_ERROR: {
            chat->Write("\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate hidestars\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::MODE_COMMAND_ERROR: {
            chat->Write("\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate mode\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        case MESSAGE::FONT_SCALE_MODE_COMMAND_ERROR: {
            chat->Write("\x1e\x51[\x1e\x06Nameplate\x1e\x51]\x1e\x01 \x1e\x6a/nameplate scalemode\x1e\x44 command error, please consult \x1e\x6a/nameplate help\x1e\x44 for correct usage.");
        }
        break;

        default: {
            chat->Writef("\x1e\x44Unknown message %u (%d)", (uint32_t) message, param);
        }
        break;
    }
}

DllExport double __stdcall GetInterfaceVersion(void) {
    return ASHITA_INTERFACE_VERSION;
}

DllExport void __stdcall CreatePluginInfo(plugininfo_t* info) {
    *info = plugininfo_t{
        "Nameplate",
        "BunnyBox Productions",
        ASHITA_INTERFACE_VERSION,
        0.60,
        0
    };
}

DllExport IPlugin* __stdcall CreatePlugin(void) {
    return new AshitaV3Nameplate();
}
