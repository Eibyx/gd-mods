# Geometry Dash 2.2091 Mods

## Geode 6.0.0 stable · Android64 (arm64-v8a)

Built by [`geode6-android64.yml`](.github/workflows/geode6-android64.yml) and [`guccibot-geode6-android64.yml`](.github/workflows/guccibot-geode6-android64.yml) against Geode `v6.0.0` and pinned `geode-sdk/bindings@94cead78`. One independent `.geode` per mod, arm64-v8a only.

| Mod | Mod ID | Release |
|-----|--------|---------|
| QOLMod v3.0.0 | `thesillydoggo.qolmod` | [qolmod-v3.0.0-geode6.0.0-android64](https://github.com/Eibyx/gd-mods/releases/tag/qolmod-v3.0.0-geode6.0.0-android64) |
| FFmpeg API v2.1.1 | `eclipse.ffmpeg-api` | [ffmpeg-api-v2.1.1-geode6.0.0-android64](https://github.com/Eibyx/gd-mods/releases/tag/ffmpeg-api-v2.1.1-geode6.0.0-android64) |
| xdBot v2.6.12 (needs FFmpeg API) | `zilko.xdbot` | [xdbot-v2.6.12-geode6.0.0-android64](https://github.com/Eibyx/gd-mods/releases/tag/xdbot-v2.6.12-geode6.0.0-android64) |
| GucciBot v2.0.0 (experimental) | `nigelx1.guccibot` | [guccibot-v2.0.0-geode6.0.0-android64](https://github.com/Eibyx/gd-mods/releases/tag/guccibot-v2.0.0-geode6.0.0-android64) |

These compile; none has been tested on a device yet. What changed, what is disabled on Android and what still has to be checked: [COMPATIBILITY.md](COMPATIBILITY.md).

Publishing: push a `geode6-*` tag (QOLMod, FFmpeg API, xdBot) or a `guccibot-geode6-*` tag (GucciBot), or run the workflow by hand with "publish" ticked.

## Earlier alpha/beta ports (Exodi-dio)

Mods ported to **Geode 6.0.0-alpha.3** for **GD 2.2091**, with xdBot and Jukebox on **Geode 6.0.0-beta.1**.

I'm too tired of waiting for the geode devs 💔

## Releases

Every `.geode` is a combined Android32 + Android64 build, except Jukebox which also ships a Windows build. Install with Geode.

| Mod | Mod ID | Release |
|-----|--------|---------|
| Jukebox | `fleym.nongd` | [v2.6](https://github.com/Exodi-dio/gd-mods/releases/tag/jukebox-v2.6-crossplatform) |
| GDH | `tobyadd.gdh` | [v4.5](https://github.com/Exodi-dio/gd-mods/releases/tag/gdh-v4.5-android) |
| QOLMod | `thesillydoggo.qolmod` | [v3.0.0](https://github.com/Exodi-dio/gd-mods/releases/tag/qolmod-v3.0.0-android) |
| xdBot | `zilko.xdbot` | [v2.6.12](https://github.com/Exodi-dio/gd-mods/releases/tag/xdbot-v2.6.12-android) |
| FFmpeg API | `eclipse.ffmpeg-api` | [v2.1.1](https://github.com/Exodi-dio/gd-mods/releases/tag/ffmpeg-api-v2.1.1-android) |
| Node IDs | `geode.node-ids` | [v1.23.5](https://github.com/Exodi-dio/gd-mods/releases/tag/node-ids-v1.23.5-android) |
| Icon Gradients | `zilko.icon_gradients` | [v1.3.15](https://github.com/Exodi-dio/gd-mods/releases/tag/icon-gradients-v1.3.15-android) |
| Death Animations | `zilko.death_animations` | [v1.1.7](https://github.com/Exodi-dio/gd-mods/releases/tag/death-animations-v1.1.7-android) |


## Notes

- **Level Thumbnails** is not included: its Argon dependency is incompatible with Geode 6.
- **Death Animations** does not include More Icons support: the latest More Icons release is incompatible with Geode 6.
- **QOLMod** is an Android-only port of the v3 source. The music pitch and pitch shifter features are disabled because the FMOD engine cannot be reached on Android.
- xdBot is a botting tool and GDH is a cheat menu. Use them at your own risk in online levels.
