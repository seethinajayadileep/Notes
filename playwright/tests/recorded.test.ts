import { test, expect } from '@playwright/test';

test('test', async ({ page }) => {
  await page.goto('https://ecommerce-playground.lambdatest.io/');
  await page.hover("//*[@id='widget-navbar-217834']/ul/li[6]/a/div")
  await page.getByRole('link', { name: 'Login' }).click();
  await page.goto('https://ecommerce-playground.lambdatest.io/index.php?route=account/login');
  await page.getByRole('textbox', { name: 'E-Mail Address' }).click();
  await page.getByRole('textbox', { name: 'E-Mail Address' }).fill('jaya@gmail.com');
  await page.getByRole('textbox', { name: 'Password' }).click();
  await page.getByRole('textbox', { name: 'E-Mail Address' }).press('CapsLock');
  await page.getByRole('textbox', { name: 'Password' }).fill('Orange@0912');
  await page.getByRole('button', { name: 'Login' }).click();
  await page.locator('.card-body').first().click();
  await page.getByRole('link', { name: ' Back' }).click();
  await page.hover("//*[@id='widget-navbar-217834']/ul/li[6]/a/div/span")

  await page.getByRole('link', { name: 'Logout', exact: true }).click();
  await page.waitForTimeout(5000)
});