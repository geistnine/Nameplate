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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Windozer.h"

#include "../Nameplate.h"


class WindozerNameplate : public PluginBase, private Nameplate {
    public:
        virtual void __stdcall Load(PluginManager* _manager) override {
            pPluginManager = _manager;

            int ret = this->Init();

            if (ret < 0) {
                ShowMessage(MESSAGE::PLUGIN_LOAD_ERROR, ret);
            }
        }

        virtual void __stdcall Unload() override {
            int ret = this->Deinit();

            if (ret < 0) {
                ShowMessage(MESSAGE::PLUGIN_UNLOAD_ERROR, ret);
            }
        }

        virtual const char* __stdcall GetPluginAuthor() override {
            return "BunnyBox Productions";
        }

        virtual const char* __stdcall GetPluginName() override {
            return "nameplate";
        }

        virtual void __stdcall PluginCommand(const char* cmd) override;

        virtual void Debug(const char* text) override {
            pPluginManager->GetConsole()->Write(text);
        }

        virtual bool GetConfigPath(wchar_t path[UNICODE_MAX_PATH]) override {
            MMFSettingsHandler* settings = pPluginManager->GetMMFSettingsHandler();

            StringCchPrintfW(path, UNICODE_MAX_PATH, L"%S\\plugins\\settings", settings->WindowerPath);

            return true;
        }

        virtual void ShowMessage(MESSAGE message, int param) override;
};

void __stdcall WindozerNameplate::PluginCommand(const char* cmd) {
    ParseCommand(cmd, false);
}

void WindozerNameplate::ShowMessage(MESSAGE message, int param) {
    auto* console = pPluginManager->GetConsole();

    switch (message) {
        case MESSAGE::PLUGIN_LOAD_ERROR: {
            char buf[1000];
            StringCbPrintfA(buf, sizeof(buf), "\\cs(255,192,255)[Nameplate] \\cs(255,128,128)Plugin load failed with error code \\cs(255,128,128)%d\\cs(255,128,255)!\\cr", param);
            console->Write(buf);
        }
        break;

        case MESSAGE::PLUGIN_UNLOAD_ERROR: {
            char buf[1000];
            StringCbPrintfA(buf, sizeof(buf), "\\cs(255,192,255)[Nameplate] \\cs(255,128,128)Plugin unload failed with error code \\cs(255,128,128)%d\\cs(255,128,255)!\\cr", param);
            console->Write(buf);
        }
        break;

        case MESSAGE::SHORT_HELP: {
            console->Write("\\cs(255,192,255)[Nameplate] \\cs(255,128,128)Unknown command, please consult \\cs(255,255,192)//nameplate help \\cs(255,128,128) for more information.\\cr");
        }
        break;

        case MESSAGE::LONG_HELP: {
            console->Write("\\cs(255,192,255)Nameplate v0.60\\cr");
            console->Write("\\cs(255,192,255)https://www.github.com/Shirk/Nameplate\\cr");
            console->Write("\\cs(255,255,255)Please visit the Nameplate website\\cr");
            console->Write("\\cs(255,255,255)for the latest information on how to use the plugin\\cr");
            console->Write("\\cs(255,192,255)Use \\cs(255,255,192)//nameplate commands \\cs(255,128,128)to see the list of commands\\cr");
        }
        break;

        case MESSAGE::COMMAND_HELP: {
            console->Write("\\cs(255,255,192)//nameplate commands - \\cs(255,255,255)You're reading it!\\cr");
            console->Write("\\cs(255,255,192)//nameplate load - \\cs(255,255,255)Load configuration from\\cs(255,255,192) plugins/settings/nameplate/defaults.ini\\cr");
            console->Write("\\cs(255,255,192)//nameplate save - \\cs(255,255,255)Save current configuration to\\cs(255,255,192) plugins/settings/nameplate/defaults.ini\\cr");
            console->Write("\\cs(255,255,192)//nameplate fontsize - \\cs(255,225,192) <number>\t\\cs(255,255,255)Set the nameplate font size to <number> pixels\\cr");
            console->Write("\\cs(255,255,192)//nameplate damagefontsize - \\cs(255,225,192) <number>\t\\cs(255,255,255)Set the damage font size to <number> pixels\\cr");
            console->Write("\\cs(255,255,192)//nameplate fontscalex - \\cs(255,225,192) <number>\t\\cs(255,255,255)Set the nameplate font X-scale factor to <number>\\cr");
            console->Write("\\cs(255,255,192)//nameplate fontscaley - \\cs(255,225,192) <number>\t\\cs(255,255,255)Set the nameplate font Y-scale factor to <number>\\cr");
            console->Write("\\cs(255,255,192)//nameplate damagefontscalex - \\cs(255,225,192) <number>\t\\cs(255,255,255)Set the damage font X-scale factor to <number>\\cr");
            console->Write("\\cs(255,255,192)//nameplate damagefontscaley - \\cs(255,225,192) <number>\t\\cs(255,255,255)Set the damage font Y-scale factor to <number>\\cr");
            console->Write("\\cs(255,255,192)//nameplate hidestars - \\cs(255,255,255)Hide all Job Mastery stars\\cr");
            console->Write("\\cs(255,255,192)//nameplate showstars - \\cs(255,255,255)Re-enable displaying Job Mastery stars\\cr");
            console->Write("\\cs(255,255,192)//nameplate mode all - \\cs(255,255,255)Show all nameplates\\cr");
            console->Write("\\cs(255,255,192)//nameplate mode none - \\cs(255,255,255)Hide all nameplates\\cr");
            console->Write("\\cs(255,255,192)//nameplate mode hideself - \\cs(255,255,255)Hide your own nameplate\\cr");
            console->Write("\\cs(255,255,192)//nameplate mode hidepc - \\cs(255,255,255)Hide all player nameplates, except when charmed\\cr");
            console->Write("\\cs(255,255,192)//nameplate mode hidepcself - \\cs(255,255,255)Hide all player nameplates, except when charmed, but also keep yours always hidden\\cr");
            console->Write("\\cs(255,255,192)//nameplate mode hidenpc - \\cs(255,255,255)Hide all non-player nameplates\\cr");
            console->Write("\\cs(255,255,192)//nameplate mode hidenpcself - \\cs(255,255,255)Hide all non-player nameplates, but also keep yours always hidden\\cr");
            console->Write("\\cs(255,255,192)//nameplate scalemode pixel - \\cs(255,255,255)Use the original pixel-based scaling mode for the nameplate and damage fonts\\cr");
            console->Write("\\cs(255,255,192)//nameplate scalemode scale - \\cs(255,255,255)Use the X/Y scale factors for the nameplate and damage fonts\\cr");
        }
        break;

        case MESSAGE::CURRENT_SETTINGS: {
            char buf[1000];
            console->Write("\\cs(255,192,255)Nameplate v0.60\\cr");
            console->Write("\\cs(255,192,255)https://www.github.com/Shirk/Nameplate\\cr");
            if (Settings.GetScaleMode() == FONT_SCALE_MODE::PIXEL) {
                StringCbPrintfA(buf, sizeof(buf), "Font Size: \\cs(255,192,255)%.1f\\cs(255,128,128) px", Settings.GetFontSize());
                console->Write(buf);
                StringCbPrintfA(buf, sizeof(buf), "Damage Font Size: \\cs(255,192,255)%.1f\\cs(255,128,128) px", Settings.GetDamageFontSize());
                console->Write(buf);
            } else {
                StringCbPrintfA(buf, sizeof(buf), "Font Scale X: \\cs(255,192,255)%.2f\\cr", Settings.GetFontScaleX());
                console->Write(buf);
                StringCbPrintfA(buf, sizeof(buf), "Font Scale Y: \\cs(255,192,255)%.2f\\cr", Settings.GetFontScaleY());
                console->Write(buf);
                StringCbPrintfA(buf, sizeof(buf), "Damage Font Scale X: \\cs(255,192,255)%.2f\\cr", Settings.GetDamageScaleX());
                console->Write(buf);
                StringCbPrintfA(buf, sizeof(buf), "Damage Font Scale Y: \\cs(255,192,255)%.2f\\cr", Settings.GetDamageScaleY());
                console->Write(buf);
                StringCbPrintfA(buf, sizeof(buf), "Scale Mode: \\cs(255,192,255)%s\\cr", Settings.GetScaleMode() == FONT_SCALE_MODE::PIXEL ? "pixel" : "scale");
                console->Write(buf);
                StringCbPrintfA(buf, sizeof(buf), "Hide Stars: \\cs(255,192,255)%s\\cr", Settings.GetHideStars() ? "yes" : "no");
                console->Write(buf);
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
            StringCbPrintfA(buf, sizeof(buf), "Display Mode: \\cs(255,192,255)%s\\cr", mode);
            console->Write(buf);
        }
        break;

        case MESSAGE::LOAD_ERROR: {
            char buf[1000];
            StringCbPrintfA(buf, sizeof(buf), "\\cs(255,192,255)[Nameplate] \\cs(255,128,128)Loading \\cs(255,255,192)plugins\\settings\\nameplate\\defaults.ini \\cs(255,128,128)failed with error code \\cs(255,128,128)%d\\cs(255,128,255)!\\cr", param);
            console->Write(buf);
        }
        break;

        case MESSAGE::LOAD_COMMAND_ERROR: {
            console->Write("\\cs(255,192,255)[Nameplate] \\cs(255,255,192)//nameplate load \\cs(255,128,128)command error, please consult \\cs(255,255,192)//nameplate help \\cs(255,128,128) for more information.\\cr");
        }
        break;

        case MESSAGE::SAVE_ERROR: {
            char buf[1000];
            StringCbPrintfA(buf, sizeof(buf), "\\cs(255,192,255)[Nameplate] \\cs(255,128,128)Save \\cs(255,255,192)plugins\\settings\\nameplate\\defaults.ini \\cs(255,128,128)failed with error code \\cs(255,128,128)%d\\cs(255,128,255)!\\cr", param);
            console->Write(buf);
        }
        break;

        case MESSAGE::SAVE_COMMAND_ERROR: {
            console->Write("\\cs(255,192,255)[Nameplate] \\cs(255,255,192)//nameplate save \\cs(255,128,128)command error, please consult \\cs(255,255,192)//nameplate help \\cs(255,128,128) for more information.\\cr");
        }
        break;

        case MESSAGE::FONT_SIZE_COMMAND_ERROR: {
            console->Write("\\cs(255,192,255)[Nameplate] \\cs(255,255,192)//nameplate fontsize \\cs(255,128,128)command error, please consult \\cs(255,255,192)//nameplate help \\cs(255,128,128) for more information.\\cr");
        }
        break;

        case MESSAGE::DAMAGE_FONT_SIZE_COMMAND_ERROR: {
            console->Write("\\cs(255,192,255)[Nameplate] \\cs(255,255,192)//nameplate damagefontsize \\cs(255,128,128)command error, please consult \\cs(255,255,192)//nameplate help \\cs(255,128,128) for more information.\\cr");
        }
        break;

        case MESSAGE::FONT_SCALE_X_COMMAND_ERROR: {
            console->Write("\\cs(255,192,255)[Nameplate] \\cs(255,255,192)//nameplate fontscalex \\cs(255,128,128)command error, please consult \\cs(255,255,192)//nameplate help \\cs(255,128,128) for more information.\\cr");
        }
        break;

        case MESSAGE::FONT_SCALE_Y_COMMAND_ERROR: {
            console->Write("\\cs(255,192,255)[Nameplate] \\cs(255,255,192)//nameplate fontscaley \\cs(255,128,128)command error, please consult \\cs(255,255,192)//nameplate help \\cs(255,128,128) for more information.\\cr");
        }
        break;

        case MESSAGE::DAMAGE_FONT_SCALE_X_COMMAND_ERROR: {
            console->Write("\\cs(255,192,255)[Nameplate] \\cs(255,255,192)//nameplate damagefontscalex \\cs(255,128,128)command error, please consult \\cs(255,255,192)//nameplate help \\cs(255,128,128) for more information.\\cr");
        }
        break;

        case MESSAGE::DAMAGE_FONT_SCALE_Y_COMMAND_ERROR: {
            console->Write("\\cs(255,192,255)[Nameplate] \\cs(255,255,192)//nameplate damagefontscaley \\cs(255,128,128)command error, please consult \\cs(255,255,192)//nameplate help \\cs(255,128,128) for more information.\\cr");
        }
        break;

        case MESSAGE::SHOW_STARS_COMMAND_ERROR: {
            console->Write("\\cs(255,192,255)[Nameplate] \\cs(255,255,192)//nameplate showstars \\cs(255,128,128)command error, please consult \\cs(255,255,192)//nameplate help \\cs(255,128,128) for more information.\\cr");
        }
        break;

        case MESSAGE::HIDE_STARS_COMMAND_ERROR: {
            console->Write("\\cs(255,192,255)[Nameplate] \\cs(255,255,192)//nameplate hidestars \\cs(255,128,128)command error, please consult \\cs(255,255,192)//nameplate help \\cs(255,128,128) for more information.\\cr");
        }
        break;

        case MESSAGE::MODE_COMMAND_ERROR: {
            console->Write("\\cs(255,192,255)[Nameplate] \\cs(255,255,192)//nameplate mode \\cs(255,128,128)command error, please consult \\cs(255,255,192)//nameplate help \\cs(255,128,128) for more information.\\cr");
        }
        break;

        case MESSAGE::FONT_SCALE_MODE_COMMAND_ERROR: {
            console->Write("\\cs(255,192,255)[Nameplate] \\cs(255,255,192)//nameplate scalemode \\cs(255,128,128)command error, please consult \\cs(255,255,192)//nameplate help \\cs(255,128,128) for more information.\\cr");
        }
        break;

        default: {
            char buf[1000];
            StringCbPrintfA(buf, sizeof(buf), "\\cs(255,192,255)[Nameplate] \\cs(255,255,192)Unknown message %u (%d)\\cr", (uint32_t) message, param);
            console->Write(buf);
        }
        break;
    }
}

uint32_t GetInterfaceVersion() {
    return WINDOZER_INTERFACE_VERSION;
}

PluginBase* CreateInstance() {
    return new WindozerNameplate();
}
