import { defineConfig, devices } from '@playwright/test';

/**
 * Clockwise Paradise WebUI E2E tests.
 *
 * Target device URL is set via environment variable:
 *   CW_DEVICE_URL=http://192.168.1.212
 *
 * Defaults to http://192.168.1.212 for local homelab use.
 */
export default defineConfig({
  testDir: './e2e',
  timeout: 20000,
  // Retry once — ESP32 can drop connections under load
  retries: 2,
  reporter: [['list'], ['html', { open: 'never' }]],

  // Run tests serially — ESP32 is single-threaded
  workers: 1,
  fullyParallel: false,

  use: {
    baseURL: process.env.CW_DEVICE_URL || 'http://192.168.1.212',
    headless: true,
    launchOptions: {
      args: ['--no-sandbox', '--disable-dev-shm-usage'],
    },
    // Device responds slowly — generous timeouts
    actionTimeout: 10000,
    navigationTimeout: 15000,
  },

  projects: [
    {
      name: 'chromium',
      use: { ...devices['Desktop Chrome'] },
    },
  ],
});
