# Compatibilidad: Geode 6.0.0 · GD 2.2091 · Android64

Objetivo: Geometry Dash 2.2091 con el loader Geode **6.0.0 estable**, Android 16 y arm64-v8a. Dispositivo de referencia: Poco X7 Pro.

Este documento distingue dos niveles:

- **Compila:** GitHub Actions construyó el `.geode` sin errores. Además, el paquete se revisó automáticamente: `.so` ELF aarch64, `mod.json` con `geode: 6.0.0` y `gd.android: 2.2091`, y segmentos LOAD alineados a 16 KB.
- **Funciona en el dispositivo:** se probó en un teléfono real. **Nada de esta tabla se ha probado todavía en un dispositivo.** Ni en el Poco X7 Pro ni en otro.

| Mod | ID | Versión | Compila | Probado en dispositivo |
|-----|----|---------|---------|------------------------|
| QOLMod | `thesillydoggo.qolmod` | v3.0.0 | Sí | No |
| FFmpeg API | `eclipse.ffmpeg-api` | v2.1.1 | Sí | No |
| xdBot | `zilko.xdbot` | v2.6.12 | Sí | No |
| GucciBot | `nigelx1.guccibot` | v2.0.0 | Sí (experimental) | No |

## Entorno de compilación (fijado)

| Pieza | Valor |
|-------|-------|
| Geode SDK | `v6.0.0` (tag) |
| Bindings | `geode-sdk/bindings@94cead78` (main justo después de publicarse 6.0.0) |
| NDK | r29 (`29.0.14206865`), API mínima 23 (FFmpeg API: 24) |
| Acción | `geode-sdk/build-geode-mod@dce36b3` |
| Arquitectura | solo `arm64-v8a` (Android64). No se compila Android32 ni otras plataformas. |

Por qué se fijaron los bindings: `main` cambia varias veces al día. El 2026-11-24 corrigió el orden de funciones virtuales de varias clases (EditorUI y otras) y el layout de `PlayerObject`. Un mod construido contra unos bindings anteriores puede compilar y aun así cerrarse o leer datos erróneos en tiempo de ejecución.

## Cambios de código necesarios

### Todos los mods: miembros de `PlayerObject` que no existen en 2.2091

`m_stateNoStickX`, `m_stateNoStickY` y `m_stateUnk2` se quitaron de los bindings (commit `ec526620`, "impostor members") porque no existen en GD 2.2091. QOLMod (Checkpoint Fix), xdBot (Practice Fix) y GucciBot (checkpoints) los guardaban y restauraban. Ya no los tocan.

Esto también corrige un fallo latente de los ports alpha/beta anteriores: con los bindings viejos, esos campos y `m_stateBoostX`/`m_stateBoostY` caían en offsets equivocados.

### FFmpeg API

- Las librerías estáticas de FFmpeg 8 (aom, vpx, x264, x265) se compilan en CI con `ffmpeg-android-maker` y se guardan en caché.
- libvpx se descarga del mirror de GitHub (`webmproject/libvpx`), porque los tarballs de googlesource fallan desde los runners.
- El build de FFmpeg usa CMake 3.31, porque x265 no configura con CMake 4.
- El mod es **solo Android**, por diseño del port original.

### xdBot

- Depende de `eclipse.ffmpeg-api >= v2.0.0`. Al compilar, la CLI descarga del índice de Geode la versión 2.0.0 de FFmpeg API, solo para tener sus cabeceras.
- **En el teléfono hay que instalar el FFmpeg API de estas Releases**, porque la del índice es para Geode 5.

### GucciBot

El build de Geode 6 de upstream es solo para Windows. Lo que se cambió (ver `guccibot/patches/`):

1. **Android64 habilitado** para Geode 6. Usa el motor "portable" (`GB_NATIVE_ENGINE 0`), el mismo que el build de Windows en Geode 6.
2. **Bindings 94cead78.** Los bindings nuevos convierten los alias `renamed_from` en `__declspec(property)`, y GucciBot usa nombres antiguos dentro de `offsetof`, `sizeof` y lecturas `const`, que las propiedades no admiten. El parche de codegen genera otra vez `union` para alias de escalares y punteros. El layout es idéntico y los demás tipos mantienen los alias de upstream. Sustituye al parche `bindings-g6-copyable-renames.patch` de upstream.
3. **Parche de escala de ImGui para móvil**, rehecho para `gd-imgui-cocos@934958c`.
4. **Paquete Android** con `gd.android = 2.2091`, y sin las DLL/dylib de FFmpeg de escritorio, que en Android nunca se cargan.

## Funciones desactivadas o incompatibles en Android

| Mod | Función | Estado | Motivo |
|-----|---------|--------|--------|
| QOLMod | Music Pitch / Pitch Shifter | Según el port de Exodi, no funciona | No se puede acceder al motor FMOD de esa forma en Android (heredado del port original, sin verificar). |
| GucciBot | Renderizado de vídeo (Render) | **No disponible** | `src/render/ffmpeg.hpp` solo carga FFmpeg en Windows y macOS. Integrarlo con `eclipse.ffmpeg-api` sería trabajo nuevo. |
| GucciBot | Mantener el toque pulsado al reiniciar con tecla (R) | **Desactivado** | `UILayer::handleKeypress` es inline en los bindings de 2.2091 y no se puede enganchar. Solo afecta a teclados físicos. |
| GucciBot | Pathfinder, TPS < 162, cambios de TPS dentro de una macro, High TPS precision | No disponibles | Limitación de upstream en 2.2091 (anunciada para 2.0.1). No es algo de Android. |
| GucciBot | "World" (motor de triggers del modo nativo) | Apagado | Igual que en macOS y Android con Geode 5: solo hay motor portable. |
| GucciBot | Assistant Access (servidor MCP) | Sin verificar | Usa sockets BSD fuera de Windows. |
| Todos | Android32, Windows, macOS, iOS | No compilados | Fuera del alcance pedido (arm64-v8a). |

## Qué falta comprobar en el Poco X7 Pro

1. Geode 6.0.0 instalado con el launcher de Android y GD 2.2091 arrancando sin mods.
2. Instalar los mods de uno en uno, en este orden: FFmpeg API, QOLMod, xdBot y GucciBot. Tras cada uno, abrir el juego y entrar a un nivel.
3. QOLMod: abrir el menú con el botón en pantalla, usar Checkpoint Fix en práctica y probar el speedhack.
4. xdBot: grabar y reproducir una macro, y renderizar un vídeo corto. Esto último prueba FFmpeg API de punta a punta.
5. GucciBot: abrir el menú desde el botón de pausa, revisar la escala de la interfaz y grabar y reproducir una macro.
6. Si algo se cierra, recoger `geode/logs/` y el crash log del launcher.

Hasta completar esa lista, el estado real es **"compila, sin probar en dispositivo"**.
