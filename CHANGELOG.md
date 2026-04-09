# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).


## [2.1.0](https://github.com/Starlord-8bit/clockwise/compare/v2.0.0...v2.1.0) (2026-04-09)


### Features

* add GBR LED colour order and reverse phase options ([d37dead](https://github.com/Starlord-8bit/clockwise/commit/d37dead1a1417a264dbf889cb2bd7571af8d4f0f))
* clockface index persistence + auto-reboot on change, URL-decode fix on boot ([80ea54c](https://github.com/Starlord-8bit/clockwise/commit/80ea54cda2eb63afd9ee0b419352fd8d7d884585))
* Clockwise Paradise v2.0.0 ([7cafe6d](https://github.com/Starlord-8bit/clockwise/commit/7cafe6db4e94e7e8e470fcdd460507c28b890d95))
* config backup and restore (closes [#6](https://github.com/Starlord-8bit/clockwise/issues/6)) ([8bdd952](https://github.com/Starlord-8bit/clockwise/commit/8bdd952a46fbe1065f58cfa1a09dcfd92c4becd8))
* enable runtime clockface dispatcher (CW_DISPATCHER_ENABLED=1) ([76e9cff](https://github.com/Starlord-8bit/clockwise/commit/76e9cff9193c645d27d9d0e0cce0a3f2229ee7b0))
* MQTT support + Canvas editor link (closes [#1](https://github.com/Starlord-8bit/clockwise/issues/1), [#3](https://github.com/Starlord-8bit/clockwise/issues/3)) ([a905b3d](https://github.com/Starlord-8bit/clockwise/commit/a905b3dbd5d0a34681b029d491a1a828b3174537))
* multi-page WebUI (Tasmota/WLED-style navigation) ([0dfb9a0](https://github.com/Starlord-8bit/clockwise/commit/0dfb9a0c89b00ba6f57dcc8336ba6c1f5fb5c404))
* OTA binary upload via POST /ota/upload + web UI button ([d70a46a](https://github.com/Starlord-8bit/clockwise/commit/d70a46a5edcc44779778ae9e17a91e21157c6911))
* OTA firmware updates from GitHub releases (closes [#5](https://github.com/Starlord-8bit/clockwise/issues/5)) ([9bf94f2](https://github.com/Starlord-8bit/clockwise/commit/9bf94f24ecc02a44918331a7b8f7aabad3a4242e))
* **ota:** automatic rollback guard — device cannot be bricked by OTA ([9ddc1ae](https://github.com/Starlord-8bit/clockwise/commit/9ddc1ae557ff8a44ccd3058c97fe12dc19dc652d))
* **ota:** automatic rollback guard — device cannot be bricked by OTA ([9ddc1ae](https://github.com/Starlord-8bit/clockwise/commit/9ddc1ae557ff8a44ccd3058c97fe12dc19dc652d))
* **ota:** automatic rollback guard — device cannot be bricked by OTA ([288acb5](https://github.com/Starlord-8bit/clockwise/commit/288acb590a91df4988618500a0b57ed6a3c3c32f))
* rewrite MQTT with HA Discovery protocol ([9f6483f](https://github.com/Starlord-8bit/clockwise/commit/9f6483f62a50229a23483814a712ea33d091f074))
* runtime clockface dispatcher scaffolding (CW_DISPATCHER_ENABLED) ([1e50f99](https://github.com/Starlord-8bit/clockwise/commit/1e50f997c3122cf4c05b72d2cef1d829d9052d02))
* v1 web UI redesign — structured menu and grouped pages ([8264d9c](https://github.com/Starlord-8bit/clockwise/commit/8264d9c8495be81d39c56970dabe5f4c86449277))
* **v3:** CWClockfaceDriver — WLED-style function-pointer registry ([f31a5f7](https://github.com/Starlord-8bit/clockwise/commit/f31a5f760cb4d407dd21efede97c210cc79fccbe))
* web UI cards for clockface selector, auto-change, brightness method, night mode ([c9d4e34](https://github.com/Starlord-8bit/clockwise/commit/c9d4e346559172ae2c5746f4d21364d3c1732166))


### Bug Fixes

* add app_update to CMakeLists PRIV_REQUIRES for esp_ota_ops.h ([e5c3c07](https://github.com/Starlord-8bit/clockwise/commit/e5c3c0706eebee72f81a969b1737f05bf5c3313e))
* **ci:** fetch full git history so git describe finds release tags ([#14](https://github.com/Starlord-8bit/clockwise/issues/14)) ([4830cd0](https://github.com/Starlord-8bit/clockwise/commit/4830cd04a6b4ad8a72abf5f8cc3082a8c6ca8fb2))
* **ci:** release workflow — checkout main before tag exists, create tag after build ([88cda95](https://github.com/Starlord-8bit/clockwise/commit/88cda952104aee48d7065781272bdefa4cfd81d5))
* compile errors caught by CI ([ba6ff91](https://github.com/Starlord-8bit/clockwise/commit/ba6ff9131ee427ca6d97e5a66bc17723f18ec1d2))
* custom partition table for larger binary + clockface default ([e6e67f5](https://github.com/Starlord-8bit/clockwise/commit/e6e67f5bcb879d671ce18f5cd53a3e065bb65c05))
* defer clockface setup() until after cwDateTime.begin() (was crashing on uninitialised datetime) ([3bbca51](https://github.com/Starlord-8bit/clockwise/commit/3bbca518296764c7f71f65ca69376ba78483640e))
* dispatcher compile errors — IClockface public/destructor, small4pt7b collision, nightMode dispatcher ([4c1f2e3](https://github.com/Starlord-8bit/clockwise/commit/4c1f2e3490d675766cee4eabf2bb1aaf42989f25))
* firmware version from git tag, rename to Clockwise Paradise ([72dc88b](https://github.com/Starlord-8bit/clockwise/commit/72dc88bea9e3cf2b49e4276d2f4362e65a3d018a))
* getHour()/getMinute() — correct CWDateTime method names ([833ac52](https://github.com/Starlord-8bit/clockwise/commit/833ac52548942f6bf2946a7f35fa02e0ec46a4b6))
* guard DMA begin() failure and cwDateTime access before NTP sync ([d263568](https://github.com/Starlord-8bit/clockwise/commit/d26356840e4b5ea3a9805f24caa5f53878a47c27))
* missing closing braces in JS causing 'Unexpected token catch' syntax error ([702bc93](https://github.com/Starlord-8bit/clockwise/commit/702bc938399a521777587487bf901323a05069cb))
* MQTT config struct IDF v4.4 compatibility (flat struct, not nested) ([8b2ad10](https://github.com/Starlord-8bit/clockwise/commit/8b2ad10efb965c85e6ee3b97d1e21360771ba176))
* overhaul CI/CD — release-please automation, remove legacy workflows ([#20](https://github.com/Starlord-8bit/clockwise/issues/20)) ([0e36f99](https://github.com/Starlord-8bit/clockwise/commit/0e36f9900241b1ba7c0fc0c7dd56fc26ca8b887b))
* remove ArduinoJson dependency from CWMqtt.h — build JSON manually ([cd29738](https://github.com/Starlord-8bit/clockwise/commit/cd297386284f2b70a807c9ed9418307dd4ddadda))
* remove hardcoded IPs and repo-specific paths ([9bf1253](https://github.com/Starlord-8bit/clockwise/commit/9bf12538a616bd17af534bde7f04c97c3bac9032))
* rename project to clockwise-paradise (fixes binary artifact path) ([2d59142](https://github.com/Starlord-8bit/clockwise/commit/2d591423ee84822ce8206fa5bb46c74d0dfbc0e5))
* restore fast char-by-char HTTP parser to prevent DMA collision ([d75c48e](https://github.com/Starlord-8bit/clockwise/commit/d75c48e61fd070215c5edffbf7cb3cdbe73d27ad))
* set CONFIG_CLOCKFACE_MARIO=y as default build clockface ([b31629e](https://github.com/Starlord-8bit/clockwise/commit/b31629edfbc917dacca6ef89a5cf3cfcaaf63778))
* set flash size to 4MB in sdkconfig.defaults ([3994bdf](https://github.com/Starlord-8bit/clockwise/commit/3994bdfc650859f03b873f4b027386acd8226521))
* update submodule refs — small4pt7b namespace outside preprocessor guards ([4806ef9](https://github.com/Starlord-8bit/clockwise/commit/4806ef93964dd2dd3c0b72c7d99b235fa00226dd))
* update submodule refs to Starlord-8bit forks with namespace + Clockface0N.h ([8e35b3b](https://github.com/Starlord-8bit/clockwise/commit/8e35b3be7a320ba5d0bdb31326bb7562b7570317))
* use Clockface0N.h include names to resolve ESP-IDF flat include paths ([b548df2](https://github.com/Starlord-8bit/clockwise/commit/b548df24ebe403923a56b83fae392c07e4073e0c))
* yield to FreeRTOS scheduler in loop() to prevent WDT panics ([f4f27cf](https://github.com/Starlord-8bit/clockwise/commit/f4f27cf67811947a0600bc05b8c99b69d54dd211))

## [Unreleased]

### Changed

- Avoid use extensive of String in CWWebServer.cpp


## [1.4.2] - 2024-04-21

### Added 

- New Display Rotation param. Thanks @Xefan.
- Added ntp sync in main loop. Thanks @vandalon
- Add api documentation
- Pacman clockface: Add library.json to import using platformio
- Canvas: Feature/add sprite loop and frame delay. Thanks @robegamesios


## [1.4.1] - 2023-08-27

### Added 

- New Manual Posix param to avoid the `timezoned.rop.nl` ezTime's timezone service. Thanks @JeffWDH!

### Changed

- Set `time.google.com` as a default NTP server - `pool.ntp.org` is a slug

### Fixed

- A bug in the Canvas clockface - Commit a216c29c4f15b1b3cadbd89805d150c2f551562b


## [1.4.0] - 2023-07-01

### Added 

- Canvas clockface
- Created a method to make use of the ezTime formating string 
- Possibility to change Wifi user/pwd via API (must be connected)
- A helper to make HTTP requests

### Changed

- RGB icons used in the startup, it was replaced by one-bit images that reduce used flash


## [1.3.0] - 2023-06-11

### Added
- Configure the NTP Server
- Firmware version displayed on settings page
- LDR GPIO configuration
- Added a link in Settings page to read any pin on ESP32 (located in LDR Pin card)

### Changed

- [ABC] It's possible to turnoff the display if the LDR reading < minBright


## [1.2.0] - 2023-05-14

### Added

- Automatic bright control using LDR 
- Restart if offline for 5 minutes

### Fixed

- Clockface 0x06 (Pokedex): show AM PM only when is not using 24h format
- Restart endpoint returns HTTP 204 before restarting 


## [1.1.0] - 2023-04-02

### Added

- Implements Improv protocol to configure wifi
- Create a Settings Page where user can set up:
  - swap blue/green pins
  - use 24h format or not
  - timezone
  - display bright

### Removed

- Unused variables in main.cpp
