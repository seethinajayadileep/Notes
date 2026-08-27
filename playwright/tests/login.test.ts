import { chromium,test } from "@playwright/test"

test("login demo",async ()=>{
const browser=await chromium.launch({
    headless:false
})
const context=await browser.newContext()
const page=await context.newPage()

await page.goto("https://ecommerce-playground.lambdatest.io/")
await page.hover("//*[@id='widget-navbar-217834']/ul/li[6]/a/div")
await page.locator("//*[@id='widget-navbar-217834']/ul/li[6]/ul/li[1]/a/div/span").click()
await page.fill("//*[@id='input-email']","jaya1@gmail.com")
await page.fill("//*[@id='input-password']","Orange@0912")
await page.click("//*[@id='content']/div/div[2]/div/div/form/input")
await page.waitForTimeout(5000)
const newContext=await browser.newContext()
const page2=await newContext.newPage()
await page2.goto("https://ecommerce-playground.lambdatest.io/")
await page2.waitForTimeout(5000)
    })
