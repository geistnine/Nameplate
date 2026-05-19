# Nameplate

## Current Status

***Abandoned***. Good luck! Take care.

## Description

Nameplate was a plugin for [Ashita v4](https://github.com/AshitaXI/Ashita-v4beta), [Ashita v3](https://ashitaxi.com/), and [Windower 4](https://www.windower.net/) that corrects XI's nameplate aspect ratio.

With this plugin, nameplates will be less blurry and the same size regardless of window size: no more stretched nameplates or having to download hacked DAT files.

## Installation for Ashita v4 users

Download the version of the Ashita v4 plugin that matches the interface version of your version of Ashita v4.

Copy `plugins\Nameplate.dll` to `<***Ashita v4 Folder***>\plugins\Nameplate.dll`.

## Usage for Ashita v4 users

`/load Nameplate` to load the plugin.  `/nameplate help` to read the
in-game command help.

- The font size can be configured via the `FontSizeInPx` setting in
`config\nameplate\defaults.ini`.
- The damage font size can be configured via the `DamageFontSizeInPx` setting in
`config\nameplate\defaults.ini`.
- The font X-scale and Y-scale factors can be configured via the `FontScaleX` and `FontScaleY` settings in `config\nameplate\defaults.ini`.
- The damage font X-scale and Y-scale factors can be configured via the `DamageFontScaleX` and `DamageFontScaleY` settings in `config\nameplate\defaults.ini`.
- Job Mastery stars can be hidden by setting `HideStars=1` in the configuration.
- The font scaling mode can be changed via the `FontScaleMode` setting.
- Nameplate visibility modes can be changed via the `NameMode` setting.

The configuration file is ***not*** autosaved when changing these settings in-game. The configuration
file can be saved and loaded by using the `/nameplate save` and `/nameplate load` commands.

| command                                | description                                                                        |
|----------------------------------------|------------------------------------------------------------------------------------|
| /nameplate help                        | You're reading it!                                                                 |
| /nameplate load                        | Load configuration from `config\nameplate\defaults.ini`                            |
| /nameplate save                        | Save current configuration to `config\nameplate\defaults.ini`                      |
| /nameplate fontsize `<number>`         | Set the nameplate font size to `<number>` pixels                                   |
| /nameplate damagefontsize `<number>`   | Set the damage font size to `<number>` pixels                                      |
| /nameplate fontscalex `<number>`       | Set the nameplate font X-scale factor to `<number>` (e.g. 1.2)                     |
| /nameplate fontscaley `<number>`       | Set the nameplate font Y-scale factor to `<number>` (e.g. 1.2)                     |
| /nameplate damagefontscalex `<number>` | Set the damage font X-scale factor to `<number>` (e.g. 1.2)                        |
| /nameplate damagefontscaley `<number>` | Set the damage font Y-scale factor to `<number>` (e.g. 1.2)                        |
| /nameplate hidestars                   | Hide all Job Mastery stars                                                         |
| /nameplate showstars                   | Re-enable displaying Job Mastery stars                                             |
| /nameplate scalemode pixel             | Sets the nameplate and damage font scaling to use pixel size                       |
| /nameplate scalemode scale             | Sets the nameplate and damage font scaling to use scale factors                    |
| /nameplate mode all                    | Show all nameplates                                                                |
| /nameplate mode none                   | Hide all nameplates                                                                |
| /nameplate mode hideself               | Hide your own nameplate                                                            |
| /nameplate mode hidepc                 | Hide all player nameplates, except when charmed                                    |
| /nameplate mode hidepcself             | Hide all player nameplates, except when charmed, but also always keep yours hidden |
| /nameplate mode hidenpc                | Hide all non-player nameplates                                                     |
| /nameplate mode hidenpcself            | Hide all non-player nameplates, but also always keep yours hidden                  |

## Installation for Ashita v3 users

Download Nameplate for Ashita v3, and copy `plugins\Nameplate.dll` to `<***Ashita v3 Folder***>\plugins\Nameplate.dll`

## Usage for Ashita v3 users

Please consult the [Usage for Ashita v4 users](#usage-for-ashita-v4-users) section for details.

## Installation for Windower 4 users

***Please report any and all issues with this plugin on the [Nameplate Issues](https://github.com/Shirk/Nameplate/issues/) tracker. This is the *only* valid location to get any support or assistance for this plugin. If you would like to see this plugin officially bundled with Windower 4, please petition the Windower developers to reach out to the Nameplate project.***

Download Nameplate for Ashita v4, and copy `plugins\Nameplate.dll` to `<***Windower 4 Folder***>\plugins\Nameplate.dll`

The Ashita v4 version of Nameplate is compatible with the current version of Windower 4. If trying to load this plugin results in "plugin is out of date" errors, then you may need to download a different version of the plugin.

## Usage for Windower 4 users

***Please report any and all issues with this plugin on the [Nameplate Issues](https://github.com/Shirk/Nameplate/issues/) tracker. This is the *only* valid location to get any support or assistance for this plugin. If you would like to see this plugin officially bundled with Windower 4, please petition the Windower developers to reach out to the Nameplate project.***

`//load Nameplate` to load the plugin.  `//nameplate help` to read the
in-game command help.

Besides using the in-game commands to control nameplate, the settings can be edited directly in its configuration file.

- The font pixel size can be configured via the `FontSizeInPx` setting in
`plugins\settings\nameplate\defaults.ini`.
- The damage pixel font size can be configured via the `DamageFontSizeInPx` setting in
`plugins\settings\nameplate\defaults.ini`.
- The font X-scale and Y-scale factors can be configured via the `FontScaleX` and `FontScaleY` settings in `plugins\settings\nameplate\defaults.ini`.
- The damage font X-scale and Y-scale factors can be configured via the `DamageFontScaleX` and `DamageFontScaleY` settings in `plugins\settings\nameplate\defaults.ini`.
- Job Mastery stars can be hidden by setting `HideStars=1` in the configuration.
- The font scaling mode can be changed via the `FontScaleMode` setting.
- Nameplate visibility modes can be changed via the `NameMode` setting.

The configuration file is ***not*** autosaved when changing these settings in-game. The configuration
file can be saved and loaded by using the `//nameplate save` and `//nameplate load` commands.

| command                                 | description                                                                        |
|-----------------------------------------|------------------------------------------------------------------------------------|
| //nameplate help                        | You're reading it!                                                                 |
| //nameplate load                        | Load configuration from `plugins\settings\nameplate\defaults.ini`                  |
| //nameplate save                        | Save current configuration to `plugins\settings\nameplate\defaults.ini`            |
| //nameplate fontsize `<number>`         | Set the nameplate font size to `<number>` pixels                                   |
| //nameplate damagefontsize `<number>`   | Set the damage font size to `<number>` pixels                                      |
| //nameplate fontscalex `<number>`       | Set the nameplate font X-scale factor to `<number>` (e.g. 1.2)                     |
| //nameplate fontscaley `<number>`       | Set the nameplate font Y-scale factor to `<number>` (e.g. 1.2)                     |
| //nameplate damagefontscalex `<number>` | Set the damage font X-scale factor to `<number>` (e.g. 1.2)                        |
| //nameplate damagefontscaley `<number>` | Set the damage font Y-scale factor to `<number>` (e.g. 1.2)                        |
| //nameplate hidestars                   | Hide all Job Mastery stars                                                         |
| //nameplate showstars                   | Re-enable displaying Job Mastery stars                                             |
| //nameplate scalemode pixel             | Sets the nameplate and damage font scaling to use pixel size                       |
| //nameplate scalemode scale             | Sets the nameplate and damage font scaling to use scale factors                    |
| //nameplate mode all                    | Show all nameplates                                                                |
| //nameplate mode none                   | Hide all nameplates                                                                |
| //nameplate mode hideself               | Hide your own nameplate                                                            |
| //nameplate mode hidepc                 | Hide all player nameplates, except when charmed                                    |
| //nameplate mode hidepcself             | Hide all player nameplates, except when charmed, but also always keep yours hidden |
| //nameplate mode hidenpc                | Hide all non-player nameplates                                                     |
| //nameplate mode hidenpcself            | Hide all non-player nameplates, but also always keep yours hidden                  |

## For more information

- [Nameplate Homepage](https://github.com/Shirk/Nameplate)
- [Issues Tracker](https://github.com/Shirk/Nameplate/issues)
- [Original Homepage](https://ffxi.somepage.org/Nameplate/)
- [Changelog](./CHANGELOG.md)

## License

Nameplate is available under the [GNU GENERAL PUBLIC LICENSE, Version 3](https://www.gnu.org/licenses/gpl-3.0.en.html) license. Please consult [LICENSE](./LICENSE.md) for more information.

## Legal

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.
