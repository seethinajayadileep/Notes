import {expect,test} from "@playwright/test"
test("",async({page})=>{
   await page.goto("https://letcode.in/frame")
    const pageframe=page.frames()
    console.log("total frames"+ pageframe.length)
    const firstframe=page.frame("firstFr")
    await firstframe?.fill("input[name='fname']","jaya")
    const innerframe=page.frameLocator("iframe[src='innerframe']")
    await innerframe.locator("input[name='email']").fill("jaya@gmail.com")
   await page.waitForTimeout(5000)

})