import {expect,test} from "@playwright/test"
test("handling alerts",async ({page})=>{
    await page.goto("https://www.testmuai.com/selenium-playground/javascript-alert-box-demo/")
    page.on("dialog",async (alert)=>{
        const message=alert.message()
        console.log(message)
        await alert.accept();

    })
    const alertbutton=page.locator("//*[@id='__next']/div/main/section[2]/div/div/div/div[1]/p/button")
    expect(alertbutton).toHaveText("Click Me")
   await  alertbutton.click()
   await page.waitForTimeout(5000)
    
})