# Clockwise Paradise — E2E Tests

Playwright end-to-end tests for the device WebUI.

## Requirements

- Node.js ≥ 18
- Device reachable on the network

## Setup

```bash
cd tests
npm install
npx playwright install chromium
```

## Run against a live device

```bash
# Default target: http://192.168.1.212
npm test

# Override target
CW_DEVICE_URL=http://192.168.1.50 npm test
```

## What's tested

| Suite | File |
|---|---|
| `GET /get` — settings API headers | `e2e/webui.spec.ts` |
| Home page — version, IP, nav | `e2e/webui.spec.ts` |
| Clock page — brightness, clockface | `e2e/webui.spec.ts` |
| Sync page — timezone decode, HA stub | `e2e/webui.spec.ts` |
| Hardware page — driver selector | `e2e/webui.spec.ts` |
| Update page — version badge, upload | `e2e/webui.spec.ts` |
| OTA check API — JSON response | `e2e/webui.spec.ts` |
| Legacy UI — fallback page exists | `e2e/webui.spec.ts` |

## CI

Tests run automatically via GitHub Actions on pushes and PRs.
See `.github/workflows/e2e.yml`.
