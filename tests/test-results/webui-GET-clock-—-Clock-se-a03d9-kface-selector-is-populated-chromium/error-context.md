# Instructions

- Following Playwright test failed.
- Explain why, be concise, respect Playwright best practices.
- Provide a snippet of code with the fix, if possible.

# Test info

- Name: webui.spec.ts >> GET /clock — Clock settings >> clockface selector is populated
- Location: e2e/webui.spec.ts:139:7

# Error details

```
Error: page.goto: net::ERR_CONNECTION_RESET at http://192.168.1.212/clock
Call log:
  - navigating to "http://192.168.1.212/clock", waiting until "load"

```

# Test source

```ts
  40  |   test('responds with 204 and required headers', async ({ baseURL }) => {
  41  |     const res = await fetch(`${baseURL}/get`);
  42  |     expect(res.status).toBe(204);
  43  |   });
  44  | 
  45  |   test('returns firmware version header', async ({ baseURL }) => {
  46  |     const h = await getHeaders(baseURL!);
  47  |     expect(h['cw_fw_version']).toBeTruthy();
  48  |     expect(h['cw_fw_version']).not.toBe('dev');
  49  |   });
  50  | 
  51  |   test('returns device IP header', async ({ baseURL }) => {
  52  |     const h = await getHeaders(baseURL!);
  53  |     expect(h['wifiip']).toMatch(/^\d+\.\d+\.\d+\.\d+$/);
  54  |   });
  55  | 
  56  |   test('returns WiFi SSID header', async ({ baseURL }) => {
  57  |     const h = await getHeaders(baseURL!);
  58  |     expect(h['wifissid']).toBeTruthy();
  59  |   });
  60  | 
  61  |   test('timezone value is not URL-encoded', async ({ baseURL }) => {
  62  |     const h = await getHeaders(baseURL!);
  63  |     const tz = h['timezone'] || '';
  64  |     expect(tz).not.toContain('%2F');
  65  |     expect(tz).not.toContain('%');
  66  |   });
  67  | 
  68  |   test('driver header present and numeric', async ({ baseURL }) => {
  69  |     const h = await getHeaders(baseURL!);
  70  |     expect(Number(h['driver'])).toBeGreaterThanOrEqual(0);
  71  |   });
  72  | });
  73  | 
  74  | // ─── Home page ───────────────────────────────────────────────────────────────
  75  | 
  76  | test.describe('GET / — Home page', () => {
  77  |   test('page title is correct', async ({ page }) => {
  78  |     await page.goto('/');
  79  |     await expect(page).toHaveTitle('Clockwise Paradise');
  80  |   });
  81  | 
  82  |   test('header shows correct firmware version', async ({ page, baseURL }) => {
  83  |     const h = await getHeaders(baseURL!);
  84  |     await page.goto('/');
  85  |     await page.waitForTimeout(2000); // wait for JS to populate
  86  |     const ver = await page.locator('#hdr-ver').textContent();
  87  |     expect(ver).toContain(h['cw_fw_version']);
  88  |     expect(ver).not.toContain('dev');
  89  |     expect(ver).not.toContain('Loading');
  90  |   });
  91  | 
  92  |   test('status dashboard shows device IP', async ({ page }) => {
  93  |     await page.goto('/');
  94  |     await page.waitForTimeout(2000);
  95  |     const wifi = await page.locator('#wifi-info').textContent();
  96  |     expect(wifi).toMatch(/\d+\.\d+\.\d+\.\d+/);
  97  |   });
  98  | 
  99  |   test('status dashboard shows firmware name', async ({ page }) => {
  100 |     await page.goto('/');
  101 |     await page.waitForTimeout(2000);
  102 |     const fw = await page.locator('#fw-ver').textContent();
  103 |     expect(fw).toContain('Clockwise Paradise');
  104 |     expect(fw).not.toBe('…');
  105 |   });
  106 | 
  107 |   test('nav links present for all pages', async ({ page }) => {
  108 |     await page.goto('/');
  109 |     for (const href of ['/clock', '/sync', '/hardware', '/update']) {
  110 |       await expect(page.locator(`nav a[href="${href}"], .nav a[href="${href}"]`)).toBeVisible();
  111 |     }
  112 |   });
  113 | });
  114 | 
  115 | // ─── Clock page ──────────────────────────────────────────────────────────────
  116 | 
  117 | test.describe('GET /clock — Clock settings', () => {
  118 |   test('page loads without JS errors', async ({ page }) => {
  119 |     const errors: string[] = [];
  120 |     page.on('pageerror', e => errors.push(e.message));
  121 |     await page.goto('/clock');
  122 |     await page.waitForTimeout(2000);
  123 |     expect(errors).toHaveLength(0);
  124 |   });
  125 | 
  126 |   test('brightness slider is populated', async ({ page }) => {
  127 |     await page.goto('/clock');
  128 |     await page.waitForTimeout(2000);
  129 |     const val = await page.locator('#displayBright').inputValue();
  130 |     expect(Number(val)).toBeGreaterThanOrEqual(0);
  131 |     expect(Number(val)).toBeLessThanOrEqual(255);
  132 |   });
  133 | 
  134 |   test('Apply button exists', async ({ page }) => {
  135 |     await page.goto('/clock');
  136 |     await expect(page.locator('button:has-text("Apply")')).toBeVisible();
  137 |   });
  138 | 
  139 |   test('clockface selector is populated', async ({ page }) => {
> 140 |     await page.goto('/clock');
      |                ^ Error: page.goto: net::ERR_CONNECTION_RESET at http://192.168.1.212/clock
  141 |     await page.waitForTimeout(2000);
  142 |     const options = await page.locator('#clockFace option').count();
  143 |     expect(options).toBeGreaterThan(0);
  144 |   });
  145 | });
  146 | 
  147 | // ─── Sync page ───────────────────────────────────────────────────────────────
  148 | 
  149 | test.describe('GET /sync — Sync & Connectivity', () => {
  150 |   test('page loads without JS errors', async ({ page }) => {
  151 |     const errors: string[] = [];
  152 |     page.on('pageerror', e => errors.push(e.message));
  153 |     await page.goto('/sync');
  154 |     await page.waitForTimeout(2000);
  155 |     expect(errors).toHaveLength(0);
  156 |   });
  157 | 
  158 |   test('timezone field populated and not URL-encoded', async ({ page }) => {
  159 |     await page.goto('/sync');
  160 |     await page.waitForTimeout(2000);
  161 |     const tz = await page.locator('#timeZone').inputValue();
  162 |     expect(tz).not.toContain('%2F');
  163 |     expect(tz).not.toContain('%');
  164 |     expect(tz.length).toBeGreaterThan(0);
  165 |   });
  166 | 
  167 |   test('HA Discovery toggle is disabled (not yet implemented)', async ({ page }) => {
  168 |     await page.goto('/sync');
  169 |     const disabled = await page.locator('#haDiscovery').isDisabled();
  170 |     expect(disabled).toBe(true);
  171 |   });
  172 | 
  173 |   test('MQTT port defaults to 1883', async ({ page }) => {
  174 |     await page.goto('/sync');
  175 |     await page.waitForTimeout(2000);
  176 |     const port = await page.locator('#mqttPort').inputValue();
  177 |     expect(port).toBe('1883');
  178 |   });
  179 | });
  180 | 
  181 | // ─── Hardware page ───────────────────────────────────────────────────────────
  182 | 
  183 | test.describe('GET /hardware — Hardware settings', () => {
  184 |   test('page loads without JS errors', async ({ page }) => {
  185 |     const errors: string[] = [];
  186 |     page.on('pageerror', e => errors.push(e.message));
  187 |     await page.goto('/hardware');
  188 |     await page.waitForTimeout(2000);
  189 |     expect(errors).toHaveLength(0);
  190 |   });
  191 | 
  192 |   test('driver selector is populated from device', async ({ page }) => {
  193 |     await page.goto('/hardware');
  194 |     await page.waitForTimeout(2000);
  195 |     const driver = await page.locator('#driver').inputValue();
  196 |     expect(['0', '1', '2', '3', '4', '5']).toContain(driver);
  197 |   });
  198 | 
  199 |   test('Apply button exists', async ({ page }) => {
  200 |     await page.goto('/hardware');
  201 |     await expect(page.locator('button:has-text("Apply")')).toBeVisible();
  202 |   });
  203 | });
  204 | 
  205 | // ─── Update page ─────────────────────────────────────────────────────────────
  206 | 
  207 | test.describe('GET /update — Firmware update', () => {
  208 |   test('page loads without JS errors', async ({ page }) => {
  209 |     const errors: string[] = [];
  210 |     page.on('pageerror', e => errors.push(e.message));
  211 |     await page.goto('/update');
  212 |     await page.waitForTimeout(2000);
  213 |     expect(errors).toHaveLength(0);
  214 |   });
  215 | 
  216 |   test('version badge shows current version', async ({ page, baseURL }) => {
  217 |     const h = await getHeaders(baseURL!);
  218 |     await page.goto('/update');
  219 |     await page.waitForTimeout(2000);
  220 |     const ver = await page.locator('#ver').textContent();
  221 |     expect(ver).toContain(h['cw_fw_version']);
  222 |   });
  223 | 
  224 |   test('upload file input accepts .bin', async ({ page }) => {
  225 |     await page.goto('/update');
  226 |     const accept = await page.locator('#bin').getAttribute('accept');
  227 |     expect(accept).toContain('.bin');
  228 |   });
  229 | });
  230 | 
  231 | // ─── OTA check API ───────────────────────────────────────────────────────────
  232 | 
  233 | test.describe('GET /ota/check — OTA check API', () => {
  234 |   test('responds with JSON', async ({ baseURL }) => {
  235 |     const res = await fetch(`${baseURL}/ota/check`);
  236 |     const ct = res.headers.get('content-type') || '';
  237 |     expect(ct).toContain('application/json');
  238 |   });
  239 | 
  240 |   test('response contains available field or error status', async ({ baseURL }) => {
```